/**
  ******************************************************************************
  * @file           : log.cpp
  * @brief          : Logging to the serial monitor over USART2
  ******************************************************************************
  */
#include "log.hpp"
#include "main.h"

#include <cstdarg>
#include <cstdio>

// Defined and initialized by CubeMX in main.c
extern "C" UART_HandleTypeDef huart2;

// Static instead of on the stack: the stack is only 1 KB
static char log_buffer[256];

static char level_letter(LogLevel level)
{
  switch (level)
  {
    case LogLevel::Debug:   return 'D';
    case LogLevel::Info:    return 'I';
    case LogLevel::Warning: return 'W';
    case LogLevel::Error:   return 'E';
  }
  return '?';
}

static void uart_send(const char* data, int len)
{
  HAL_UART_Transmit(&huart2, reinterpret_cast<const uint8_t*>(data), len, HAL_MAX_DELAY);
}

void log_write(LogLevel level, const char* tag, const char* format, ...)
{
  if (level < LOG_MIN_LEVEL)
  {
    return;
  }

  // Reserve 2 bytes for "\r\n"
  const int size = sizeof(log_buffer) - 2;
  const uint32_t now = HAL_GetTick();

  int len = snprintf(log_buffer, size, "[%5lu.%03lu] %c %s: ",
                     now / 1000U, now % 1000U, level_letter(level), tag);

  va_list args;
  va_start(args, format);
  len += vsnprintf(log_buffer + len, size - len, format, args);
  va_end(args);

  // Message was cut off to fit the buffer
  if (len > size - 1)
  {
    len = size - 1;
  }

  log_buffer[len++] = '\r';
  log_buffer[len++] = '\n';
  uart_send(log_buffer, len);
}

// Overrides the weak _write() in syscalls.c, so plain printf() also goes to USART2
extern "C" int _write(int file, char* ptr, int len)
{
  (void)file;
  uart_send(ptr, len);
  return len;
}
