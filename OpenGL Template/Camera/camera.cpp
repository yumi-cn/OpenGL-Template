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

float deltaTime = 0.0f; // 当前帧与上一帧的时间差
float lastFrame = 0.0f; // 上一帧的时间

float pitch = 0, yaw = -90;
float lastX = 400, lastY = 300;

bool firstMouse = true;

float fov = 45.0f;

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    // 这个bool变量初始时是设定为true的
    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    // 偏航角从-90度开始，鼠标向左移动，值变的更小
    // 视角要朝左旋转的话，就要更小的偏航角值
    // 所以直接加上 xpose - lastX即可
    float xoffset = xpos - lastX;
    // 而俯仰角是相反的，鼠标向上移动，值变的更小
    // 视角要朝上旋转的话，就要更大的俯仰角
    // 所以要反过来减两个坐标的差值
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
    // 其实还要重新计算Right和Up向量
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

        glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

        glm::mat4 projection = glm::mat4(1.0f);
        projection = glm::perspective(glm::radians(fov), (float)width / (float)height, 0.1f, 100.0f);
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

        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

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
void CameraRender::process_input(GLFWwindow *window) {
    float cameraSpeed = 2.5f * deltaTime;
    // 检查用户是否按下了返回键(Esc)，如果没有按下，glfwGetKey将会返回GLFW_RELEASE
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