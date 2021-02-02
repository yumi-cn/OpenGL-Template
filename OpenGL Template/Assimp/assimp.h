#pragma once
#include "../gl_template.h"
#include "../cam.h"

class AssimpData : public Data {
public:
    unsigned cube_VBO, cube_VAO;
    unsigned light_VBO, light_VAO;
    unsigned diffuse_texture;
    unsigned specular_texture;
    
    AssimpData();
    ~AssimpData();

    void init_buffers();
    void init_textures();
};

class AssimpShader : public Shader {
public:
    AssimpShader();
    AssimpShader(const GLchar* vp, const GLchar* fp);
    ~AssimpShader();
};

class AssimpRender : public Render {
public:
    AssimpData data;
    AssimpShader shader, light_shader;
    int width, height;

    AssimpRender(int w, int h);
    ~AssimpRender();

    void run(GLFWwindow* window);
};