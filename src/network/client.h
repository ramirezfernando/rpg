#include <sys/socket.h>
#include <sys/types.h>

#include <memory>
#include <string>

class Client {
 public:
  ~Client();
  Client(const Client& other) = delete;
  Client operator=(const Client& other) = delete;
  Client(Client&& other) = delete;
  Client operator=(Client&& other) = delete;

  static std::unique_ptr<Client> Create(const std::string& host,
                                        const std::string& port);
  ssize_t Send(const void* buffer, size_t buffer_length) const;
  ssize_t Receive(void* buffer, size_t buffer_length) const;

 private:
  explicit Client(int socket_file_descriptor)
      : socket_file_descriptor_(socket_file_descriptor) {}
  int socket_file_descriptor_;
};