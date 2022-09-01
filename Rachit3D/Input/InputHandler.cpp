#include "InputHandler.h"

InputHandler::InputHandler()
{
}

InputHandler::~InputHandler()
{
}

bool InputHandler::KeyHeld(Window& window, int glfwKey) const
{
    if (glfwGetKey(window.GetWindow(), glfwKey) == GLFW_PRESS)
        return true;

    return false;
}

bool InputHandler::KeyReleased(Window& window, int glfwKey) const
{
    if (glfwGetKey(window.GetWindow(), glfwKey) == GLFW_RELEASE)
        return true;

    return false;
}

bool InputHandler::LeftMouseButtonHeld(Window& window) const
{
    if (glfwGetMouseButton(window.GetWindow(), GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
        return true;

    return false;
}

bool InputHandler::RightMouseButtonHeld(Window& window) const
{
    if (glfwGetMouseButton(window.GetWindow(), GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
        return true;

    return false;
}

bool InputHandler::LeftMouseButtonReleased(Window& window) const
{
    if (glfwGetMouseButton(window.GetWindow(), GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
        return true;

    return false;
}

bool InputHandler::RightMouseButtonReleased(Window& window) const
{
    if (glfwGetMouseButton(window.GetWindow(), GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE)
        return true;

    return false;
}

void InputHandler::GetMouseCoords(Window& window, float& mouseX, float& mouseY)
{
    double mouseXAsDouble, mouseYAsDouble;

    glfwGetCursorPos(window.GetWindow(), &mouseXAsDouble, &mouseYAsDouble);

    mouseX = (float)mouseXAsDouble;
    mouseY = (float)mouseYAsDouble;
}

void InputHandler::SetMouseHidden(Window& window) const
{
    glfwSetInputMode(window.GetWindow(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
}

void InputHandler::SetMouseVisible(Window& window) const
{
    glfwSetInputMode(window.GetWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void InputHandler::SetMouseCoords(Window& window, float xPos, float yPos)
{
    glfwSetCursorPos(window.GetWindow(), (double)xPos, (double)yPos);
}

float InputHandler::GetScrollOffset(Window& window) const
{
    return window.GetScrollOffset() * -1.0f; // Call The Hacked Function That Returns The ScrollWheel Offset Global.
}