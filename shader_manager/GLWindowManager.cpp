#include "GLWindowManager.hpp"
#include "GLFW/glfw3.h"
#include "GLinitializer.hpp"
#include "shader_manger.hpp"
#include <cstdlib>
GLWindowManager::GLWindowManager() {
  if (GLEW_OK == glewInit()) {
    if (false == GL_Initializer::restart_gl_log())
      exit(1);
  } else {
    GL_Initializer::gl_log("window manager class failed to initialize glew");
    exit(1);
  }
};
GLFWwindow *GLWindowManager::createWindow(GLuint width, GLuint height,
                                          const GLchar *title) {
  GLFWwindow *window = glfwCreateWindow(width, height, title, nullptr, nullptr);
  if (nullptr != window) {
    windows.push_back(window);
  }
  return window;
}
GLFWwindow *GLWindowManager::createWindow(GLuint width, GLuint height,
                                          const GLchar *title,
                                          GLFWmonitor *monitor,
                                          GLFWwindow *share) {
  GLFWwindow *window = glfwCreateWindow(width, height, title, monitor, share);
  if (nullptr != window) {
    windows.push_back(window);
  }
  return window;
}
void GLWindowManager::destroyWindow(GLFWwindow *window) {
  auto iter = std::find(windows.begin(), windows.end(), window);
  if (iter != windows.end()) {
    glfwDestroyWindow(*iter);
    windows.erase(iter);
  }
}

GLFWwindow *GLWindowManager::findWindowbyTitle(const GLchar *title) noexcept {
  for (GLFWwindow *window : windows) {
    const char *_title = glfwGetWindowTitle(window);
    if (0 == _title && std::strcmp(_title, title) == 0) {
      return window;
    }
  }
  return nullptr;
}

GLFWwindow *GLWindowManager::getWindowAt(GLuint index) noexcept {
  if (index < windows.size()) {
    return windows[index];
  }
  return nullptr;
}
bool GLWindowManager::anyWindowHasLeftOpen() const noexcept {
  for (GLFWwindow *window : windows) {
    if (!glfwWindowShouldClose(window)) {
      return true;
    }
  }
  return false;
}

void GLWindowManager::pollEvents() noexcept { glfwPollEvents(); }
void GLWindowManager::swapBuffers(GLFWwindow *window) noexcept {
  glfwSwapBuffers(window);
}