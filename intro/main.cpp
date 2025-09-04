#include <GL/glew.h>
#define GLFW_DLL
#include <GLFW/glfw3.h>
#include <cstdio>

int main(int argc, char *argv[]) {
  if (!glfwInit()) {
    std::perror("OpenGL initalization failed");
    return 1;
  }

  GLFWwindow *window =
      glfwCreateWindow(640, 480, "testing... OPENGL !", NULL, NULL);
  if (!window) {
    std::perror("Window initalization failed");
    glfwTerminate();
    glfwMakeContextCurrent(window);
    return 1;
  }
  const GLubyte *renderer = glGetString(GL_RENDERER);
  const GLubyte *version = glGetString(GL_VERSION);
  std::printf("Renderer: %s\n", renderer);
  std::printf("OpenGL version supported %s\n", version);

  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
  std::getchar();

  glfwTerminate();
  return 0;
}