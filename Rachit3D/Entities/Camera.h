#pragma once
/* CAMERA CLASS: A SIMPLE CAMERA THAT CAN BE MOVED AROUND, AND CREATES A VIEW MATRIX FOR RENDERERING */

#include <glm/glm.hpp>

class Camera
{
private:
	float m_FOV;

	glm::vec3 m_Position;
	glm::vec3 m_Orientation;
	glm::vec3 m_Up;

public:
	Camera(glm::vec3 position, glm::vec3 orientation);
	~Camera();

	glm::mat4 GetViewMatrix();
	glm::mat4 GetProjMatrix(int width, int height);
	
	void MoveCameraPosition(glm::vec3 orientation, float amount);
	void RotateCamera(glm::vec3 axis, float degrees);
	
	void ChangeFOV(float amount);
	void SetFOV(float amount);

	inline glm::vec3 GetOrientation() const { return m_Orientation; }
	inline glm::vec3 GetUp() const { return m_Up; }
	inline float GetFOV() const { return m_FOV; }
};