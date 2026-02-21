#include <sys/socket.h>
#include <sys/types.h>

#include <memory>

class Server {
 public:
  ~Server();
  Server(const Server& other) = delete;
  Server operator=(const Server& other) = delete;
  Server(Server&& other) = delete;
  Server operator=(const Server&& other) = delete;

  static std::unique_ptr<Server> Create(const std::string& port);
  ssize_t ReceiveFrom(void* buf, size_t len, sockaddr_storage& peer,
                      socklen_t& peer_len) const;
  ssize_t SendTo(const void* buf, size_t len, const sockaddr_storage& peer,
                 socklen_t peer_len) const;

 private:
  explicit Server(int socket_file_descriptor)
      : socket_file_descriptor_(socket_file_descriptor) {}
  int socket_file_descriptor_{-1};
};