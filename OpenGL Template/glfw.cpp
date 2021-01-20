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
    // ���û��ı䴰�ڵĴ�С��ʱ���ӿ�ҲӦ�ñ�����
    // ���ԶԴ���ע��һ���ص�����(Callback Function)
    // ������ÿ�δ��ڴ�С��������ʱ�򱻵���
    // void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    // ��Ҫע���������������GLFW����ϣ��ÿ�����ڵ�����С��ʱ������������
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // GLAD����������OpenGL�ĺ���ָ���
    // �����ڵ����κ�OpenGL�ĺ���֮ǰ������Ҫ��ʼ��GLAD
    // ��GLAD��������������ϵͳ��ص�OpenGL����ָ���ַ�ĺ���
    // GLFW�����ǵ���glfwGetProcAddress
    // ���������Ǳ����ϵͳ��������ȷ�ĺ���
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return nullptr;
    }
    
    return window;
}