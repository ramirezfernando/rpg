#include "network/server.h"

#include <sys/_types/_socklen_t.h>
#include <sys/_types/_ssize_t.h>
#include <sys/socket.h>

#include <array>
#include <cstddef>
#include <memory>
#include <string>

#include "constants/network_constants.h"

int main() {
  auto server =
      std::unique_ptr<Server>(Server::Create(std::to_string(Constants::PORT)));

  std::array<char, Constants::MAX_BUFFER_SIZE> buf{};
  sockaddr_storage peer{};
  socklen_t peer_len = sizeof(peer);

  while (true) {
    const ssize_t n =
        server->ReceiveFrom(buf.data(), buf.size(), peer, peer_len);
    if (n <= 0) {
      continue;
    }

    // TODO(ramirezfernando): Deserialize buf into a game state update.
    // TODO(ramirezfernando): Run authoritative game logic.
    // TODO(ramirezfernando): Serialize and broadcast updated state back.

    server->SendTo(buf.data(), static_cast<size_t>(n), peer, peer_len);
  }

  return 0;
}