#include "network/server.h"

int main() {
  auto server = std::unique_ptr<Server>(Server::Create("8080"));

  char buf[1024];
  sockaddr_storage peer{};
  socklen_t peer_len = sizeof(peer);  // Will be updated by ReceiveFrom.

  while (true) {
    ssize_t n = server->ReceiveFrom(buf, sizeof(buf), peer, peer_len);
    if (n <= 0) {
      continue;
    }

    // TODO(ramirezfernando): Deserialize buf into a game state update.
    // TODO(ramirezfernando): Run authoritative game logic.
    // TODO(ramirezfernando): Serialize and broadcast updated state back.

    server->SendTo(buf, static_cast<size_t>(n), peer, peer_len);
  }

  return 0;
}