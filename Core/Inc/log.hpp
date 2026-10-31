
#ifndef __LOG_HPP
#define __LOG_HPP

// Logs to the serial monitor over USART2 (PA2 = TX), 115200 8N1.
// Output: "[    1.234] I APP: message"
//
// Usage: LOG_INFO("APP", "value = %d", value);
//
// Not safe to call from interrupts.

enum class LogLevel
{
  Debug,
  Info,
  Warning,
  Error,
};

// Messages below this level are not sent
#ifndef LOG_MIN_LEVEL
#define LOG_MIN_LEVEL LogLevel::Debug
#endif

void log_write(LogLevel level, const char* tag, const char* format, ...)
  __attribute__((format(printf, 3, 4)));

#define LOG_DEBUG(tag, ...)   log_write(LogLevel::Debug, tag, __VA_ARGS__)
#define LOG_INFO(tag, ...)    log_write(LogLevel::Info, tag, __VA_ARGS__)
#define LOG_WARNING(tag, ...) log_write(LogLevel::Warning, tag, __VA_ARGS__)
#define LOG_ERROR(tag, ...)   log_write(LogLevel::Error, tag, __VA_ARGS__)

#endif /* __LOG_HPP */
