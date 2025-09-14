#pragma once
#include <GL/glew.h>
#undef SHADER_INFO_HPP
#define SHADER_INFO_HPP

// class prototype
// will change a lot
// for now it will remain a simple class
class ShaderInfo {
public:
  explicit ShaderInfo();
  void print_shader_log_info(GLuint shader_index) noexcept;
  void print_programme_log_info(GLuint programme) noexcept;
  void print_all(GLuint programme) noexcept;
  const char *GL_type_to_string(const GLenum type) noexcept;

private:
};
