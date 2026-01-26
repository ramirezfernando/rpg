#include "logger.h"

#include <iostream>
#include <sstream>

namespace Logger {

namespace {
Level current_level = Level::Debug;

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
  }
  return "[UNKNOWN]";
}

bool ShouldLog(Level level) {
  return level >= current_level;
}
}  // namespace

void SetLevel(Level level) {
  current_level = level;
}

void Log(Level level, const std::string& message) {
  if (!ShouldLog(level)) {
    return;
  }
  // Note: Do not use `std::endl` as it implicitly flushes the buffer.
  std::cerr << LevelToString(level) << " " << message << '\n';
}

void Log(Level level, const std::string& context, const std::string& message) {
  if (!ShouldLog(level)) {
    return;
  }
  // Note: Do not use `std::endl` as it implicitly flushes the buffer.
  std::cerr << LevelToString(level) << " [" << context << "] " << message
            << '\n';
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
