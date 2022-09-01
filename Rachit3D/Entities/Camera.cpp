#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>

Camera::Camera(glm::vec3 position, glm::vec3 orientation)
	:m_FOV(45.0f), m_Position(position), m_Orientation(orientation), m_Up(glm::vec3(0.0f, 1.0f, 0.0f))
{
}

Camera::~Camera()
{
}

glm::mat4 Camera::GetViewMatrix()
{
	return glm::lookAt(m_Position, m_Position + m_Orientation, m_Up);
}

glm::mat4 Camera::GetProjMatrix(int width, int height)
{
	return glm::perspective(glm::radians(m_FOV), (float)(width / height), 0.1f, 1000.0f);
}

void Camera::MoveCameraPosition(glm::vec3 orientation, float amount)
{
	m_Position += amount * orientation;
}

void Camera::RotateCamera(glm::vec3 axis, float degrees)
{
	m_Orientation = glm::rotate(m_Orientation, glm::radians(degrees), glm::normalize(axis));
}

void Camera::ChangeFOV(float amount)
{
	m_FOV += amount;
}

void Camera::SetFOV(float amount)
{
	m_FOV = amount;
}