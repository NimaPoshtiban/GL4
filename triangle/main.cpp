#include <GL/glew.h>
#include <gl/gl.h>

#include <GLFW/glfw3.h>
#include <cstdio>

extern "C" {
__declspec(dllexport) unsigned long NvOptimusEnablement = 0x00000001;
}

// ----------------------------shaders------------------------------
constexpr auto vertex_shader = "#version 400\n"
                               "in vec3 vp;"
                               "void main(){"
                               " gl_Position = vec4 (vp,1.0);"
                               "}";

constexpr auto fragment_shader = "#version 400\n"
                                 "out vec4 frag_color;"
                                 "void main() {"
                                 " frag_color = vec4 (0.5,0.0,0.5,1.0);"
                                 "}";

//------------------------------------------------------------------
int main(int argc, char *argv[]) {

  if (!glfwInit()) {
    std::perror("OpenGL initalization failed");
    return 1;
  }

  GLFWwindow *window =
      glfwCreateWindow(640, 480, "Triangle with OPENGL4", NULL, NULL);

  glfwMakeContextCurrent(window);

  GLenum err = glewInit();
  if (err != GLEW_OK) {
    std::fprintf(stderr, "GLEW init failed: %s\n", glewGetErrorString(err));
    return 1;
  }

  if (!window) {
    std::perror("Window initalization failed");
    glfwTerminate();
    return 1;
  }
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

  // [x y z]
  constexpr GLfloat points_xyz[] = {0.0f, 0.5f,  0.0f,  0.5f, -0.5f,
                                    0.0f, -0.5f, -0.5f, 0.0f};

  // Vertex buffer object
  GLuint vbo{};
  glGenBuffers(1, &vbo);

  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(points_xyz), points_xyz, GL_STATIC_DRAW);

  // vertex attribute object (VAO)
  GLuint vao{};
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);
  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

  // loading shaders
  GLuint vertexshader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexshader, 1, &vertex_shader, NULL);
  glCompileShader(vertexshader);
  GLuint fragmentshader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentshader, 1, &fragment_shader, NULL);
  glCompileShader(fragmentshader);

  // linking and attaching shaders
  GLuint shader_program = glCreateProgram();
  glAttachShader(shader_program, vertexshader);
  glAttachShader(shader_program, fragmentshader);
  glLinkProgram(shader_program);

  //----------drawing-----------
  while (!glfwWindowShouldClose(window)) {
    // clear the surface
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(shader_program);
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    // update other events
    glfwPollEvents();

    // display
    glfwSwapBuffers(window);
  }

  glfwTerminate();
  return 0;
}