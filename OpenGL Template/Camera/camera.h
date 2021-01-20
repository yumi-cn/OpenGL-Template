#pragma once
#include "../gl_template.h"

class CameraData : public Data {
public:
    unsigned int VBO, VAO;
    unsigned int texture1, texture2;

    CameraData();
    ~CameraData();

    void init_buffers();
    void init_textures();
};

class CameraShader : public Shader {
public:
    CameraShader();
    ~CameraShader();
};

class CameraRender : public Render {
public:
    CameraData data;
    CameraShader shader;
    int width, height;
    CameraRender(int w, int h);
    ~CameraRender();

    void run(GLFWwindow* window);

    void process_input(GLFWwindow *window);
};