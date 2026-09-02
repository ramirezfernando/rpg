#define DISCORDPP_IMPLEMENTATION

#include "discord_manager.h"

#include <atomic>
#include <csignal>
#include <functional>
#include <iostream>
#include <string>
#include <thread>

DiscordManager::DiscordManager() = default;

void DiscordManager::Init() {
  std::cout << "🚀 Initializing Discord SDK...\n";

  // Create our Discord Client.
  client_ = std::make_shared<discordpp::Client>();
  std::weak_ptr<DiscordManager> weakSelf = weak_from_this();

  // Set up logging callback.
  client_->AddLogCallback(
      [weakSelf](auto message, auto severity) {
        auto self = weakSelf.lock();
        if (!self)
          return;
        std::cout << "[" << EnumToString(severity) << "] " << message
                  << std::endl;
      },
      discordpp::LoggingSeverity::Info);

  // Set up status callback to monitor `client_` connection.
  client_->SetStatusChangedCallback([weakSelf](discordpp::Client::Status status,
                                               discordpp::Client::Error error,
                                               int32_t errorDetail) {
    auto self = weakSelf.lock();
    if (!self)
      return;

    std::cout << "🔄 Status changed: "
              << discordpp::Client::StatusToString(status) << std::endl;

    if (status == discordpp::Client::Status::Ready) {
      std::cout << "✅ Client is ready! You can now call SDK functions.\n";

      // Configure rich presence details.
      discordpp::Activity activity;
      activity.SetType(discordpp::ActivityTypes::Playing);
      activity.SetState("In Competitive Match");
      activity.SetDetails("Rank: One Above All");

      // Update rich presence.
      self->client_->UpdateRichPresence(
          activity, [weakSelf](discordpp::ClientResult result) {
            auto self = weakSelf.lock();
            if (!self)
              return;
            if (result.Successful()) {
              std::cout << "🎮 Rich Presence updated successfully!\n";
            } else {
              std::cerr << "❌ Rich Presence update failed";
            }
          });

    } else if (error != discordpp::Client::Error::None) {
      std::cerr << "❌ Connection Error: "
                << discordpp::Client::ErrorToString(error)
                << " - Details: " << errorDetail << std::endl;
    }
  });

  // Generate OAuth2 code verifier for authentication.
  auto codeVerifier = client_->CreateAuthorizationCodeVerifier();

  // Set up authentication arguments.
  discordpp::AuthorizationArgs args{};
  args.SetClientId(application_id_);
  args.SetScopes(discordpp::Client::GetDefaultPresenceScopes());
  args.SetCodeChallenge(codeVerifier.Challenge());

  // Begin authentication process.
  client_->Authorize(args, [weakSelf, codeVerifier](auto result, auto code,
                                                    auto redirectUri) {
    auto self = weakSelf.lock();
    if (!self)
      return;

    if (!result.Successful()) {
      std::cerr << "❌ Authentication Error: " << result.Error() << std::endl;
      return;
    }

    std::cout << "✅ Authorization successful! Getting access token...\n";

    // Exchange auth code for access token.
    self->client_->GetToken(
        self->application_id_, code, codeVerifier.Verifier(), redirectUri,
        [weakSelf](discordpp::ClientResult result, std::string accessToken,
                   std::string refreshToken,
                   discordpp::AuthorizationTokenType tokenType,
                   int32_t expiresIn, std::string scope) {
          auto self = weakSelf.lock();
          if (!self)
            return;

          std::cout << "🔓 Access token received! Establishing connection...\n";

          // Update the token and connect.
          self->client_->UpdateToken(
              discordpp::AuthorizationTokenType::Bearer, accessToken,
              [weakSelf](discordpp::ClientResult result) {
                auto self = weakSelf.lock();
                if (!self)
                  return;

                if (result.Successful()) {
                  std::cout << "🔑 Token updated, connecting to Discord...\n";
                  self->client_->Connect();
                }
              });
        });
  });
}

void DiscordManager::RunCallbacks() {
  discordpp::RunCallbacks();
}
