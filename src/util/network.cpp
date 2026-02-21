#include "network.h"

#include <netdb.h>
#include <sys/socket.h>

#include <cerrno>
#include <cstddef>
#include <cstring>
#include <string>

#include "util/logger.h"

namespace Network {

struct addrinfo* GetAddressInfo(const std::string& host,
                                const std::string& port, bool passive) {
  struct addrinfo hints{};
  // NOLINTNEXTLINE(misc-const-correctness)
  struct addrinfo* result{nullptr};

  memset(&hints, 0, sizeof hints);  // Make sure the struct is empty.
  hints.ai_family = AF_UNSPEC;      // Don't care IPv4 or IPv6.
  hints.ai_socktype = SOCK_DGRAM;   // UDP socket.
  if (passive) {
    hints.ai_flags = AI_PASSIVE;  // Fill in my IP for me.
  }

  const char* node = host.empty() ? nullptr : host.c_str();
  // NOLINTNEXTLINE(misc-const-correctness)
  int status = getaddrinfo(node, port.c_str(), &hints, &result);
  if (status != 0) {
    Logger::Error("Socket", gai_strerror(errno));
  }
  // TODO(ramirezfernando): Be sure to free this pointer.
  return result;
}

}  // namespace Network