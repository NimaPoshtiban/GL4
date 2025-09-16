

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
  // the memory managment will be handled automatically
  // deallocation accurs when the object instance goes out of scope
  GLShaderManager() = default;
  GLShaderManager(GLShaderManager &) = delete;
  GLShaderManager(GLShaderManager &&) = default;
  ~GLShaderManager();

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

  /*
   * creates an empty program
   */
  void createProgram() noexcept;

  /*
   * all shaders will be attached to the `program_handle`
   * `non-zero value indicate success`
   * `0 is returned if any error has happen`
   * returns the number of attached shaders
   */

  [[nodiscard]] GLuint attachShaders() noexcept;

  void linkProgram() noexcept;

  GLuint program_handle;
  std::vector<GLuint> vertex_shaders_handle;
  std::vector<GLuint> fragment_shaders_handle;
  std::vector<GLuint> geometry_shaders_handle;
  std::vector<GLuint> tes_control_shaders_handle;
  std::vector<GLuint> tes_eval_shaders_handle;
  std::vector<GLuint> compute_shaders_handle;
};