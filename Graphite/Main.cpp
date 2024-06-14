#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Textures/Textures.h"
#include "Shaders/Shader.h"
#include "Textures/stb_image.h"
#include "Camera/Camera.h"
#include "Objects/VertexBufferObject.h"
#include "Objects/VertexArrayObject.h"
#include "Objects/ElementBufferObject.h"
#include "Primitives/3D/Cube.h"
#include "Utils/Deltatime/DeltaTime.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);
void glfwInitWindow();

// settings
const float SCR_WIDTH = 800.0f;
const float SCR_HEIGHT = 600.0f;

// Camera
Camera camera(SCR_WIDTH / 2.0, SCR_HEIGHT / 2.0, glm::vec3(0.0f, 0.0f, 3.0f));

DeltaTime deltaTime = DeltaTime();

int main()
{
    glfwInitWindow();

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Graphite", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    ShaderSource shaderSource = Shader::ParseShaders("Shaders/Vertex/BasicVertex.shader", "Shaders/Fragment/BasicFragment.shader");
    Shader shaderProgram = Shader(shaderSource);

    Texture2D containerTexture = Texture2D("Textures/Images/container.jpg");
    Texture2D faceTexture = Texture2D("Textures/Images/awesomeface.png");

    Cube cube = Cube();

    glEnable(GL_DEPTH_TEST);
    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        deltaTime.UpdateDeltaTime(glfwGetTime());

        // input
        processInput(window);

        // render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 projection;
        projection = glm::perspective(glm::radians(camera.GetZoom()), 800.0f / 600.0f, 0.1f, 100.0f);

        shaderProgram.Bind();
        shaderProgram.SetUniform1i("texture1", 0);
        shaderProgram.SetUniform1i("texture2", 1);

        // camera/view transformation
        glm::mat4 view = camera.GetViewMatrix();

        shaderProgram.SetUniformMatrix4fv("view", view);
        shaderProgram.SetUniformMatrix4fv("projection", projection);

        containerTexture.Bind(0);
        faceTexture.Bind(1);

        cube.Bind();
        shaderProgram.SetUniformMatrix4fv("model", cube.GetModelMatrix());
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        cube.Unbind();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        camera.ProcessKeyboard(FORWARD, deltaTime.GetDeltaTime());
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        camera.ProcessKeyboard(BACKWARD, deltaTime.GetDeltaTime());
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        camera.ProcessKeyboard(LEFT, deltaTime.GetDeltaTime());
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        camera.ProcessKeyboard(RIGHT, deltaTime.GetDeltaTime());
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
    {
        camera.ProcessKeyboard(DOWN, deltaTime.GetDeltaTime());
    }
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
    {
        camera.ProcessKeyboard(UP, deltaTime.GetDeltaTime());
    }
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (camera.IsFirstMouse())
    {
        camera.SetLastX(xpos);
        camera.SetLastY(ypos);
        camera.SetFirstMouse(false);
    }

    float xoffset = xpos - camera.GetLastX();
    float yoffset = camera.GetLastY() - ypos; // reversed since y-coordinates go from bottom to top

    camera.SetLastX(xpos);
    camera.SetLastY(ypos);

    camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}

void glfwInitWindow()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwSwapInterval(1);
}
