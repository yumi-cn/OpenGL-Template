#include "program.h"

char vertex_shader[] = "CubeParty/shader.vs";
char fragment_shader[] = "CubeParty/shader.fs";
char texture_1_path[] = "CubeParty/container.jpg";
char texture_2_path[] = "CubeParty/awesomeface.png";

float vertices[] = {
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
    
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};

glm::vec3 positions[] = {
    glm::vec3(0.0f,  0.0f,  0.0f),
    glm::vec3(2.0f,  5.0f, -15.0f),
    glm::vec3(-1.5f, -2.2f, -2.5f),
    glm::vec3(-3.8f, -2.0f, -12.3f),
    glm::vec3(2.4f, -0.4f, -3.5f),
    glm::vec3(-1.7f,  3.0f, -7.5f),
    glm::vec3(1.3f, -2.0f, -2.5f),
    glm::vec3(1.5f,  2.0f, -2.5f),
    glm::vec3(1.5f,  0.2f, -1.5f),
    glm::vec3(-1.3f,  1.0f, -1.5f)
};


CubePartyData::CubePartyData() {
    init_buffers();
    init_textures();
};
CubePartyData::~CubePartyData() {
};
void CubePartyData::init_buffers() {
    // 创建顶点属性对象
    glGenVertexArrays(1, &VAO);
    // 创建顶点缓冲对象和索引缓冲对象
    glGenBuffers(1, &VBO);
    //glGenBuffers(1, &EBO);
    // 先绑定VAO，再绑定VBO，然后再配置顶点属性
    glBindVertexArray(VAO);
    // 绑定VBO到GL_ARRAY_BUFFER
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // 顶点数据复制到缓冲的内存中
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // 告诉OpenGL如何解析顶点数据
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    // 以顶点属性值作为参数，启动顶点属性
    glEnableVertexAttribArray(0);
    // 告诉OpenGL如何解析顶点数据
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    // 以顶点属性值作为参数，启动顶点属性
    glEnableVertexAttribArray(1);

    // 先解绑VAO
    glBindVertexArray(0);
    // 解绑VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
void CubePartyData::init_textures() {
    texture1 = get_texture(texture_1_path);
    texture2 = get_texture(texture_2_path);
}


CubePartyShader::CubePartyShader() : Shader(vertex_shader, fragment_shader) {};
CubePartyShader::~CubePartyShader() {};


CubePartyRender::CubePartyRender(int w, int h) : width(w), height(h) {};
CubePartyRender::~CubePartyRender() {};

void CubePartyRender::run(GLFWwindow* window) {

    // 告诉OpenGL渲染窗口的尺寸大小, 视口 Viewport
    // 窗口左下角的位置，宽度，高度
    glViewport(0, 0, width, height);

    // set 之前记得要use
    shader.use();
    shader.setInt("texture1", 0);
    shader.setInt("texture2", 1);

    // 开启深度测试
    glEnable(GL_DEPTH_TEST);

    while (!glfwWindowShouldClose(window)) {
        process_input(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 view = glm::mat4(1.0f);
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
        glm::mat4 projection = glm::mat4(1.0f);
        projection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);
        shader.setMat4("view", view);
        shader.setMat4("projection", projection);

        shader.use();

        // 绑定纹理
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, data.texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, data.texture2);

        // 绑定VAO
        glBindVertexArray(data.VAO);

        for (unsigned int i = 0; i < 10; i++) {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, positions[i]);
            float angle = 20.0f * i;
            model = glm::rotate(model, (float)glfwGetTime() * glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            shader.setMat4("model", model);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        // 解绑VAO
        glBindVertexArray(0);
        // 解绑纹理
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, 0);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, 0);

        // glfwSwapBuffers函数会交换颜色缓冲
        // 它是一个储存着GLFW窗口每一个像素颜色值的大缓冲
        // 它在这一迭代中被用来绘制，并且将会作为输出显示在屏幕上。
        glfwSwapBuffers(window);

        // glfwPollEvents函数检查有没有触发什么事件
        // 比如键盘输入、鼠标移动、更新窗口状态等
        // 并调用对应的回调函数（可以通过回调方法手动设置）
        glfwPollEvents();
    }
};

// 望能够在GLFW中实现一些输入控制，可以通过使用GLFW的几个输入函数来完成
// 使用GLFW的glfwGetKey函数，它需要一个窗口以及一个按键作为输入
// 这个函数将会返回这个按键是否正在被按下
void CubePartyRender::process_input(GLFWwindow *window) {
    // 检查用户是否按下了返回键(Esc)，如果没有按下，glfwGetKey将会返回GLFW_RELEASE
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}