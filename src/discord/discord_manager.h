#pragma once

#include <stdint.h>

#include <memory>

#include "discordpp.h"

class DiscordManager : public std::enable_shared_from_this<DiscordManager> {
 public:
  DiscordManager();
  ~DiscordManager() = default;
  DiscordManager(const DiscordManager&) = delete;
  DiscordManager& operator=(const DiscordManager&) = delete;
  DiscordManager(DiscordManager&&) = delete;
  DiscordManager& operator=(DiscordManager&&) = delete;

  void Init();
  void RunCallbacks();

 private:
  std::shared_ptr<discordpp::Client> client_;
  const uint64_t application_id_ = 1544628625301704835;
};
