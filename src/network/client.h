class Client {
 public:
  Client() = default;
  ~Client() = default;
  Client(const Client& other) = delete;
  Client operator=(const Client& other) = delete;
  Client(Client&& other) = delete;
  Client operator=(Client&& other) = delete;
};