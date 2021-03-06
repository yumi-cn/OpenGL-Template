#pragma once
#include "../gl_template.h"
#include "../cam.h"

class LightData : public Data {
public:
    unsigned cube_VBO, cube_VAO;
    unsigned light_VBO, light_VAO;
    unsigned diffuse_texture;
    unsigned specular_texture;
    
    LightData();
    ~LightData();

    void init_buffers();
    void init_textures();
};

class LightShader : public Shader {
public:
    LightShader();
    LightShader(const GLchar* vp, const GLchar* fp);
    ~LightShader();
};

class LightRender : public Render {
public:
    LightData data;
    LightShader shader, light_shader;
    int width, height;

    LightRender(int w, int h);
    ~LightRender();

    void run(GLFWwindow* window);
};