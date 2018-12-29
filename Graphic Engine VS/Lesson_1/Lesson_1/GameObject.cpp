#include "GameObject.h"
#include "ShaderManager.h"
#include <iostream>
#include <string>

GameObject::GameObject(glm::vec3 position, glm::vec3 scale, float rotationAngle,
	glm::vec3 rotationAxis, bool isLit, std::string shaderName, bool isTextured,
	std::string textureFile, std::string textureID)
{
	m_Position = position;
	m_Scale = scale;
	m_RotationAngle = rotationAngle;
	m_RotationAxis = rotationAxis;
	m_isLit = isLit;
	m_isTextured = isTextured;
	m_textureFile = textureFile;
	m_textureID = textureID;
	m_shaderName = shaderName;
}

void GameObject::SetColor(glm::vec3 color)
{
	m_color.r = color.r;
	m_color.g = color.g;
	m_color.b = color.b;
}

void GameObject::SetMaterial(MaterialType materialType)
{

	if (materialType == RUBY)
	{
		m_shininess = 76.8f;
		m_ambient = glm::vec3(0.1745f, 0.01175f, 0.01175f);
		m_diffuse = glm::vec3(0.61424f, 0.04136f, 0.04136f);
		m_specular = glm::vec3(0.727811f, 0.626959f, 0.626959f);
	}

	else if (materialType == EMERALD)
	{
		m_shininess = 76.8f;
		m_ambient = glm::vec3(0.0215f, 0.1745f, 0.0215f);
		m_diffuse = glm::vec3(0.07568f, 0.61424f, 0.07568f);
		m_specular = glm::vec3(0.633f, 0.727811f, 0.633f);
	}

	else if (materialType == OBSIDIAN)
	{
		m_shininess = 38.4f;
		m_ambient = glm::vec3(0.05375f, 0.05375f, 0.6625f);
		m_diffuse = glm::vec3(0.18275f, 0.17f, 0.22525f);
		m_specular = glm::vec3(0.332741f, 0.328634f, 0.346435f);
	}

	else if (materialType == PEARL)
	{
		m_shininess = 11.264f;
		m_ambient = glm::vec3(0.25f, 0.20725f, 0.20725f);
		m_diffuse = glm::vec3(1.0f, 0.829f, 0.829f);
		m_specular = glm::vec3(0.296648f, 0.296648f, 0.296648f);
	}

	else if (materialType == TURQUOISE)
	{
		m_shininess = 12.8f;
		m_ambient = glm::vec3(0.1f, 0.18725f, 0.1745f);
		m_diffuse = glm::vec3(0.396f, 0.74151f, 0.69102f);
		m_specular = glm::vec3(0.297254f, 0.30829f, 0.306678f);
	}

	else if (materialType == BLACK_PLASTIC)
	{
		m_shininess = 32.0f;
		m_ambient = glm::vec3(0.0f, 0.0f, 0.0f);
		m_diffuse = glm::vec3(0.01f, 0.01f, 0.01f);
		m_specular = glm::vec3(0.5f, 0.5f, 0.5f);
	}

	else if (materialType == COPPER)
	{
		m_shininess = 12.8;
		m_ambient = glm::vec3(0.19125f, 0.0735f, 0.0225f);
		m_diffuse = glm::vec3(0.7038f, 0.27048f, 0.0828f);
		m_specular = glm::vec3(0.256777f, 0.137622f, 0.086014f);
	}

	else if (materialType == SILVER)
	{
		m_shininess = 51.2f;
		m_ambient = glm::vec3(0.19225f, 0.19225f, 0.19225f);
		m_diffuse = glm::vec3(0.50754f, 0.50754f, 0.50754f);
		m_specular = glm::vec3(0.508273f, 0.508273f, 0.508273f);
	}

	else if (materialType == GOLD)
	{
		m_shininess = 51.2f;
		m_ambient = glm::vec3(0.24725f, 0.1995f, 0.0745f);
		m_diffuse = glm::vec3(0.75164f, 0.60648f, 0.22648f);
		m_specular = glm::vec3(0.628281f, 0.555802f, 0.366065f);
	}

	else if (materialType == CHROME)
	{
		m_shininess = 76.8;
		m_ambient = glm::vec3(0.25f, 0.25f, 0.25f);
		m_diffuse = glm::vec3(0.4f, 0.4f, 0.4f);
		m_specular = glm::vec3(0.774597f, 0.774597f, 0.774597f);
	}
}

void GameObject::SetAmbient(glm::vec3 ambient)
{
	m_ambient = m_material->SetAmbient(glm::vec3(ambient));
}

void GameObject::SetDiffuse(glm::vec3 diffuse)
{
	m_diffuse = m_material->SetAmbient(glm::vec3(diffuse));
}

void GameObject::SetSpecular(glm::vec3 specular)
{
	m_specular = m_material->SetAmbient(glm::vec3(specular));
}

void GameObject::SetShininess(float shininess)
{
	m_shininess = m_material->SetShininess(shininess);
}

void GameObject::Create(bool isCube, bool isQuad)
{
	if (isCube)
	{
		m_buffer->Enable(m_color, m_ambient, m_diffuse, m_specular, m_shininess, m_isLit, m_shaderName, m_isTextured, m_textureFile, m_textureID);
		m_buffer->Bind(true, false);
	}
	else if (isQuad)
	{
		m_buffer->Enable(m_color, m_ambient, m_diffuse, m_specular, m_shininess, m_isLit, m_shaderName, m_isTextured, m_textureFile, m_textureID);
		m_buffer->Bind(false, true);
	}
}

void GameObject::Draw(bool isCube, bool isQuad)
{
	int shaderProgramID = TheShader::Instance()->getProgramID();

	m_vertModelUniformID = glGetUniformLocation(shaderProgramID, "vertModel");
	m_fragModelUniformID = glGetUniformLocation(shaderProgramID, "fragModel");
	GLuint m_normalMatrixUniformID = glGetUniformLocation(shaderProgramID, "normal");

	if (isCube)
	{
		m_model = glm::mat4(1.0f);

		m_model = glm::translate(m_model, m_Position);

		m_model = glm::rotate(m_model, glm::radians(m_RotationAngle), m_RotationAxis);

		m_model = glm::scale(m_model, m_Scale);

		glm::mat3 normalMatrix = glm::inverse(glm::mat3(m_model));
		glUniformMatrix4fv(m_normalMatrixUniformID, 1, GL_TRUE, &normalMatrix[0][0]);

		//Send the model (the cube) information to the vertex shader
		glUniformMatrix4fv(m_vertModelUniformID, 1, GL_FALSE, &m_model[0][0]);
		glUniformMatrix4fv(m_fragModelUniformID, 1, GL_FALSE, &m_model[0][0]);

		m_buffer->Draw(true, false);
	}
	else if (isQuad)
	{
		m_model = glm::mat4(1.0f);

		m_model = glm::translate(m_model, m_Position);

		m_model = glm::rotate(m_model, glm::radians(m_RotationAngle), m_RotationAxis);

		m_model = glm::scale(m_model, m_Scale);

		glm::mat3 normalMatrix = glm::inverse(glm::mat3(m_model));
		glUniformMatrix4fv(m_normalMatrixUniformID, 1, GL_TRUE, &normalMatrix[0][0]);

		//Send the model (the quad) information to the vertex shader
		glUniformMatrix4fv(m_vertModelUniformID, 1, GL_FALSE, &m_model[0][0]);
		glUniformMatrix4fv(m_fragModelUniformID, 1, GL_FALSE, &m_model[0][0]);

		m_buffer->Draw(false, true);
	}
}

void GameObject::Update()
{
	const Uint8* keyStates = SDL_GetKeyboardState(NULL);

	//Check if either the left of right shift is being held
	//if so set isHoldingShift to true, meaning the cube
	//can move faster
	if (keyStates[SDL_SCANCODE_LSHIFT] || keyStates[SDL_SCANCODE_RSHIFT])
	{
		m_isHoldingShift = true;
	}
	//Check if the left key is pressed
	//if so move the quad left
	if (keyStates[SDL_SCANCODE_LEFT])
	{
		if (m_isHoldingShift)
		{
			m_Position.x -= (2 * m_MoveSpeed);
		}
		else
		{
			m_Position.x -= m_MoveSpeed;
		}
	}
	//Check if the right key is pressed
	//if so move the quad right
	if (keyStates[SDL_SCANCODE_RIGHT])
	{
		if (m_isHoldingShift)
		{
			m_Position.x += (2 * m_MoveSpeed);
		}
		else
		{
			m_Position.x += m_MoveSpeed;
		}
	}
	//Check if the up key is pressed
	//if so move the quad up
	if (keyStates[SDL_SCANCODE_UP])
	{
		if (m_isHoldingShift)
		{
			m_Position.y += (2 * m_MoveSpeed);
		}
		else
		{
			m_Position.y += m_MoveSpeed;
		}
	}
	//Check if the down key is pressed
	//if so move the quad down
	if (keyStates[SDL_SCANCODE_DOWN])
	{
		if (m_isHoldingShift)
		{
			m_Position.y -= (2 * m_MoveSpeed);
		}
		else
		{
			m_Position.y -= m_MoveSpeed;
		}
	}
	//When shift is let go, set isHoldingShift back to false
	else
	{
		m_isHoldingShift = false;
	}
}

void GameObject::Destroy()
{
	m_buffer->Destroy();
}