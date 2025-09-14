#undef GLinitializer
#define GLinitializer
#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <array>

#define GL_LOG_FILE "gl.log"
#define LOGGER_MESSAGE_SIZE 256
// this class is way too general
// we need a window manager class
class GL_Initializer {
public:
  explicit GL_Initializer(
      [[maybe_unused]] const char *logFilePath = GL_LOG_FILE) noexcept;

  static void gl_log_info() noexcept;
  template <typename T, typename... Ts>
  static bool gl_log(T message, ...) noexcept;
  [[nodiscard]] static bool restart_gl_log() noexcept;

private:
  const char *logFilePath = GL_LOG_FILE;

  inline static const std::array<const GLchar *, 12> names = {
      "GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS",
      "GL_MAX_CUBE_MAP_TEXTURE_SIZE",
      "GL_MAX_DRAW_BUFFERS",
      "GL_MAX_FRAGMENT_UNIFORM_COMPONENTS",
      "GL_MAX_TEXTURE_IMAGE_UNITS",
      "GL_MAX_TEXTURE_SIZE",
      "GL_MAX_VARYING_FLOATS",
      "GL_MAX_VERTEX_ATTRIBS",
      "GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS",
      "GL_MAX_VERTEX_UNIFORM_COMPONENTS",
      "GL_MAX_VIEWPORT_DIMS",
      "GL_STEREO",
  };
  inline static const std::array<GLenum, 12> params = {
      GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS,
      GL_MAX_CUBE_MAP_TEXTURE_SIZE,
      GL_MAX_DRAW_BUFFERS,
      GL_MAX_FRAGMENT_UNIFORM_COMPONENTS,
      GL_MAX_TEXTURE_IMAGE_UNITS,
      GL_MAX_TEXTURE_SIZE,
      GL_MAX_VARYING_FLOATS,
      GL_MAX_VERTEX_ATTRIBS,
      GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS,
      GL_MAX_VERTEX_UNIFORM_COMPONENTS,
      GL_MAX_VIEWPORT_DIMS,
      GL_STEREO,
  };
};