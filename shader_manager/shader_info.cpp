#include "shader_info.hpp"
#include <array>
#include <cstdio>

void ShaderInfo::print_shader_log_info(GLuint shader_index) noexcept {
  int shader_size{};
  std::array<GLchar, 2048> log{};
  glGetShaderInfoLog(shader_index, 2048, &shader_size, &log[0]);
  std::printf("shader info log for GL index %u:\n%s\n", shader_index,
              log.data());
};
void ShaderInfo::print_programme_log_info(GLuint programme) noexcept {
  int shader_size{};
  std::array<GLchar, 2048> log{};
  glGetProgramInfoLog(programme, 2048, &shader_size, &log[0]);
  std::printf("program info log for GL index %u:\n%s", programme, log.data());
}

void ShaderInfo::print_all(GLuint programme) noexcept {
  std::printf("--------------------\nshader programme %i info:\n", programme);
  int params = -1;
  glGetProgramiv(programme, GL_LINK_STATUS, &params);
  std::printf("GL_LINK_STATUS = %i\n", params);
  glGetProgramiv(programme, GL_ATTACHED_SHADERS, &params);
  std::printf("GL_ATTACHED_SHADERS = %i\n", params);
  glGetProgramiv(programme, GL_ACTIVE_ATTRIBUTES, &params);
  std::printf("GL_ACTIVE_ATTRIBUTES = %i\n", params);
  for (GLuint i = 0; i < (GLuint)params; i++) {
    std::array<char, 64> name{};
    int max_length = 64;
    int actual_length = 0;
    int size = 0;
    GLenum type;
    glGetActiveAttrib(programme, i, max_length, &actual_length, &size, &type,
                      name.data());
    if (size > 1) {
      for (int j = 0; j < size; j++) {
        std::array<char, 64> long_name{};
        std::sprintf(long_name.data(), "%s[%i]", name.data(), j);
        int location = glGetAttribLocation(programme, long_name.data());
        std::printf(" %i) type:%s name:%s location:%i\n", i,
                    GL_type_to_string(type), long_name.data(), location);
      }
    } else {
      int location = glGetAttribLocation(programme, name.data());
      std::printf(" %i) type:%s name:%s location:%i\n", i,
                  GL_type_to_string(type), name.data(), location);
    }
  }
}

const char *ShaderInfo::GL_type_to_string(const GLenum type) noexcept {
  switch (type) {
  case GL_BOOL:
    return "bool";
  case GL_INT:
    return "int";
  case GL_FLOAT:
    return "float";
  case GL_FLOAT_VEC2:
    return "vec2";
  case GL_FLOAT_VEC3:
    return "vec3";
  case GL_FLOAT_VEC4:
    return "vec4";
  case GL_FLOAT_MAT2:
    return "mat2";
  case GL_FLOAT_MAT3:
    return "mat3";
  case GL_FLOAT_MAT4:
    return "mat4";
  case GL_SAMPLER_2D:
    return "sampler2D";
  case GL_SAMPLER_3D:
    return "sampler3D";
  case GL_SAMPLER_CUBE:
    return "samplerCube";
  case GL_SAMPLER_2D_SHADOW:
    return "sampler2DShadow";
  }
  return "other";
};
