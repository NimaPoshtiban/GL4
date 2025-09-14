#pragma once
#include "shader_info.hpp"
#undef GL_WINDOW_MANAGER_HPP
#define GL_WINDOW_MANAGER_HPP
#include <GLFW/glfw3.h>
#include <vector>
class GLWindowManager {
public:
  explicit GLWindowManager();
  ~GLWindowManager();

  GLFWwindow *createWindow(GLuint width, GLuint height, const GLchar *title);
  GLFWwindow *createWindow(GLuint width, GLuint height, const GLchar *title,
                           GLFWmonitor *monitor, GLFWwindow *share);
  void destroyWindow(GLFWwindow *window);

  GLFWwindow *findWindowbyTitle(const GLchar *title) noexcept;
  GLFWwindow *getWindowAt(GLuint index) noexcept;

  /*
   *Event processing is not required for joystick input to work.
   *@Errors
   * GLFW_NOT_INITIALIZED and GLFW_PLATFORM_ERROR.
   *@Reentrancy
   * This function must not be called from a callback.
   *@Thread safety
   * This function must only be called from the main thread.
   *
   */
  void pollEvents() noexcept;

  /*
   * This function swaps the front and back buffers of the specified window
   * when rendering with OpenGL or OpenGL ES. If the swap interval is greater
   * than zero, the GPU driver waits the specified number of screen updates
   * before swapping the buffers. The specified window must have an OpenGL or
   * OpenGL ES context. Specifying a window without a context will generate a
   * GLFW_NO_WINDOW_CONTEXT error.
   *
   * This function does not apply to Vulkan
   */
  void swapBuffers(GLFWwindow *window) noexcept;

  bool anyWindowHasLeftOpen() const noexcept;

private:
  std::vector<GLFWwindow *> windows;
};