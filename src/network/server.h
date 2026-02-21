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
  ssize_t ReceiveFrom(void* buffer, size_t buffer_length,
                      sockaddr_storage& client_address,
                      socklen_t& client_address_length) const;
  ssize_t SendTo(const void* buffer, size_t buffer_length,
                 const sockaddr_storage& client_address,
                 socklen_t client_address_length) const;

 private:
  explicit Server(int socket_file_descriptor)
      : socket_file_descriptor_(socket_file_descriptor) {}
  int socket_file_descriptor_{-1};
};