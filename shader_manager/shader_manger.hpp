#pragma once
#include <GL/glew.h>
#undef SHADER_MNG_HPP
#define SHADER_MNG_HPP

// class prototype
// will change a lot
// for now it will remain a simple class
class ShaderManager {
public:
  explicit ShaderManager();
  static void print_shader_log_info(GLuint shader_index) noexcept;
  static void print_programme_log_info(GLuint programme) noexcept;
  static void print_all(GLuint programme) noexcept;
  static const char *GL_type_to_string(const GLenum type) noexcept;
  static const bool is_programme_valid(GLuint programme) noexcept;

private:
};
