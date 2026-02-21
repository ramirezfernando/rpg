#include <sys/socket.h>
#include <sys/types.h>

#include "socket.h"

class Server : public Socket {
 public:
  ~Server() = default;
  Server(const Server& other) = delete;
  Server operator=(const Server& other) = delete;
  Server(Server&& other) = delete;
  Server operator=(const Server&& other) = delete;

  static std::unique_ptr<Server> Create(const std::string& port);
  ssize_t ReceiveFrom(void* buf, size_t len, sockaddr_storage& peer,
                      socklen_t& peer_len);
  ssize_t SendTo(const void* buf, size_t len, const sockaddr_storage& peer,
                 socklen_t peer_len);

 private:
  Server(int socket_file_descriptor) : Socket(socket_file_descriptor) {}
};