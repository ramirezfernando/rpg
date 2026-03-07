#pragma once

#include <netdb.h>
#include <sys/types.h>

#include <string>

namespace Network {

struct Packet {
  uint32_t id;
  int x_pos;
  int y_pos;
};

struct addrinfo* GetAddressInfo(const std::string& host,
                                const std::string& port, bool passive);

}  // namespace Network