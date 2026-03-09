#include "network/server.h"

#include <sys/_types/_socklen_t.h>
#include <sys/types.h>
#include <sys/socket.h>

#include <array>
#include <cstddef>
#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "constants/network_constants.h"
#include "util/logger.h"
#include "util/network.h"

namespace {

struct PlayerState {
  Network::Packet client_packet;
  sockaddr_storage client_address;
  socklen_t client_address_length;
};

// Client ID (or packet ID) is the key, `PlayerState` is the value.
// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
std::map<uint32_t, PlayerState> players;
// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
uint32_t nextClientId = 1;

}  // anonymous namespace

// NOLINTNEXTLINE(bugprone-exception-escape)
int main() {
  auto server =
      std::unique_ptr<Server>(Server::Create(std::to_string(Constants::PORT)));

  Network::Packet packet{};
  sockaddr_storage client_address{};
  socklen_t client_address_length = sizeof(client_address);

  while (true) {
    // Read a player state update from any client.
    const ssize_t bytes_received = server->ReceiveFrom(
        &packet, sizeof(packet), client_address, client_address_length);
    if (bytes_received == -1) {
      continue;
    }

    // Register a new player if the client id is 0 (convention for "new
    // player").
    if (packet.id == 0) {
      packet.id = nextClientId++;
      players[packet.id] = {
          .client_packet = Network::Packet{.id = packet.id,
                                           .x_pos = packet.x_pos,
                                           .y_pos = packet.y_pos},
          .client_address = client_address,
          .client_address_length = client_address_length};
      server->SendTo(&packet, sizeof(packet), client_address,
                     client_address_length);
      Logger::Debug("Server",
                    "New player with ID: " + std::to_string(packet.id));
      continue;
    }

    // Update an existing player's state.
    auto& state = players[packet.id];
    state.client_packet.x_pos = packet.x_pos;
    state.client_packet.y_pos = packet.y_pos;

    // Build a snapshot containing every player's state.
    std::vector<Network::Packet> snapshot;
    snapshot.reserve(players.size());

    for (auto const& [_, state] : players) {
      snapshot.push_back(state.client_packet);
    }

    // Broadcast the snapshot to every client.
    for (auto const& [_, state] : players) {
      server->SendTo(snapshot.data(), snapshot.size() * sizeof(Network::Packet),
                     state.client_address, state.client_address_length);
    }
  }

  return 0;
}