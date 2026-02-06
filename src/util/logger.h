#pragma once

#include <string>

namespace Logger {

// Logging levels
enum class Level : std::uint8_t { Debug, Info, Warning, Error };

// Log a message with a specific level
void Log(Level level, const std::string& message);
void Log(Level level, const std::string& context, const std::string& message);

// Convenience functions
void Debug(const std::string& message);
void Info(const std::string& message);
void Warning(const std::string& message);
void Error(const std::string& message);

// Context variants for better organization
void Debug(const std::string& context, const std::string& message);
void Info(const std::string& context, const std::string& message);
void Warning(const std::string& context, const std::string& message);
void Error(const std::string& context, const std::string& message);

}  // namespace Logger
