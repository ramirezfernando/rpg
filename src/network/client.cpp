#include "client.h"

#include <fcntl.h>
#include <netdb.h>
#include <sys/_types/_ssize_t.h>
#include <sys/fcntl.h>
#include <sys/socket.h>
#include <unistd.h>

#include <cerrno>
#include <cstring>
#include <memory>
#include <string>

#include "util/logger.h"
#include "util/network.h"

Client::~Client() {
  close(socket_file_descriptor_);
  Logger::Debug("Client", "Destroyed");
}

std::unique_ptr<Client> Client::Create(const std::string& host,
                                       const std::string& port) {
  addrinfo* address_info = Network::GetAddressInfo(host, port, false);
  if (address_info == nullptr) {
    Logger::Error("Client", "Failed to get address info");
    return nullptr;
  }

  const int socket_file_descriptor =
      socket(address_info->ai_family, address_info->ai_socktype,
             address_info->ai_protocol);
  if (socket_file_descriptor == -1) {
    Logger::Error("Client", strerror(errno));
    return nullptr;
  }

  const int status = connect(socket_file_descriptor, address_info->ai_addr,
                             address_info->ai_addrlen);

  freeaddrinfo(address_info);

  // Set the socket to non-blocking mode so that `recv` calls do not block the
  // game loop. NOLINTNEXTLINE(cppcoreguidelines-pro-type-vararg)
  fcntl(socket_file_descriptor, F_SETFL, O_NONBLOCK);

  if (status == -1) {
    Logger::Error("Client", strerror(errno));
    close(socket_file_descriptor);
    return nullptr;
  }

  Logger::Debug("Client", "Created");
  return std::unique_ptr<Client>(new Client(socket_file_descriptor));
}

ssize_t Client::Send(const void* buffer, size_t buffer_length) const {
  const ssize_t bytes_sent =
      send(socket_file_descriptor_, buffer, buffer_length, 0);
  if (bytes_sent == -1) {
    Logger::Error("Client", strerror(errno));
  }
  Logger::Debug("Client", "Sent " + std::to_string(bytes_sent) + " bytes");
  return bytes_sent;
}

ssize_t Client::Receive(void* buffer, size_t buffer_length) const {
  const ssize_t bytes_received =
      recv(socket_file_descriptor_, buffer, buffer_length, 0);
  if (bytes_received == -1) {
    Logger::Error("Client", strerror(errno));
  }
  Logger::Debug("Client",
                "Received " + std::to_string(bytes_received) + " bytes");
  return bytes_received;
}