//#include "CubeParty/program.h"
//#include "Camera/camera.h"
#include "Light/light.h"

extern GLFWwindow* init_glfw(int width, int height);

int main() {
    int width = 800, height = 600;

    // GLFW≥ı ºªØ
    GLFWwindow* window = init_glfw(width, height);
    if (!window) {
        std::cout << "Failed to initialize window." << std::endl;
        return -1;
    }

    //CubePartyRender render(width, height);
    //CameraRender render(width, height);
    LightRender render(width, height);
    render.run(window);

    glfwTerminate();
    return 0;
}