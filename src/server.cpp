#include "network/server.h"

#include <sys/_types/_socklen_t.h>
#include <sys/_types/_ssize_t.h>
#include <sys/socket.h>

#include <array>
#include <cstddef>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "constants/network_constants.h"
#include "network/packet.h"
#include "util/logger.h"

struct PlayerState {
  uint32_t id;
  int32_t x, y;
  sockaddr_storage client_address;
  socklen_t client_address_length;
};

// Client ID (or packet ID) is the key, `PlayerState` is the value.
static std::map<uint32_t, PlayerState> players;
static uint32_t nextClientId = 1;

int main() {
  auto server =
      std::unique_ptr<Server>(Server::Create(std::to_string(Constants::PORT)));

  Packet packet{};
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
      players[packet.id] = {packet.id, packet.x_pos, packet.y_pos,
                            client_address, client_address_length};
      server->SendTo(&packet, sizeof(packet), client_address,
                     client_address_length);
      Logger::Debug("Server",
                    "New player with ID: " + std::to_string(packet.id));
      continue;
    }

    // Update an existing player's state.
    auto& state = players[packet.id];
    state.x = packet.x_pos;
    state.y = packet.y_pos;

    // Build a snapshot containing every player's state.
    std::vector<Packet> snapshot;
    snapshot.reserve(players.size());
    for (auto const& [_, state] : players) {
      snapshot.push_back({state.id, state.x, state.y});
    }

    // Broadcast the snapshot to every client.
    for (auto const& [_, state] : players) {
      server->SendTo(snapshot.data(), snapshot.size() * sizeof(Packet),
                     state.client_address, state.client_address_length);
    }
  }

  return 0;
}