#include "network/server.h"

int main() {
  auto server = std::unique_ptr<Server>(Server::Create("8080"));

  char buf[1024];
  sockaddr_storage peer{};

  while (true) {
    ssize_t n = server->ReceiveFrom(buf, sizeof(buf), peer);
    if (n <= 0) continue;

    // TODO: deserialize buf into a game state update
    // TODO: run authoritative game logic
    // TODO: serialize and broadcast updated state back

    server->SendTo(buf, static_cast<size_t>(n), peer);  // echo back for now
  }

  return 0;
}