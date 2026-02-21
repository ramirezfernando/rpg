#include "client.h"

#include <netdb.h>
#include <sys/_types/_ssize_t.h>
#include <sys/socket.h>
#include <unistd.h>

#include <cerrno>
#include <cstring>
#include <memory>
#include <string>

#include "network/socket.h"
#include "util/logger.h"

std::unique_ptr<Client> Client::Create(const std::string& host,
                                       const std::string& port) {
  const addrinfo* address_info = Socket::GetAddressInfo(host, port, false);
  if (address_info == nullptr) {
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
  // fcntl(fd, F_SETFL, O_NONBLOCK);
  if (status == -1) {
    Logger::Error("Client", strerror(errno));
    close(socket_file_descriptor);
    return nullptr;
  }

  Logger::Debug("Client", "Created");
  return std::unique_ptr<Client>(new Client(socket_file_descriptor));
}

ssize_t Client::Send(const void* buf, size_t len) {
  const ssize_t bytes_sent = send(GetFileDescriptor(), buf, len, 0);
  if (bytes_sent == -1) {
    Logger::Error("Client", strerror(errno));
  }
  Logger::Debug("Client", "Send");
  return bytes_sent;
}

ssize_t Client::Receive(void* buf, size_t len) {
  const ssize_t bytes_read_into_buffer = recv(GetFileDescriptor(), buf, len, 0);
  if (bytes_read_into_buffer == -1) {
    Logger::Error("Client", strerror(errno));
  }
  Logger::Debug("Client", "Receive");
  return bytes_read_into_buffer;
}