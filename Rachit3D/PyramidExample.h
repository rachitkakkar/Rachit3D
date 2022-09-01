#pragma once
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
    window.SetTitle("PYRADMID DEMO, FOV: " + std::to_string(camera.GetFOV()));

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
        Window window(800, 800, "PYRAMID DEMO");
        TimeHandler timeHandler;

        /* POSITIONS */
        float positions[] = {
            -0.5f, 0.0f,  0.5f,   	0.0f, 0.0f, 0.0f,   	0.0f, 0.0f,
            -0.5f, 0.0f, -0.5f,    	0.0f, 0.0f, 0.0f,   	5.0f, 0.0f,
             0.5f, 0.0f, -0.5f,    	0.0f, 0.0f, 0.0f,   	0.0f, 0.0f,
             0.5f, 0.0f,  0.5f,     0.0f, 0.0f, 0.0f,   	5.0f, 0.0f,
             0.0f, 0.8f,  0.0f,     0.0f, 0.0f, 0.0f,   	2.5f, 5.0f
        };

        unsigned int indices[] = {
            0, 2, 1,
            0, 3, 2,
            0, 1, 4,
            1, 2, 4,
            2, 3, 4,
            3, 0, 4,
        };

        /* VERTEX ARRAY & BUFFER */
        VertexArray va;
        VertexBuffer vb(positions, sizeof(positions));

        VertexBufferLayout layout;
        layout.Push<float>(3);
        layout.Push<float>(2);
        va.AddBuffer(vb, layout);

        /* INDEX BUFFER */
        IndexBuffer ib(indices, sizeof(indices));
        ib.Bind();
        
        /* SHADER */
        Shader shader("res/shaders/basic.shader");
        shader.Bind();
        
        /* TEXTURE */
        Texture texture("res/textures/brick.jpg");
        texture.Bind();

        shader.SetUniform1i("u_Texture", 0);

        /* RENDER */
        Renderer renderer;
        Camera camera(glm::vec3(0.0f, 0.5f, 2.0f), glm::vec3(0.0f, 0.0f, -1.0f));

        float rotation = 0.0f;

        while (window.IsRunning())
        {
            /* OBJECT HANDLING */
            rotation += 100.0f * timeHandler.GetDeltaTime();
            HandleFPSCamera(camera, window);

            /* MVP */
            glm::mat4 model = glm::rotate(glm::mat4(1.0f), glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));
            glm::mat4 view = camera.GetViewMatrix();
            glm::mat4 projection = camera.GetProjMatrix(width, height);

            shader.SetUniformMat4f("u_Model", model);
            shader.SetUniformMat4f("u_View", view);
            shader.SetUniformMat4f("u_Projection", projection);
            
            /* UPDATE */
            renderer.Clear();
            renderer.Draw(va, ib, shader);
            window.Update();
        }
    }

    return 0;
}