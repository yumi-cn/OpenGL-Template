#include "camera.h"

char vertex_shader[] = "Camera/shader.vs";
char fragment_shader[] = "Camera/shader.fs";
char texture_1_path[] = "Camera/container.jpg";
char texture_2_path[] = "Camera/awesomeface.png";

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

glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
glm::vec3 cameraRight = glm::normalize(glm::cross(cameraFront, cameraUp));

float deltaTime = 0.0f; // ��ǰ֡����һ֡��ʱ���
float lastFrame = 0.0f; // ��һ֡��ʱ��

float pitch = 0, yaw = -90;
float lastX = 400, lastY = 300;

bool firstMouse = true;

float fov = 45.0f;

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    // ���bool������ʼʱ���趨Ϊtrue��
    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    // ƫ���Ǵ�-90�ȿ�ʼ����������ƶ���ֵ��ĸ�С
    // �ӽ�Ҫ������ת�Ļ�����Ҫ��С��ƫ����ֵ
    // ����ֱ�Ӽ��� xpose - lastX����
    float xoffset = xpos - lastX;
    // �����������෴�ģ���������ƶ���ֵ��ĸ�С
    // �ӽ�Ҫ������ת�Ļ�����Ҫ����ĸ�����
    // ����Ҫ����������������Ĳ�ֵ
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.05f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    if (pitch > 89.0f) {
        pitch = 89.0f;
    }
    if (pitch < -89.0f) {
        pitch = -89.0f;
    }

    glm::vec3 front;
    front.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
    front.y = sin(glm::radians(pitch));
    front.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
    cameraFront = glm::normalize(front);
    // ��ʵ��Ҫ���¼���Right��Up����
    cameraRight = glm::normalize(glm::cross(cameraFront, worldUp));
    cameraUp = glm::normalize(glm::cross(cameraRight, cameraFront));
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    if (fov >= 1.0f && fov <= 89.0f)
        fov -= yoffset;
    if (fov <= 1.0f)
        fov = 1.0f;
    if (fov >= 89.0f)
        fov = 89.0f;
}

CameraData::CameraData() {
    init_buffers();
    init_textures();
};
CameraData::~CameraData() {
};
void CameraData::init_buffers() {
    // �����������Զ���
    glGenVertexArrays(1, &VAO);
    // �������㻺�����������������
    glGenBuffers(1, &VBO);
    //glGenBuffers(1, &EBO);
    // �Ȱ�VAO���ٰ�VBO��Ȼ�������ö�������
    glBindVertexArray(VAO);
    // ��VBO��GL_ARRAY_BUFFER
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // �������ݸ��Ƶ�������ڴ���
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // ����OpenGL��ν�����������
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    // �Զ�������ֵ��Ϊ������������������
    glEnableVertexAttribArray(0);
    // ����OpenGL��ν�����������
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    // �Զ�������ֵ��Ϊ������������������
    glEnableVertexAttribArray(1);

    // �Ƚ��VAO
    glBindVertexArray(0);
    // ���VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
void CameraData::init_textures() {
    texture1 = get_texture(texture_1_path);
    texture2 = get_texture(texture_2_path);
}


CameraShader::CameraShader() : Shader(vertex_shader, fragment_shader) {};
CameraShader::~CameraShader() {};


CameraRender::CameraRender(int w, int h) : width(w), height(h) {};
CameraRender::~CameraRender() {};

void CameraRender::run(GLFWwindow* window) {

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // ����OpenGL��Ⱦ���ڵĳߴ��С, �ӿ� Viewport
    // �������½ǵ�λ�ã���ȣ��߶�
    glViewport(0, 0, width, height);

    // set ֮ǰ�ǵ�Ҫuse
    shader.use();
    shader.setInt("texture1", 0);
    shader.setInt("texture2", 1);

    // ������Ȳ���
    glEnable(GL_DEPTH_TEST);

    while (!glfwWindowShouldClose(window)) {
        process_input(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

        glm::mat4 projection = glm::mat4(1.0f);
        projection = glm::perspective(glm::radians(fov), (float)width / (float)height, 0.1f, 100.0f);
        shader.setMat4("view", view);
        shader.setMat4("projection", projection);

        shader.use();

        // ������
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, data.texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, data.texture2);

        // ��VAO
        glBindVertexArray(data.VAO);

        for (unsigned int i = 0; i < 10; i++) {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, positions[i]);
            float angle = 20.0f * i;
            model = glm::rotate(model, (float)glfwGetTime() * glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            shader.setMat4("model", model);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        // ���VAO
        glBindVertexArray(0);
        // �������
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, 0);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, 0);

        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

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

// ���ܹ���GLFW��ʵ��һЩ������ƣ�����ͨ��ʹ��GLFW�ļ������뺯�������
// ʹ��GLFW��glfwGetKey����������Ҫһ�������Լ�һ��������Ϊ����
// ����������᷵����������Ƿ����ڱ�����
void CameraRender::process_input(GLFWwindow *window) {
    float cameraSpeed = 2.5f * deltaTime;
    // ����û��Ƿ����˷��ؼ�(Esc)�����û�а��£�glfwGetKey���᷵��GLFW_RELEASE
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        cameraPos += cameraSpeed * cameraFront;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        cameraPos -= cameraSpeed * cameraFront;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        cameraPos -= cameraSpeed * cameraRight;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        cameraPos += cameraSpeed * cameraRight;
    }
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}