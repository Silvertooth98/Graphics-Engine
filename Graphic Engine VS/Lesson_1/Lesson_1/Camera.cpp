#include "Camera.h"
#include "ShaderManager.h"
#include "InputManager.h"
#include <string>
#include <iostream>

Camera::Camera()
{
}

void Camera::ProjectionSetup()
{
	//Create projection properties, making it 3D
	projection = glm::perspective(glm::radians(45.0f), 1280.0f / 720.0f, 0.5f, 1000.0f);
}

void Camera::OrthographicSetup()
{
	//Create orthographic properties, making it 2D
	projection = glm::ortho(0.0f, 1280.0f, 0.0f, 768.0f);
}

void Camera::CameraSetup()
{
	int shaderProgramID = TheShader::Instance()->getProgramID();

	viewUniformID = glGetUniformLocation(shaderProgramID, "view");
	projectionUniformID = glGetUniformLocation(shaderProgramID, "projection");
	m_positionID = glGetUniformLocation(shaderProgramID, "cameraPosition");

	//Create the camera's properties
	m_camPosition = glm::vec3(-0.3f, 0.0f, 0.0f);
	m_target = glm::vec3(0.0f, 0.0f, -1.0f);
	m_up = glm::vec3(0.0f, 1.0f, 0.0f);

	//Set mouse position to X = 640 and Y = 360
	SDL_WarpMouseGlobal(640, 360);
	//Set show cursor to false meaning you can't see the cursor
	SDL_ShowCursor(false);
}

void Camera::MoveCamera()
{
	//Set mouse position to X = 640 and Y = 360
	SDL_WarpMouseGlobal(640, 360);

	const Uint8* keyStates = SDL_GetKeyboardState(NULL);

	//*********************************************************************************************
	//			MOUSE MOTION - tutorial from https://learnopengl.com/Getting-started/Camera
	//				 - my own code and comments, but was following along the tutorial above
	//*********************************************************************************************

	//Get the initial mouse position of X and Y
	//Which will be X = 640 and Y = 360 since we set the initial position
	m_xMousePos = TheInput::Instance()->getMouseMotionX();
	m_yMousePos = TheInput::Instance()->getMouseMotionY();

	//m_firstMouse is set to true when first starting up the application
	//Running this sets the variables lastX and lastY to the initial positions
	//of the X and Y values for the camera. Then set m_firstMouse to false
	//so the code isn't run again, as we only want it to be run the first time
	if (m_firstMouse)	//Initially set to be true
	{
		lastX = m_xMousePos;
		lastY = m_yMousePos;
		m_firstMouse = false;
	}

	//m_xOffset is the difference between the initial X mouse position and the
	//current frame X mouse position. m_yOffset is the difference between the current
	//frame Y position and the initial Y mouse position. m_yOffset is reversed, as
	//Y coordinates range from bottom to top.
	float m_xOffset = m_xMousePos - lastX;
	float m_yOffset = lastY - m_yMousePos;

	//Sensitivity is the speed at which I want the camera motion to move
	//We multiple the Offset value by the sensitivity to make the movement
	//dependant on the value we set for the sensitivity speed
	float sensitivity = 0.25f;
	m_xOffset *= sensitivity;
	m_yOffset *= sensitivity;

	//Yaw is the Y Euler angle and Pitch is the X Euler angle
	//We add the offset values to the Yaw and Pitch values in order to work out
	//the X and Y rotations
	yaw += m_xOffset;
	pitch += m_yOffset;

	//We then check the value for the Y rotation, as we don't want the camera to be able
	//to look further than straight up and straight down. These contraints work by
	//just replacing the resulting Pitch value with it's contraint, being 89 or -89
	if (pitch > 89.0f)
	{
		pitch = 89.0f;
	}
	else if (pitch < -89.0f)
	{
		pitch = -89.0f;
	}

	//Finally, calculate the direction vector from the Yaw and Pitch value results
	glm::vec3 front;	//front is the actual direction vector which will be manipulated
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));	//X value for front
	front.y = sin(glm::radians(pitch));								//Y value for front
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));	//Z value for front

	//then set the target of the camera to be the normalized value of the actual direction
	//vector, which is the front variable
	m_target = glm::normalize(front);

	//*********************************************************************************************
	//				tutorial help end
	//*********************************************************************************************

	//Check if either the left of right shift is being held
	//if so set isHoldingShift to true, meaning the camera
	//can move faster
	if (keyStates[SDL_SCANCODE_LSHIFT] || keyStates[SDL_SCANCODE_RSHIFT])
	{
		isHoldingShift = true;
	}
	//Check if Left Control is pressed
	//if so move the camera down
	if (keyStates[SDL_SCANCODE_LCTRL])
	{
		if (isHoldingShift)
		{
			m_camPosition.y -= (2 * m_cameraSpeed);
		}
		else
		{
			m_camPosition.y -= m_cameraSpeed;
		}
	}
	//Check if space is pressed
	//if so move the camera up
	if (keyStates[SDL_SCANCODE_SPACE])
	{
		if (isHoldingShift)
		{
			m_camPosition.y += (2 * m_cameraSpeed);
		}
		else
		{
			m_camPosition.y += m_cameraSpeed;
		}
	}
	//Check if W key is pressed
	//if so move camera forward towards
	//where the camera is facing
	if (keyStates[SDL_SCANCODE_W])
	{
		if (isHoldingShift)
		{
			m_camPosition += (2 * m_cameraSpeed) * m_target;
		}
		else
		{
			m_camPosition += m_cameraSpeed * m_target;
		}
	}
	//Check if S key is pressed
	//if so move camera backward towards
	//where the camera is facing
	if (keyStates[SDL_SCANCODE_S])
	{
		if (isHoldingShift)
		{
			m_camPosition -= (2 * m_cameraSpeed) * m_target;
		}
		else
		{
			m_camPosition -= m_cameraSpeed * m_target;
		}
	}
	//Check if A key is pressed
	//if so move camera left in the direction
	//of where the camera is facing
	if (keyStates[SDL_SCANCODE_A])
	{
		if (isHoldingShift)
		{
			m_camPosition -= glm::normalize(glm::cross(m_target, m_up)) * (2 * m_cameraSpeed);
		}
		else
		{
			m_camPosition -= glm::normalize(glm::cross(m_target, m_up)) * m_cameraSpeed;
		}
	}
	//Check if D key is pressed
	//if so move camera right in the direction
	//of where the camera is facing
	if (keyStates[SDL_SCANCODE_D])
	{
		if (isHoldingShift)
		{
			m_camPosition += glm::normalize(glm::cross(m_target, m_up)) * (2 * m_cameraSpeed);
		}
		else
		{
			m_camPosition += glm::normalize(glm::cross(m_target, m_up)) * m_cameraSpeed;
		}
	}
	//When shift is let go, set isHoldingShift back to false
	else
	{
		isHoldingShift = false;
	}

	//Move the camera based on the player's input
	view = glm::lookAt(m_camPosition, m_camPosition + m_target, m_up);

	//Send the view (camera) information to the vertex shader
	glUniformMatrix4fv(viewUniformID, 1, GL_FALSE, &view[0][0]);

	//Send the projection (2D or 3D) information to the vertex shader
	glUniformMatrix4fv(projectionUniformID, 1, GL_FALSE, &projection[0][0]);

	glUniform3fv(m_positionID, 1, &m_camPosition.x);
}