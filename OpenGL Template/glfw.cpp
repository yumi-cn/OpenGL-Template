#include <iostream>
// GLAD must be include before GLFW
// GL/GLES/EGL/GLX/WGL Loader-Generator based on the official specs.
#include <glad/glad.h>
// GLFW is an Open Source, multi-platform library for OpenGL, OpenGL ES and Vulkan application development.
// It provides a simple, platform-independent API for creating windows, contexts and surfaces, reading input, handling events, etc.
#include <GLFW/glfw3.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

GLFWwindow* init_glfw(int width, int height) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // glfwCreateWindow(width, height, title, ..., ...)
    GLFWwindow* window = glfwCreateWindow(width, height, "OpenGL", NULL, NULL);
    if (window == nullptr) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return nullptr;
    }
    glfwMakeContextCurrent(window);
    // 当用户改变窗口的大小的时候，视口也应该被调整
    // 可以对窗口注册一个回调函数(Callback Function)
    // 它会在每次窗口大小被调整的时候被调用
    // void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    // 需要注册这个函数，告诉GLFW我们希望每当窗口调整大小的时候调用这个函数
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // GLAD是用来管理OpenGL的函数指针的
    // 所以在调用任何OpenGL的函数之前我们需要初始化GLAD
    // 给GLAD传入了用来加载系统相关的OpenGL函数指针地址的函数
    // GLFW给我们的是glfwGetProcAddress
    // 它根据我们编译的系统定义了正确的函数
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return nullptr;
    }
    
    return window;
}