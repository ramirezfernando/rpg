#pragma once

#include <netdb.h>
#include <sys/types.h>

#include <string>

namespace Network {

struct addrinfo* GetAddressInfo(const std::string& host,
                                const std::string& port, bool passive);

}  // namespace Network