#include "Sprite.h"
#include "ShaderManager.h"
#include <string>
#include <iostream>

Sprite::Sprite(GLuint width, GLuint height)
{
	m_dimesion = glm::vec3(width, height, 1.0f);
}

void Sprite::Create()
{
	int shaderProgramID = TheShader::Instance()->getProgramID();

	m_modelUniformID = glGetUniformLocation(shaderProgramID, "model");
	m_vertexAttributeID = glGetAttribLocation(shaderProgramID, "vertexIn");
	m_colorAttributeID = glGetAttribLocation(shaderProgramID, "colorIn");

	//Create all the VBOs, the EBO and the VAO
	glGenBuffers(1, &vertexVBO);
	glGenBuffers(1, &colorVBO);
	glGenBuffers(1, &EBO);
	glGenVertexArrays(1, &VAO);

	//bind the VAO which has all the VBOs and EBO inside
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(m_vertexAttributeID, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(m_vertexAttributeID);

	glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
	glVertexAttribPointer(m_colorAttributeID, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(m_colorAttributeID);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
}

void Sprite::Draw()
{
	m_model = glm::mat4(1.0f);

	m_model = glm::translate(m_model, m_spritePosition);

	//Send the model (the quad) information to the vertex shader
	glUniformMatrix4fv(m_modelUniformID, 1, GL_FALSE, &m_model[0][0]);

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Sprite::Update()
{
	const Uint8* keyStates = SDL_GetKeyboardState(NULL);

	//Check if the left key is pressed
	//if so move the quad left
	if (keyStates[SDL_SCANCODE_LEFT])
	{
		m_spritePosition.x -= 0.01f;
	}
	//Check if the right key is pressed
	//if so move the quad right
	if (keyStates[SDL_SCANCODE_RIGHT])
	{
		m_spritePosition.x += 0.01f;
	}
	//Check if the up key is pressed
	//if so move the quad up
	if (keyStates[SDL_SCANCODE_UP])
	{
		m_spritePosition.y += 0.01f;
	}
	//Check if the down key is pressed
	//if so move the quad down
	if (keyStates[SDL_SCANCODE_DOWN])
	{
		m_spritePosition.y -= 0.01f;
	}
}

void Sprite::Destroy()
{
	//Disable both the vertex and color attributes
	glDisableVertexAttribArray(m_vertexAttributeID);
	glDisableVertexAttribArray(m_colorAttributeID);

	//Destroy the buffers
	glDeleteBuffers(1, &vertexVBO);
	glDeleteBuffers(1, &colorVBO);
	glDeleteBuffers(1, &EBO);

	//Destroy the buffers
	glDeleteVertexArrays(1, &VAO);
}