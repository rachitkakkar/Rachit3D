#pragma once
/* WINDOW CLASS: CREATES A GLFW WINDOW WITH AN OPENGL CONTEXT AND HANDLES INPUT */

#include <string>

#include "../Renderer/Renderer.h" // Include GLEW Before GLFW

#include <GLFW/glfw3.h>

void Resize(GLFWwindow* window, int width, int height);

class Window
{
private:
	int m_Width, m_Height;
	std::string m_Title;
	GLFWwindow* m_Window;

public:
	Window(int width, int height, std::string title);
	~Window();

	bool IsRunning() const;
	void Update() const;
	
	void SetTitle(std::string newTitle);
	void GetDimensions(int* width, int* height) const;
	float GetScrollOffset() const;

	inline GLFWwindow* GetWindow() const { return m_Window; }
};