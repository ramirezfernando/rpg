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

  std::array<char, Constants::MAX_BUFFER_SIZE> buffer{};
  sockaddr_storage client_address{};
  socklen_t client_address_length = sizeof(client_address);

  while (true) {
    const ssize_t n = server->ReceiveFrom(
        buffer.data(), buffer.size(), client_address, client_address_length);
    if (n <= 0) {
      continue;
    }

    // TODO(ramirezfernando): Deserialize buffer into a game state update.
    // TODO(ramirezfernando): Run authoritative game logic.
    // TODO(ramirezfernando): Serialize and broadcast updated state back.

    server->SendTo(buffer.data(), static_cast<size_t>(n), client_address,
                   client_address_length);
  }

  return 0;
}