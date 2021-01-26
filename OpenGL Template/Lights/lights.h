#pragma once
#include "../gl_template.h"
#include "../cam.h"

class LightsData : public Data {
public:
    unsigned cube_VBO, cube_VAO;
    unsigned light_VBO, light_VAO;
    unsigned diffuse_texture;
    unsigned specular_texture;
    
    LightsData();
    ~LightsData();

    void init_buffers();
    void init_textures();
};

class LightsShader : public Shader {
public:
    LightsShader();
    LightsShader(const GLchar* vp, const GLchar* fp);
    ~LightsShader();
};

class LightsRender : public Render {
public:
    LightsData data;
    LightsShader shader, light_shader;
    int width, height;

    LightsRender(int w, int h);
    ~LightsRender();

    void run(GLFWwindow* window);
};