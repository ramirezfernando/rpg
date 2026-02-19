class Server {
 public:
  Server() = default;
  ~Server() = default;
  Server(const Server& other) = delete;
  Server operator=(const Server& other) = delete;
  Server(Server&& other) = delete;
  Server operator=(const Server&& other) = delete;
};