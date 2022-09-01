#include "TimeHandler.h"

#include <GLFW/glfw3.h>

TimeHandler::TimeHandler()
{
	m_CurrentFrameTime = glfwGetTime();
	m_LastFrameTime = m_CurrentFrameTime;
}

TimeHandler::~TimeHandler()
{
}

float TimeHandler::GetDeltaTime()
{
	m_CurrentFrameTime = glfwGetTime();
	float deltaTime = m_CurrentFrameTime - m_LastFrameTime;
	m_LastFrameTime = m_CurrentFrameTime;

	return deltaTime;
}