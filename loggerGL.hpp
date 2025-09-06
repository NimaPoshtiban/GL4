#pragma once
#include <cstdint>
#include <string>
class LoggerGL {
public:
  std::uint8_t restart_gl_log() noexcept;
  std::uint8_t gl_log(std::string message, ...) noexcept;
  void glfw_error_callback(int error, const char *description);
  LoggerGL();
};