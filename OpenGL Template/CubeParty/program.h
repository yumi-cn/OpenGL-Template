#pragma once
#include "../gl_template.h"

class CubePartyData : public Data {
public:
    unsigned int VBO, VAO;
    unsigned int texture1, texture2;

    CubePartyData();
    ~CubePartyData();

    void init_buffers();
    void init_textures();
};

class CubePartyShader : public Shader {
public:
    CubePartyShader();
    ~CubePartyShader();
};

class CubePartyRender : public Render {
public:
    CubePartyData data;
    CubePartyShader shader;
    int width, height;
    CubePartyRender(int w, int h);
    ~CubePartyRender();

    void run(GLFWwindow* window);

    void process_input(GLFWwindow *window);
};