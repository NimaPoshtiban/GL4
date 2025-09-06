#include "loggerGL.hpp"
#include <cassert>
#include <cstdarg>
#include <fstream>
#include <iostream>

LoggerGL::LoggerGL() { assert(LoggerGL::restart_gl_log()); }

std::uint8_t LoggerGL::gl_log(std::string message, ...) noexcept {
  std::fstream file{GL_LOG_FILE};
  if (file.is_open()) {
    va_list args;
    va_start(args, message);
    file << "\r\n";
    file << message << args;
    va_end(args);
    file << "\r\n";
    file.close();
    return true;
  }
  std::cerr << "Error could not open " << GL_LOG_FILE << " log file";
  return false;
}
void LoggerGL::glfw_error_callback(int error, const char *description) {
  LoggerGL::gl_log("GLFW ERROR: code ", error, "  message: ", description);
}
