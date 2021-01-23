#include "light.h"

void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void process_input(GLFWwindow *window);

char vertex_shader[] = "Light/shader.vs";
char fragment_shader[] = "Light/shader.fs";
char light_fragment_shader[] = "Light/lshader.fs";

float vertices[] = {
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
};

// camera
Camera camera(glm::vec3(0.0f, 1.0f, 4.0f));
float lastX = 0.0f;
float lastY = 0.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

glm::vec3 cube_pos(0.0f, 0.0f, 0.0f);
glm::vec3 light_pos(1.2f, 1.0f, 2.0f);

LightData::LightData() {
    init_buffers();
};
LightData::~LightData() {
    glDeleteVertexArrays(1, &cube_VAO);
    glDeleteVertexArrays(1, &light_VAO);
    glDeleteBuffers(1, &cube_VBO);
    glDeleteBuffers(1, &light_VBO);
};
void LightData::init_buffers() {
    // �ȳ�ʼ��Cube VAO VBO
    glGenVertexArrays(1, &cube_VAO);
    glGenBuffers(1, &cube_VBO);

    glBindVertexArray(cube_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, cube_VBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    // �ٳ�ʼ��Light VAO VBO
    glGenVertexArrays(1, &light_VAO);
    glGenBuffers(1, &light_VBO);

    glBindVertexArray(light_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, light_VBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

LightShader::LightShader() {};
LightShader::LightShader(const GLchar* vp, const GLchar* fp) : Shader(vp, fp) {};
LightShader::~LightShader() {};

LightRender::LightRender(int w, int h) : width(w), height(h) {
    shader = LightShader(vertex_shader, fragment_shader);
    light_shader = LightShader(vertex_shader, light_fragment_shader);
};

LightRender::~LightRender() {

};

void LightRender::run(GLFWwindow* window) {

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // ����OpenGL��Ⱦ���ڵĳߴ��С, �ӿ� Viewport
    // �������½ǵ�λ�ã���ȣ��߶�
    glViewport(0, 0, width, height);

    // ������Ȳ���
    glEnable(GL_DEPTH_TEST);

    while (!glfwWindowShouldClose(window)) {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        process_input(window);

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // set ֮ǰ�ǵ�Ҫuse
        shader.use();
        shader.setVec3("objectColor", glm::vec3(1.0f, 0.5f, 0.31f));
        shader.setVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
        shader.setVec3("lightPos", light_pos);

        glm::mat4 view = camera.GetViewMatrix();

        glm::mat4 projection = glm::mat4(1.0f);
        projection = glm::perspective(glm::radians(camera.Zoom), (float)width / (float)height, 0.1f, 100.0f);
        shader.setMat4("view", view);
        shader.setMat4("projection", projection);

        glm::mat4 model = glm::mat4(1.0f);
        shader.setMat4("model", model);

        // ��VAO
        glBindVertexArray(data.cube_VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        // ���VAO
        glBindVertexArray(0);

        light_shader.use();
        light_shader.setMat4("view", view);
        light_shader.setMat4("projection", projection);
        model = glm::mat4(1.0f);
        model = glm::translate(model, light_pos);
        model = glm::scale(model, glm::vec3(0.2f)); // a smaller cube
        light_shader.setMat4("model", model);

        // ��VAO
        glBindVertexArray(data.light_VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        // ���VAO
        glBindVertexArray(0);

        // glfwSwapBuffers�����ύ����ɫ����
        // ����һ��������GLFW����ÿһ��������ɫֵ�Ĵ󻺳�
        // ������һ�����б��������ƣ����ҽ�����Ϊ�����ʾ����Ļ�ϡ�
        glfwSwapBuffers(window);

        // glfwPollEvents���������û�д���ʲô�¼�
        // ����������롢����ƶ������´���״̬��
        // �����ö�Ӧ�Ļص�����������ͨ���ص������ֶ����ã�
        glfwPollEvents();
    }
};

void process_input(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    camera.ProcessMouseScroll(yoffset);
}