#include <vector>

#pragma once
// since pragma might not be supported
#undef GLShaderManager_HPP
#define GLShaderManager_HPP
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#ifndef MAX_COMPILE_LOG_LENGTH
#define MAX_COMPILE_LOG_LENGTH 2048
#endif
class GLShaderManager {
public:
  const char *GLTypeToString(const GLenum type) noexcept;
  const bool validateProgram(GLuint programme) noexcept;

  /*
   * loads and compiles the specified shader
   * return codes:
   * failure:
   * `0 if shader file did not opened for reading shader`
   * `or if shader failed to create, or shader source is empty`
   * `GL_INVALID_VALUE if shader failed to compile`
   * `GL_INVALID_ENUM  if shader_type is invalid`
   *
   * success:
   * `GL_TRUE`
   */
  [[nodiscard]] GLuint loadShaderFromFile(const char *filepath,
                                          GLenum shader_type) noexcept;
  ~GLShaderManager();

private:
  std::vector<GLuint> vertex_shaders_handle;
  std::vector<GLuint> fragment_shaders_handle;
  std::vector<GLuint> geometry_shaders_handle;
  std::vector<GLuint> tes_control_shaders_handle;
  std::vector<GLuint> tes_eval_shaders_handle;
  std::vector<GLuint> compute_shaders_handle;
};