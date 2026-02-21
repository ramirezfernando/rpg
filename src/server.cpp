#include "network/server.h"

#include <sys/_types/_socklen_t.h>
#include <sys/_types/_ssize_t.h>
#include <sys/socket.h>

#include <array>
#include <cstddef>
#include <memory>

int main() {
  auto server = std::unique_ptr<Server>(Server::Create("8080"));

  const size_t maxBufferSize = 1024;
  std::array<char, maxBufferSize> buf{};
  sockaddr_storage peer{};
  socklen_t peer_len = sizeof(peer);  // Will be updated by ReceiveFrom.

  while (true) {
    const ssize_t n =
        server->ReceiveFrom(buf.data(), sizeof(buf.data()), peer, peer_len);
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