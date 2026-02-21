#pragma once

#include <sys/types.h>

#include <cstddef>
#include <memory>
#include <string>

class Socket {
 public:
  Socket(int socket_file_descriptor);
  ~Socket();
  Socket(const Socket& other) = delete;
  Socket& operator=(const Socket& other) = delete;
  Socket(Socket&& other) = delete;
  Socket& operator=(Socket&& other) = delete;

  static struct addrinfo* GetAddressInfo(const std::string& host,
                                         const std::string& port, bool passive);
  int GetFileDescriptor() const { return socket_file_descriptor_; }

 private:
  int socket_file_descriptor_;
};