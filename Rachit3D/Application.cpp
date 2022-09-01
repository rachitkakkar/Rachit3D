#include "Entities/Mesh.h"
#include "Entities/Camera.h"

#include "Renderer/Renderer.h"
#include "Renderer/VertexBuffer.h"
#include "Renderer/IndexBuffer.h"
#include "Renderer/VertexBufferLayout.hpp"
#include "Renderer/VertexArray.h"
#include "Renderer/Shader.h"
#include "Renderer/Texture.h"

#include "Input/Window.h"
#include "Input/InputHandler.h"
#include "Input/TimeHandler.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

/* GLOBALS */
bool firstClick = true;
int width, height;

void HandleFPSCamera(Camera& camera, Window& window)
{
    InputHandler inputHandler;
    float speed = 0.08f;
    float sensitivity = 50.0f;

    window.GetDimensions(&width, &height);
    window.SetTitle("MESH DEMO, FOV: " + std::to_string(camera.GetFOV()));

    float ScrollOffset = inputHandler.GetScrollOffset(window) * 5.0f;

    camera.ChangeFOV(ScrollOffset);
    if (camera.GetFOV() > 179.0f)
        camera.SetFOV(179.0f);
    if (camera.GetFOV() < 1.0f)
        camera.SetFOV(1.0f);

    if (inputHandler.KeyHeld(window, GLFW_KEY_W))
        camera.MoveCameraPosition(camera.GetOrientation(), speed);

    if (inputHandler.KeyHeld(window, GLFW_KEY_S))
        camera.MoveCameraPosition(-camera.GetOrientation(), speed);

    if (inputHandler.KeyHeld(window, GLFW_KEY_A))
        camera.MoveCameraPosition(-glm::normalize(glm::cross(camera.GetOrientation(), camera.GetUp())), speed);

    if (inputHandler.KeyHeld(window, GLFW_KEY_D))
        camera.MoveCameraPosition(glm::normalize(glm::cross(camera.GetOrientation(), camera.GetUp())), speed);

    if (inputHandler.KeyHeld(window, GLFW_KEY_SPACE))
        camera.MoveCameraPosition(camera.GetUp(), speed);

    if (inputHandler.KeyHeld(window, GLFW_KEY_LEFT_SHIFT))
        camera.MoveCameraPosition(-camera.GetUp(), speed);

    if (inputHandler.LeftMouseButtonHeld(window))
    {
        inputHandler.SetMouseHidden(window);

        if (firstClick)
        {
            firstClick = false;
            inputHandler.SetMouseCoords(window, (float)(width / 2.0f), (float)(height / 2.0f));
        }

        float mouseX, mouseY;
        inputHandler.GetMouseCoords(window, mouseX, mouseY);

        float rotX = sensitivity * (float)(mouseY - (height / 2.0f)) / height;
        float rotY = sensitivity * (float)(mouseX - (width / 2.0f)) / width;

        camera.RotateCamera(glm::cross(camera.GetOrientation(), camera.GetUp()), -rotX);
        camera.RotateCamera(camera.GetUp(), -rotY);

        inputHandler.SetMouseCoords(window, (float)(width / 2.0f), (float)(height / 2.0f));
    }

    if (inputHandler.LeftMouseButtonReleased(window))
    {
        inputHandler.SetMouseVisible(window);
        firstClick = true;
    }

}

int main(void)
{
    {
        /* WINDOW CREATION */
        Window window(800, 600, "MESH DEMO");
        TimeHandler timeHandler;

        /* PIPELINE STATE */
        GLCall(glEnable(GL_DEPTH_TEST));

        //GLCall(glEnable(GL_CULL_FACE));
        //GLCall(glCullFace(GL_FRONT));
        //GLCall(glFrontFace(GL_CCW));

        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        /* MESH CREATION */
        std::vector<Vertex> vertices = {
            Vertex{glm::vec3(-1.0f, 0.0f,  1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f)},
            Vertex{glm::vec3(-1.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 1.0f)},
            Vertex{glm::vec3(1.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f)},
            Vertex{glm::vec3(1.0f, 0.0f,  1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f)}
        };

        std::vector<unsigned int> indices = {
            0, 1, 2,
            0, 2, 3
        };

        Texture texture("res/textures/brick.jpg");
        texture.Bind();

        Mesh mesh(vertices, indices);

        VertexArray va;
        VertexBuffer vb(mesh.GetVertices(), mesh.GetSizeOfVertices());
        IndexBuffer ib(mesh.GetIndices(), mesh.GetSizeOfVertices());
        Shader shader("res/shaders/basic3DColor.shader");

        VertexBufferLayout layout;
        layout.Push<float>(3);
        layout.Push<float>(3);
        layout.Push<float>(3);
        layout.Push<float>(2);
        va.AddBuffer(vb, layout);

        /* RENDER */
        Renderer renderer;
        Camera camera(glm::vec3(0.0f, 0.5f, 2.0f), glm::vec3(0.0f, 0.0f, -1.0f));

        shader.Bind();
        //shader.SetUniform1i("uTexture", 0);
        va.Bind();
        ib.Bind();

        while (window.IsRunning())
        {
            /* OBJECT HANDLING */
            HandleFPSCamera(camera, window);

            /* MVP */
            glm::mat4 model = glm::mat4(1.0f);
            glm::mat4 view = camera.GetViewMatrix();
            glm::mat4 projection = camera.GetProjMatrix(width, height);

            shader.SetUniformMat4f("uModel", model);
            shader.SetUniformMat4f("uView", view);
            shader.SetUniformMat4f("uProjection", projection);

            /* UPDATE */
            renderer.Clear();
            renderer.Draw(va, ib, shader);
            window.Update();
        }
    }

    return 0;
}