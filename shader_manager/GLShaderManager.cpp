// NOTE:
//  C style void cast only is used to show that function is void
//  C++ style void cast is used to discard the function value

#include "GLShaderManager.hpp"
#include "GLinitializer.hpp"
#include <fstream>
#include <sstream>

const bool GLShaderManager::validateProgramme(GLuint programme) noexcept {
  glValidateProgram(programme);
  int params = -1;
  glGetProgramiv(programme, GL_VALIDATE_STATUS, &params);
  if (params != GL_TRUE) {
    return false;
  }
  return true;
}

const char *GLShaderManager::GLTypeToString(const GLenum type) noexcept {
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

[[nodiscard]] GLuint
GLShaderManager::loadShaderFromFile(const char *filepath,
                                    GLenum shader_type) noexcept {
  std::ifstream file(filepath, std::ios::in);
  if (file.is_open()) {
    std::stringstream buffer;
    buffer << file.rdbuf();
    (void)file.close();
    auto shadertmp = buffer.str();
    const char *shaderfile = shadertmp.c_str();
    GLuint shader_handle = glCreateShader(shader_type);
    if (0 == shader_handle) {
      static_cast<void>(GL_Initializer::gl_log(
          "[Error] shader did not created\t ", __TIME__, "\n"));
      return 0;
    }
    (void)glShaderSource(shader_handle, 1, &shaderfile, nullptr);
    int shader_source_status{};
    (void)glGetShaderiv(shader_handle, GL_SHADER_SOURCE_LENGTH,
                        &shader_source_status);
    if (0 == shader_source_status) {
      static_cast<void>(GL_Initializer::gl_log(
          "[Error] shader source is empty\t ", __TIME__, "\n"));
      return 0;
    }
    int compile_status{};
    std::array<GLchar, MAX_COMPILE_LOG_LENGTH> compile_info{};

    if (GL_VERTEX_SHADER == shader_type) {
      (void)glCompileShader(shader_handle);
      (void)glGetShaderiv(shader_handle, GL_COMPILE_STATUS, &compile_status);
      if (compile_status == GL_TRUE) {
        static_cast<void>(GL_Initializer::gl_log(
            "[info] Vertex Shader compiled successfully\n"));
        (void)vertex_shaders_handle.push_back(shader_handle);
        return GL_TRUE;
      } else {
        (void)glGetShaderInfoLog(shader_handle, MAX_COMPILE_LOG_LENGTH, nullptr,
                                 &compile_info[0]);
        static_cast<void>(GL_Initializer::gl_log(
            "[Error] Vertex Shader did not compile at: ", __TIME__, "\r\n",
            compile_info.data(), "\n\r"));
        (void)glDeleteShader(shader_handle);
        return GL_INVALID_VALUE;
      }
    }

    if (GL_FRAGMENT_SHADER == shader_type) {
      (void)glCompileShader(shader_handle);
      (void)glGetShaderiv(shader_handle, GL_COMPILE_STATUS, &compile_status);
      if (compile_status == GL_TRUE) {
        static_cast<void>(GL_Initializer::gl_log(
            "[info] Fragment Shader compiled successfully\n"));
        (void)fragment_shaders_handle.push_back(shader_handle);
        return GL_TRUE;
      } else {
        (void)glGetShaderInfoLog(shader_handle, MAX_COMPILE_LOG_LENGTH, nullptr,
                                 &compile_info[0]);
        static_cast<void>(GL_Initializer::gl_log(
            "[Error] Fragment Shader did not compile at: ", __TIME__, "\r\n",
            compile_info.data(), "\n\r"));
        (void)glDeleteShader(shader_handle);
        return GL_INVALID_VALUE;
      }
    }
    if (GL_TESS_CONTROL_SHADER == shader_type) {
      (void)glCompileShader(shader_handle);
      (void)glGetShaderiv(shader_handle, GL_COMPILE_STATUS, &compile_status);
      if (compile_status == GL_TRUE) {
        static_cast<void>(GL_Initializer::gl_log(
            "[info] TESSCONTROL Shader compiled successfully\n"));
        (void)tes_control_shaders_handle.push_back(shader_handle);
        return GL_TRUE;
      } else {
        (void)glGetShaderInfoLog(shader_handle, MAX_COMPILE_LOG_LENGTH, nullptr,
                                 &compile_info[0]);
        static_cast<void>(GL_Initializer::gl_log(
            "[Error] TESSCONTROL Shader did not compile at: ", __TIME__, "\r\n",
            compile_info.data(), "\n\r"));
        (void)glDeleteShader(shader_handle);
        return GL_INVALID_VALUE;
      }
    }
    if (GL_TESS_EVALUATION_SHADER == shader_type) {
      (void)glCompileShader(shader_handle);
      (void)glGetShaderiv(shader_handle, GL_COMPILE_STATUS, &compile_status);
      if (compile_status == GL_TRUE) {
        static_cast<void>(GL_Initializer::gl_log(
            "[info] TESSEVALUATION Shader compiled successfully\n"));
        (void)tes_eval_shaders_handle.push_back(shader_handle);
        return GL_TRUE;
      } else {
        (void)glGetShaderInfoLog(shader_handle, MAX_COMPILE_LOG_LENGTH, nullptr,
                                 &compile_info[0]);
        static_cast<void>(GL_Initializer::gl_log(
            "[Error] TESSEVALUATION Shader did not compile at: ", __TIME__,
            "\r\n", compile_info.data(), "\n\r"));
        (void)glDeleteShader(shader_handle);
        return GL_INVALID_VALUE;
      }
    }
    if (GL_GEOMETRY_SHADER == shader_type) {
      (void)glCompileShader(shader_handle);
      (void)glGetShaderiv(shader_handle, GL_COMPILE_STATUS, &compile_status);
      if (compile_status == GL_TRUE) {
        static_cast<void>(GL_Initializer::gl_log(
            "[info] Geometry Shader compiled successfully\n"));
        (void)geometry_shaders_handle.push_back(shader_handle);
        return GL_TRUE;
      } else {
        (void)glGetShaderInfoLog(shader_handle, MAX_COMPILE_LOG_LENGTH, nullptr,
                                 &compile_info[0]);
        static_cast<void>(GL_Initializer::gl_log(
            "[Error] Geometry Shader did not compile at: ", __TIME__, "\r\n",
            compile_info.data(), "\n\r"));
        (void)glDeleteShader(shader_handle);
        return GL_INVALID_VALUE;
      }
    }
    if (GL_COMPUTE_SHADER == shader_type) {
      (void)glCompileShader(shader_handle);
      (void)glGetShaderiv(shader_handle, GL_COMPILE_STATUS, &compile_status);
      if (compile_status == GL_TRUE) {
        static_cast<void>(GL_Initializer::gl_log(
            "[info] Compute Shader compiled successfully\n"));
        (void)compute_shaders_handle.push_back(shader_handle);
        return GL_TRUE;
      } else {
        (void)glGetShaderInfoLog(shader_handle, MAX_COMPILE_LOG_LENGTH, nullptr,
                                 &compile_info[0]);
        static_cast<void>(GL_Initializer::gl_log(
            "[Error] Compute Shader did not compile at: ", __TIME__, "\r\n",
            compile_info.data(), "\n\r"));
        (void)glDeleteShader(shader_handle);
        return GL_INVALID_VALUE;
      }
    }
    (void)glDeleteShader(shader_handle);
    static_cast<void>(GL_Initializer::gl_log("[Error] Invalid shader type"));
    return GL_INVALID_ENUM;
  }
  return 0;
}
GLShaderManager::~GLShaderManager() {}
