class Socket {
 public:
  Socket() = default;
  ~Socket() = default;
  Socket(const Socket& other) = delete;
  Socket operator=(const Socket& other) = delete;
  Socket(Socket&& other) = delete;
  Socket operator=(Socket&& other) = delete;
};