#include "logger.h"

#include <print>
#include <string>
#include <utility>

namespace Logger {

namespace {

std::string LevelToString(Level level) {
  switch (level) {
    case Level::Debug:
      return "[DEBUG]";
    case Level::Info:
      return "[INFO]";
    case Level::Warning:
      return "[WARNING]";
    case Level::Error:
      return "[ERROR]";
    default:
      std::unreachable();
  }
}

bool ShouldLog([[maybe_unused]] Level level) {
#ifdef DEBUG_MODE
  return true;
#else
  return false;
#endif  // DEBUG_MODE
}

}  // namespace

void Log(Level level, const std::string& message) {
  if (!ShouldLog(level)) {
    return;
  }
  std::println("{} {}", LevelToString(level), message);
}

void Log(Level level, const std::string& context, const std::string& message) {
  if (!ShouldLog(level)) {
    return;
  }
  std::println("{}[{}] {}", LevelToString(level), context, message);
}

void Debug(const std::string& message) {
  Log(Level::Debug, message);
}
void Info(const std::string& message) {
  Log(Level::Info, message);
}
void Warning(const std::string& message) {
  Log(Level::Warning, message);
}
void Error(const std::string& message) {
  Log(Level::Error, message);
}

void Debug(const std::string& context, const std::string& message) {
  Log(Level::Debug, context, message);
}
void Info(const std::string& context, const std::string& message) {
  Log(Level::Info, context, message);
}
void Warning(const std::string& context, const std::string& message) {
  Log(Level::Warning, context, message);
}
void Error(const std::string& context, const std::string& message) {
  Log(Level::Error, context, message);
}

}  // namespace Logger
