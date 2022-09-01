#include "Window.h"

#include <iostream>

void Resize(GLFWwindow* window, int width, int height)
{
    GLCall(glViewport(0, 0, width, height));
}

static float scrollOffset; // Global For Storing ScrollWheel, A Hack Since There Is No Function To Get ScrollWheel Without A Callback
void ScrollWheel(GLFWwindow* window, double xOffset, double yOffset)
{
    scrollOffset = (float)yOffset;
}

Window::Window(int width, int height, std::string title)
	: m_Width(width), m_Height(height), m_Title(title), m_Window(nullptr)
{
    if (!glfwInit()) {
        std::cerr << "GLFW FAILED TO INIT" << std::endl;
        return;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    m_Window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);

    if (!m_Window)
    {
        std::cerr << "WINDOW CREATION FAILED" << std::endl;
        glfwTerminate();
        return;
    }

    glfwSetFramebufferSizeCallback(m_Window, Resize);
    glfwSetScrollCallback(m_Window, ScrollWheel);
    glfwMakeContextCurrent(m_Window);

    if (!glewInit() == GLEW_OK) {
        std::cerr << "GLEW FAILED TO INIT" << std::endl;
        return;
    }

    glfwSwapInterval(1);
}

Window::~Window()
{
    glfwDestroyWindow(m_Window);
    glfwTerminate();
}

bool Window::IsRunning() const
{
    return !glfwWindowShouldClose(m_Window);
}

void Window::Update() const
{
    scrollOffset = 0.0f;
    glfwSwapBuffers(m_Window);
    glfwPollEvents();
}

void Window::SetTitle(std::string newTitle)
{
    glfwSetWindowTitle(m_Window, newTitle.c_str());
}

void Window::GetDimensions(int* width, int* height) const
{
    glfwGetWindowSize(m_Window, width, height);
}

float Window::GetScrollOffset() const
{
    return scrollOffset; // Just Return The ScrollOffset Global Variable (Set Through The Callback)
}