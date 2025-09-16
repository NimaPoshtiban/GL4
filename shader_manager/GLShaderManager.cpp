// NOTE:
//  C style void cast only is used to show that function is void
//  C++ style void cast is used to discard the function value

#include "GLShaderManager.hpp"
#include "GLinitializer.hpp"
#include <fstream>
#include <sstream>

const bool GLShaderManager::validateProgram(GLuint programme) noexcept {
  glValidateProgram(programme);
  int params = -1;
  glGetProgramiv(programme, GL_VALIDATE_STATUS, &params);
  if (params != GL_TRUE) {
    return false;
  }
  return true;
}

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
          "[Error] shader did not created\t ", __TIME__, "\r\n"));
      return 0;
    }
    (void)glShaderSource(shader_handle, 1, &shaderfile, nullptr);
    int shader_source_status{};
    (void)glGetShaderiv(shader_handle, GL_SHADER_SOURCE_LENGTH,
                        &shader_source_status);
    if (0 == shader_source_status) {
      static_cast<void>(GL_Initializer::gl_log(
          "[Error] shader source is empty\t ", __TIME__, "\r\n"));
      return 0;
    }
    int compile_status{};
    std::array<GLchar, MAX_COMPILE_LOG_LENGTH> compile_info{};

    if (GL_VERTEX_SHADER == shader_type) {
      (void)glCompileShader(shader_handle);
      (void)glGetShaderiv(shader_handle, GL_COMPILE_STATUS, &compile_status);
      if (compile_status == GL_TRUE) {
        static_cast<void>(GL_Initializer::gl_log(
            "[info] Vertex Shader compiled successfully\r\n"));
        (void)vertex_shaders_handle.push_back(shader_handle);
        return GL_TRUE;
      } else {
        (void)glGetShaderInfoLog(shader_handle, MAX_COMPILE_LOG_LENGTH, nullptr,
                                 &compile_info[0]);
        static_cast<void>(GL_Initializer::gl_log(
            "[Error] Vertex Shader did not compile at: ", __TIME__, "\r\n",
            compile_info.data(), "\r\n"));
        (void)glDeleteShader(shader_handle);
        return GL_INVALID_VALUE;
      }
    }

    if (GL_FRAGMENT_SHADER == shader_type) {
      (void)glCompileShader(shader_handle);
      (void)glGetShaderiv(shader_handle, GL_COMPILE_STATUS, &compile_status);
      if (compile_status == GL_TRUE) {
        static_cast<void>(GL_Initializer::gl_log(
            "[info] Fragment Shader compiled successfully\r\n"));
        (void)fragment_shaders_handle.push_back(shader_handle);
        return GL_TRUE;
      } else {
        (void)glGetShaderInfoLog(shader_handle, MAX_COMPILE_LOG_LENGTH, nullptr,
                                 &compile_info[0]);
        static_cast<void>(GL_Initializer::gl_log(
            "[Error] Fragment Shader did not compile at: ", __TIME__, "\r\n",
            compile_info.data(), "\r\n"));
        (void)glDeleteShader(shader_handle);
        return GL_INVALID_VALUE;
      }
    }
    if (GL_TESS_CONTROL_SHADER == shader_type) {
      (void)glCompileShader(shader_handle);
      (void)glGetShaderiv(shader_handle, GL_COMPILE_STATUS, &compile_status);
      if (compile_status == GL_TRUE) {
        static_cast<void>(GL_Initializer::gl_log(
            "[info] TESSCONTROL Shader compiled successfully\r\n"));
        (void)tes_control_shaders_handle.push_back(shader_handle);
        return GL_TRUE;
      } else {
        (void)glGetShaderInfoLog(shader_handle, MAX_COMPILE_LOG_LENGTH, nullptr,
                                 &compile_info[0]);
        static_cast<void>(GL_Initializer::gl_log(
            "[Error] TESSCONTROL Shader did not compile at: ", __TIME__, "\r\n",
            compile_info.data(), "\r\n"));
        (void)glDeleteShader(shader_handle);
        return GL_INVALID_VALUE;
      }
    }
    if (GL_TESS_EVALUATION_SHADER == shader_type) {
      (void)glCompileShader(shader_handle);
      (void)glGetShaderiv(shader_handle, GL_COMPILE_STATUS, &compile_status);
      if (compile_status == GL_TRUE) {
        static_cast<void>(GL_Initializer::gl_log(
            "[info] TESSEVALUATION Shader compiled successfully\r\n"));
        (void)tes_eval_shaders_handle.push_back(shader_handle);
        return GL_TRUE;
      } else {
        (void)glGetShaderInfoLog(shader_handle, MAX_COMPILE_LOG_LENGTH, nullptr,
                                 &compile_info[0]);
        static_cast<void>(GL_Initializer::gl_log(
            "[Error] TESSEVALUATION Shader did not compile at: ", __TIME__,
            "\r\n", compile_info.data(), "\r\n"));
        (void)glDeleteShader(shader_handle);
        return GL_INVALID_VALUE;
      }
    }
    if (GL_GEOMETRY_SHADER == shader_type) {
      (void)glCompileShader(shader_handle);
      (void)glGetShaderiv(shader_handle, GL_COMPILE_STATUS, &compile_status);
      if (compile_status == GL_TRUE) {
        static_cast<void>(GL_Initializer::gl_log(
            "[info] Geometry Shader compiled successfully\r\n"));
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
            "[info] Compute Shader compiled successfully\r\n"));
        (void)compute_shaders_handle.push_back(shader_handle);
        return GL_TRUE;
      } else {
        (void)glGetShaderInfoLog(shader_handle, MAX_COMPILE_LOG_LENGTH, nullptr,
                                 &compile_info[0]);
        static_cast<void>(GL_Initializer::gl_log(
            "[Error] Compute Shader did not compile at: ", __TIME__, "\r\n",
            compile_info.data(), "\r\n"));
        (void)glDeleteShader(shader_handle);
        return GL_INVALID_VALUE;
      }
    }
    (void)glDeleteShader(shader_handle);
    static_cast<void>(
        GL_Initializer::gl_log("[Error] Invalid shader type\r\n"));
    return GL_INVALID_ENUM;
  }
  return 0;
}

void GLShaderManager::createProgram() noexcept {
  this->program_handle = glCreateProgram();
  if (0 == this->program_handle) {
    static_cast<void>(GL_Initializer::gl_log(
        "[Error] ", "Shader Program did not created ", __TIME__, "\r\n"));
  }
  static_cast<void>(GL_Initializer::gl_log("[Info] ", "Shader Program created ",
                                           __TIME__, "\r\n"));
}

[[nodiscard]] GLuint GLShaderManager::attachShaders() noexcept {
  if (0 == this->program_handle) {
    static_cast<void>(
        GL_Initializer::gl_log("[Error] ",
                               "No Program exist, a first a program must be "
                               "created before attaching shaders ",
                               __TIME__, "\r\n"));
    return 0;
  }
  for (GLuint &vert_shader : this->vertex_shaders_handle) {
    (void)glAttachShader(this->program_handle, vert_shader);
  }
  for (GLuint &frag_shader : this->fragment_shaders_handle) {
    (void)glAttachShader(this->program_handle, frag_shader);
  }
  for (GLuint &geo_shader : this->geometry_shaders_handle) {
    (void)glAttachShader(this->program_handle, geo_shader);
  }
  for (GLuint &control_shader : this->tes_control_shaders_handle) {
    (void)glAttachShader(this->program_handle, control_shader);
  }
  for (GLuint &eval_shader : this->tes_eval_shaders_handle) {
    (void)glAttachShader(this->program_handle, eval_shader);
  }
  for (GLuint &compute_shader : this->compute_shaders_handle) {
    (void)glAttachShader(this->program_handle, compute_shader);
  }
  int shaders_attached_count;
  (void)glGetProgramiv(this->program_handle, GL_ATTACHED_SHADERS,
                       &shaders_attached_count);
  if (0 != shaders_attached_count) {
    static_cast<void>(GL_Initializer::gl_log(
        "[Info] ", "All shaders have been attached to the program ", __TIME__,
        "\r\n"));
    return static_cast<GLuint>(shaders_attached_count);
  }
  static_cast<void>(GL_Initializer::gl_log(
      "[ERROR] ", "No shader has been attached ", __TIME__, "\r\n"));
  return 0;
};

void GLShaderManager::linkProgram() noexcept {
  if (0 == this->program_handle) {
    static_cast<void>(GL_Initializer::gl_log("[ERROR] ", "No Program exists ",
                                             __TIME__, "\r\n"));
  }
  (void)glLinkProgram(this->program_handle);
  int link_status;
  (void)glGetProgramiv(this->program_handle, GL_LINK_STATUS, &link_status);
  if (link_status == GL_TRUE) {
    static_cast<void>(GL_Initializer::gl_log(
        "[Info] ", "Program was linked without an error ", __TIME__, "\r\n"));
  } else {
    static_cast<void>(GL_Initializer::gl_log(
        "[Error] ", "Program did not linked ", __TIME__, "\r\n"));
  }
}

GLShaderManager::~GLShaderManager() {
  for (GLuint &vert_shader : this->vertex_shaders_handle) {
    (void)glDeleteShader(vert_shader);
  }
  for (GLuint &frag_shader : this->fragment_shaders_handle) {
    (void)glDeleteShader(frag_shader);
  }
  for (GLuint &geo_shader : this->geometry_shaders_handle) {
    (void)glDeleteShader(geo_shader);
  }
  for (GLuint &control_shader : this->tes_control_shaders_handle) {
    (void)glDeleteShader(control_shader);
  }
  for (GLuint &eval_shader : this->tes_eval_shaders_handle) {
    (void)glDeleteShader(eval_shader);
  }
  for (GLuint &compute_shader : this->compute_shaders_handle) {
    (void)glDeleteShader(compute_shader);
  }

  (void)glDeleteProgram(this->program_handle);
}
