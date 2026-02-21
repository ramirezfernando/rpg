#include <sys/socket.h>
#include <sys/types.h>

#include "socket.h"

class Client : public Socket {
 public:
  ~Client() = default;
  Client(const Client& other) = delete;
  Client operator=(const Client& other) = delete;
  Client(Client&& other) = delete;
  Client operator=(Client&& other) = delete;

  static std::unique_ptr<Client> Create(const std::string& host,
                                        const std::string& port);
  ssize_t Send(const void* buf, size_t len);
  ssize_t Receive(void* buf, size_t len);

 private:
  Client(int socket_file_descriptor) : Socket(socket_file_descriptor) {}
};