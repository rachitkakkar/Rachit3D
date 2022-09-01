#pragma once
/* INPUTHANDLER CLASS: HANDLES KEYBOARD & MOUSE INPUT */

#include "Window.h"

class InputHandler
{
public:
	InputHandler();
	~InputHandler();

	bool KeyHeld(Window& window, int glfwKey) const;
	bool KeyReleased(Window& window, int glfwKey) const;

	bool LeftMouseButtonHeld(Window& window) const;
	bool RightMouseButtonHeld(Window& window) const;
	bool LeftMouseButtonReleased(Window& window) const;
	bool RightMouseButtonReleased(Window& window) const;

	void GetMouseCoords(Window& window, float& mouseX, float& mouseY);
	void SetMouseCoords(Window& window, float xPos, float yPos);
	
	void SetMouseHidden(Window& window) const;
	void SetMouseVisible(Window& window) const;

	float GetScrollOffset(Window& window) const;
};