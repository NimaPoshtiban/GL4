#include "GLinitializer.hpp"
#include <cassert>
#include <cstdarg>
#include <cstdio>
#include <fstream>
#include <sstream>

template <typename T = const char *, typename... Ts>
[[nodiscard]] bool GL_Initializer::gl_log(T message, ...) noexcept {
  std::ofstream file(GL_LOG_FILE, std::ios::app | std::ios::in | std::ios::out |
                                      std::ios::binary);
  if (file.is_open()) {
    va_list args;
    va_start(args, message);
    file << "message: " << message;
    const char *str = message;

    while (nullptr != str) {
      str = va_arg(args, const char *);
      file << str;
    }
    va_end(args);
    file.close();
  }

  std::fprintf(stderr, "Error could not open %s log file for appending \r\n",
               GL_LOG_FILE);
  return false;
}
[[nodiscard]] bool GL_Initializer::restart_gl_log() noexcept {
  std::ofstream file(GL_LOG_FILE,
                     std::ios::trunc | std::ios::in | std::ios::out);
  if (file.is_open()) {
    std::stringstream buffer;
    buffer << "GL_LOG_FILE log.file:\n\rDate: " << __DATE__
           << " Time: " << __TIME__ << " \r\n";
    file.write(buffer.str().data(), buffer.gcount());
    file.close();
    buffer.flush();
    return true;
  }
  std::fprintf(stderr, "Error could not open %s", GL_LOG_FILE);
  return false;
}

void GL_Initializer::gl_log_info() noexcept {
  if (false == gl_log("GL context Parameters:\r\n\r")) {
    std::fprintf(stderr, "Logging context Parameters failed at: %s and line %d",
                 __TIME__, __LINE__);
  };
  std::array<char, LOGGER_MESSAGE_SIZE> msg{};
  for (int i = 0; i < 10; ++i) {
    int value = 0;
    glGetIntegerv(params[i], &value);
    if (false == gl_log("%s %i\r\n", names[i], value)) {
      std::fprintf(stderr,
                   "getting context Parameters failed at: %s and line %d",
                   __TIME__, __LINE__);
    }
  }
  std::array<int, 2> v{0, 0};
  glGetIntegerv(params[10], v.data());
  if (false == gl_log("%s %i %i\r\n", names[10], v.at(0), v.at(1))) {
    std::fprintf(stderr, "getting context Parameter failed at: %s and line %d",
                 __TIME__, __LINE__);
  }
  uint8_t check_param = 0;
  glGetBooleanv(params[11], &check_param);
  if (false == gl_log("%s %u\r\n", names[11], (uint32_t)(check_param))) {
    std::fprintf(stderr, "getting context Parameter failed at: %s and line %d",
                 __TIME__, __LINE__);
  }
  auto _ = gl_log("%s\r\n", "--------------------------------------");
}

GL_Initializer::GL_Initializer(
    [[maybe_unused]] const char *logFilePath) noexcept
    : logFilePath(logFilePath) {
  assert(true == this->restart_gl_log());
  if (false ==
      gl_log("initializing GLFW\r\n\r%s\r\n", glfwGetVersionString())) {
    exit(1);
  };
}
