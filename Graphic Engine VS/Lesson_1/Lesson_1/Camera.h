#ifndef CAMERA_H
#define CAMERA_H

#include <glew.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

class Camera
{

public:

	Camera();

	void ProjectionSetup();
	void OrthographicSetup();
	void CameraSetup();
	void MoveCamera();

private:

	glm::vec3 m_camPosition;
	glm::vec3 m_target;
	glm::vec3 m_up;
	float m_cameraSpeed = 0.05f;

	//Mouse Motion
	glm::mat4 m_totalRotation;
	float m_xMousePos;
	float m_yMousePos;
	float lastX = 1280 / 2;
	float lastY = 720 / 2;
	float yaw = -90.0f;
	float pitch;
	bool m_firstMouse = true;

	//View
	GLuint viewUniformID = 0;
	glm::mat4 view;

	//Projection
	GLuint projectionUniformID = 0;
	glm::mat4 projection;
	bool isHoldingShift;

	GLuint m_positionID = 0;
};

#endif CAMERA_H