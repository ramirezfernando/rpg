#include "server.h"

#include <netdb.h>
#include <netinet/in.h>
#include <sys/_types/_socklen_t.h>
#include <sys/_types/_ssize_t.h>
#include <sys/socket.h>
#include <unistd.h>

#include <cerrno>
#include <cstring>
#include <memory>
#include <string>

#include "util/logger.h"
#include "util/network.h"

Server::~Server() {
  close(socket_file_descriptor_);
}

std::unique_ptr<Server> Server::Create(const std::string& port) {
  addrinfo* address_info = Network::GetAddressInfo("", port, true);
  if (address_info == nullptr) {
    return nullptr;
  }

  const int socket_file_descriptor =
      socket(address_info->ai_family, address_info->ai_socktype,
             address_info->ai_protocol);
  if (socket_file_descriptor == -1) {
    Logger::Error("Server", strerror(errno));
    return nullptr;
  }

  if (bind(socket_file_descriptor, address_info->ai_addr,
           address_info->ai_addrlen) == -1) {
    Logger::Error("Server", strerror(errno));
    close(socket_file_descriptor);
    return nullptr;
  }

  freeaddrinfo(address_info);

  Logger::Debug("Server", "Created");
  return std::unique_ptr<Server>(new Server(socket_file_descriptor));
}

ssize_t Server::ReceiveFrom(void* buf, size_t len, sockaddr_storage& peer,
                            socklen_t& peer_len) const {
  peer_len = sizeof(peer);
  const ssize_t bytes_recieved =
      // NOLINTNEXTLINE(cppcoreguidelines-pro-type-cstyle-cast)
      recvfrom(socket_file_descriptor_, buf, len, 0, (sockaddr*)&peer,
               &peer_len);
  if (bytes_recieved == -1) {
    Logger::Error("Server", strerror(errno));
  }
  Logger::Debug("Server", "ReceiveFrom");
  return bytes_recieved;
}

ssize_t Server::SendTo(const void* buf, size_t len,
                       const sockaddr_storage& peer, socklen_t peer_len) const {
  const ssize_t bytes_sent =
      sendto(socket_file_descriptor_, buf, len, 0,
             // NOLINTNEXTLINE(cppcoreguidelines-pro-type-cstyle-cast)
             (const sockaddr*)&peer, peer_len);
  if (bytes_sent == -1) {
    Logger::Error("Server", strerror(errno));
  }
  Logger::Debug("Server", "SendTo");
  return bytes_sent;
}