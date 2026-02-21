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
  Logger::Debug("Server", "Destroyed");
}

std::unique_ptr<Server> Server::Create(const std::string& port) {
  addrinfo* address_info = Network::GetAddressInfo("", port, true);
  if (address_info == nullptr) {
    Logger::Error("Server", "Failed to get address info");
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

ssize_t Server::ReceiveFrom(void* buffer, size_t buffer_length,
                            sockaddr_storage& client_address,
                            socklen_t& client_address_length) const {
  client_address_length = sizeof(client_address);
  const ssize_t bytes_recieved =
      recvfrom(socket_file_descriptor_, buffer, buffer_length, 0,
               // NOLINTNEXTLINE(cppcoreguidelines-pro-type-cstyle-cast)
               (sockaddr*)&client_address, &client_address_length);
  if (bytes_recieved == -1) {
    Logger::Error("Server", strerror(errno));
  }
  Logger::Debug("Server",
                "Received " + std::to_string(bytes_recieved) + " bytes");
  return bytes_recieved;
}

ssize_t Server::SendTo(const void* buffer, size_t buffer_length,
                       const sockaddr_storage& client_address,
                       socklen_t client_address_length) const {
  const ssize_t bytes_sent =
      sendto(socket_file_descriptor_, buffer, buffer_length, 0,
             // NOLINTNEXTLINE(cppcoreguidelines-pro-type-cstyle-cast)
             (const sockaddr*)&client_address, client_address_length);
  if (bytes_sent == -1) {
    Logger::Error("Server", strerror(errno));
  }
  Logger::Debug("Server", "Sent " + std::to_string(bytes_sent) + " bytes");
  return bytes_sent;
}