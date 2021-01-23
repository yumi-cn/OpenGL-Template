#pragma once
#include <iostream>
// GLAD must be include before GLFW
// GL/GLES/EGL/GLX/WGL Loader-Generator based on the official specs.
#include <glad/glad.h>
// GLFW is an Open Source, multi-platform library for OpenGL, OpenGL ES and Vulkan application development.
// It provides a simple, platform-independent API for creating windows, contexts and surfaces, reading input, handling events, etc.
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <fstream>
#include <sstream>

class Data {
public:
    Data() {};
    ~Data() {};

    unsigned int get_texture(const char* texture_path,
        int WRAP_S = GL_REPEAT, int WRAP_T = GL_REPEAT,
        int MIN_FILTER = GL_LINEAR, int MAG_FILTER = GL_LINEAR,
        bool flip = true);
};

class Shader {
public:
    unsigned int ID;

    Shader() {};
    Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
    ~Shader() {};

    // 使用/激活程序
    void use();

    // uniform工具函数
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
    void setVec3(const std::string &name, glm::vec3 value) const;
    void setMat4(const std::string &name, glm::mat4 mat) const;
};

class Render {
public:
    Render() {};
    virtual ~Render() {};

    virtual void run(GLFWwindow* window) = 0;
};