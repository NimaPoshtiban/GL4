
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <array>
#include <cassert>
#include <cstdarg>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <sstream>
#define LOGGER_MESSAGE_SIZE 256
#undef GL_LOG_FILE
#define GL_LOG_FILE "gl.log"

extern "C" {
__declspec(dllexport) unsigned long NvOptimusEnablement = 0x00000001;
}

// ----------------------------shaders------------------------------
// moved into shaders folder
/*
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
*/
//------------------------------------------------------------------//

// tracking window size
GLint gl_window_width = 640;
GLint gl_window_hight = 460;

/********************************************************/

const GLchar *names[] = {
    "GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS",
    "GL_MAX_CUBE_MAP_TEXTURE_SIZE",
    "GL_MAX_DRAW_BUFFERS",
    "GL_MAX_FRAGMENT_UNIFORM_COMPONENTS",
    "GL_MAX_TEXTURE_IMAGE_UNITS",
    "GL_MAX_TEXTURE_SIZE",
    "GL_MAX_VARYING_FLOATS",
    "GL_MAX_VERTEX_ATTRIBS",
    "GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS",
    "GL_MAX_VERTEX_UNIFORM_COMPONENTS",
    "GL_MAX_VIEWPORT_DIMS",
    "GL_STEREO",
};
const GLenum params[] = {
    GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS,
    GL_MAX_CUBE_MAP_TEXTURE_SIZE,
    GL_MAX_DRAW_BUFFERS,
    GL_MAX_FRAGMENT_UNIFORM_COMPONENTS,
    GL_MAX_TEXTURE_IMAGE_UNITS,
    GL_MAX_TEXTURE_SIZE,
    GL_MAX_VARYING_FLOATS,
    GL_MAX_VERTEX_ATTRIBS,
    GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS,
    GL_MAX_VERTEX_UNIFORM_COMPONENTS,
    GL_MAX_VIEWPORT_DIMS,
    GL_STEREO,
};

/********************************************************/
std::string read_file(const char *filepath) noexcept {
  std::ifstream file(filepath, std::ios::in);
  if (file.is_open()) {
    std::stringstream buffer;
    buffer << file.rdbuf();
    file.close();
    return buffer.str();
  }
  std::fprintf(stderr, "Failed to open file: %s", filepath);
  exit(1);
}
/*-----------------------external functions-------------------------  */

[[nodiscard]] bool restart_gl_log() noexcept {
  std::FILE *file = std::fopen(GL_LOG_FILE, "w");
  if (NULL != file) {
    std::fprintf(file, "GL_LOG_FILE log.file:\n\rDate: %s Time: %s \r\n",
                 __DATE__, __TIME__);
    std::fclose(file);
    return true;
  }
  std::fprintf(stderr, "Error could not open %s", GL_LOG_FILE);
  return false;
}

bool gl_log(const char *message, ...) noexcept {
  std::FILE *file = std::fopen(GL_LOG_FILE, "a");
  if (NULL != file) {
    va_list args;
    va_start(args, message);
    std::vfprintf(file, message, args);
    va_end(args);
    std::fclose(file);
    return true;
  }
  std::fprintf(stderr, "Error could not open %s log file for appending \r\n",
               GL_LOG_FILE);
  return false;
}

void glfw_error_callback(const int error, const char *description) noexcept {
  gl_log("GLFW ERROR: code %i message: %s", error, description);
}

void glfw_window_size_callback(GLFWwindow *window, GLint width, GLint hight) {
  gl_window_width = width;
  gl_window_hight = hight;
}
void gl_log_info() noexcept {
  gl_log("GL context Parameters:\r\n\r");
  std::array<char, LOGGER_MESSAGE_SIZE> msg{};
  for (int i = 0; i < 10; ++i) {
    int value = 0;
    glGetIntegerv(params[i], &value);
    gl_log("%s %i\r\n", names[i], value);
  }
  std::array<int, 2> v{0, 0};
  glGetIntegerv(params[10], v.data());
  gl_log("%s %i %i\r\n", names[10], v.at(0), v.at(1));
  uint8_t check_param = 0;
  glGetBooleanv(params[11], &check_param);
  gl_log("%s %u\r\n", names[11], (uint32_t)(check_param));
  gl_log("%s\r\n", "--------------------------------------");
}
/**************** frame rate ***************/
static inline void _update_fps_counter(GLFWwindow *window) {
  static double previous_seconds = glfwGetTime();
  static int frame_count;
  double current_seconds = glfwGetTime();
  double elapsed_seconds = current_seconds - previous_seconds;
  if (0.25 < elapsed_seconds) {
    previous_seconds = current_seconds;
    double fps = (double)frame_count / elapsed_seconds;
    std::array<char, 128> tmp{};
    std::sprintf(tmp.data(), "OpenGL @ fps: %.2f", fps);
    glfwSetWindowTitle(window, tmp.data());
    frame_count = 0;
  }
  frame_count++;
}
/**********************/
/* --------------------------------------*/

int main(int argc, char *argv[]) {

  assert(restart_gl_log());

  gl_log("initializing GLFW\r\n\r%s\r\n", glfwGetVersionString());

  glfwSetErrorCallback(glfw_error_callback);

  if (!glfwInit()) {
    std::perror("OpenGL initialization failed");
    return 1;
  }

  const GLFWvidmode *mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

  glfwWindowHint(GLFW_RED_BITS, mode->redBits);
  glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
  glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
  glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
  glfwWindowHint(GLFW_SAMPLES, 4); // anti-aliasing
  GLFWwindow *window =
      glfwCreateWindow(640, 480, "Triangle with OPENGL4", NULL, nullptr);

  glfwMakeContextCurrent(window);

  GLenum err = glewInit();
  if (err != GLEW_OK) {
    std::fprintf(stderr, "GLEW initialization failed: %s\n",
                 glewGetErrorString(err));
    return 1;
  }

  if (!window) {
    std::perror("Window initialization failed");
    glfwTerminate();
    return 1;
  }

  glfwSetWindowSizeCallback(window, glfw_window_size_callback);
  gl_log_info();
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

  /****************Loading shaders from external files**********************/
  std::string vertex_src = read_file("shaders/simple.vert.glsl");
  std::string fragment_src = read_file("shaders/simple.frag.glsl");
  const char *vertexfile = vertex_src.c_str();
  const char *fragfile = fragment_src.c_str();

  GLuint vertexshader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexshader, 1, &vertexfile, nullptr);
  glCompileShader(vertexshader);
  GLuint fragmentshader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentshader, 1, &fragfile, nullptr);
  glCompileShader(fragmentshader);

  /*-------------- linking and attaching shaders --------------*/
  GLuint shader_program = glCreateProgram();

  glAttachShader(shader_program, vertexshader);
  glAttachShader(shader_program, fragmentshader);
  glLinkProgram(shader_program);

  /*----------drawing-----------*/
  while (!glfwWindowShouldClose(window)) {
    _update_fps_counter(window);
    // clear the surface
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glViewport(0, 0, gl_window_width, gl_window_hight); // scale window

    glUseProgram(shader_program);
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    // update other events
    glfwPollEvents();

    // display
    glfwSwapBuffers(window);
    if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_ESCAPE)) {
      glfwSetWindowShouldClose(window, 1);
    }
  }

  /* explicit cleanup (not needed most of the time) */
  glDeleteProgram(shader_program);
  glDeleteShader(vertexshader);
  glDeleteShader(fragmentshader);
  glDeleteVertexArrays(1, &vao);
  glDeleteBuffers(1, &vbo);

  glfwDestroyWindow(window);

  glfwTerminate();
  return 0;
}