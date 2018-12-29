#include "Light.h"
#include <string>
#include <iostream>

int Light::s_totalLights = 0;

Light::Light(glm::vec3 position)
{
	m_lightPosition = position;

	m_ambient = glm::vec3(1.0f);
	m_diffuse = glm::vec3(1.0f);
	m_specular = glm::vec3(1.0f);

	m_attenuationConst = 0.09f;
	m_attenuationLinear = 0.09f;
	m_attenuationQuad = 0.05f;
}

void Light::SetColor(COLOR colorEnum, glm::vec3 color)
{
	m_color.r = color.r;
	m_color.g = color.g;
	m_color.b = color.b;

	m_colorEnum = colorEnum;

	//Check if colorEnum is qual to RUBY
	//if so set the ambient, diffuse and specular values for a ruby material
	if (m_colorEnum == RUBY)
	{
		m_ambient = glm::vec3(0.1745f, 0.01175f, 0.01175f);
		m_diffuse = glm::vec3(0.61424f, 0.04136f, 0.04136f);
		m_specular = glm::vec3(0.727811f, 0.626959f, 0.626959f);
	}

	//Check if colorEnum is qual to EMERALD
	//if so set the ambient, diffuse and specular values for a emerald material
	else if (m_colorEnum == EMERALD)
	{
		m_ambient = glm::vec3(0.0215f, 0.1745f, 0.0215f);
		m_diffuse = glm::vec3(0.07568f, 0.61424f, 0.07568f);
		m_specular = glm::vec3(0.633f, 0.727811f, 0.633f);
	}

	//Check if colorEnum is qual to OBSIDIAN
	//if so set the ambient, diffuse and specular values for a obsidian material
	else if (m_colorEnum == OBSIDIAN)
	{
		m_ambient = glm::vec3(0.05375f, 0.05375f, 0.6625f);
		m_diffuse = glm::vec3(0.18275f, 0.17f, 0.22525f);
		m_specular = glm::vec3(0.332741f, 0.328634f, 0.346435f);
	}

	//Check if colorEnum is qual to PEARL
	//if so set the ambient, diffuse and specular values for a pearl material
	else if (m_colorEnum == PEARL)
	{
		m_ambient = glm::vec3(0.25f, 0.20725f, 0.20725f);
		m_diffuse = glm::vec3(1.0f, 0.829f, 0.829f);
		m_specular = glm::vec3(0.296648f, 0.296648f, 0.296648f);
	}

	//Check if colorEnum is qual to TURQUOISE
	//if so set the ambient, diffuse and specular values for a turquoise material
	else if (m_colorEnum == TURQUOISE)
	{
		m_ambient = glm::vec3(0.1f, 0.18725f, 0.1745f);
		m_diffuse = glm::vec3(0.396f, 0.74151f, 0.69102f);
		m_specular = glm::vec3(0.297254f, 0.30829f, 0.306678f);
	}

	//Check if colorEnum is qual to BLACK_PLASTIC
	//if so set the ambient, diffuse and specular values for a black_plastic material
	else if (m_colorEnum == BLACK_PLASTIC)
	{
		m_ambient = glm::vec3(0.0f, 0.0f, 0.0f);
		m_diffuse = glm::vec3(0.01f, 0.01f, 0.01f);
		m_specular = glm::vec3(0.5f, 0.5f, 0.5f);
	}

	//Check if colorEnum is qual to COPPER
	//if so set the ambient, diffuse and specular values for a copper material
	else if (m_colorEnum == COPPER)
	{
		m_ambient = glm::vec3(0.19125f, 0.0735f, 0.0225f);
		m_diffuse = glm::vec3(0.7038f, 0.27048f, 0.0828f);
		m_specular = glm::vec3(0.256777f, 0.137622f, 0.086014f);
	}

	//Check if colorEnum is qual to SILVER
	//if so set the ambient, diffuse and specular values for a silver material
	else if (m_colorEnum == SILVER)
	{
		m_ambient = glm::vec3(0.19225f, 0.19225f, 0.19225f);
		m_diffuse = glm::vec3(0.50754f, 0.50754f, 0.50754f);
		m_specular = glm::vec3(0.508273f, 0.508273f, 0.508273f);
	}

	//Check if colorEnum is qual to GOLD
	//if so set the ambient, diffuse and specular values for a gold material
	else if (m_colorEnum == GOLD)
	{
		m_ambient = glm::vec3(0.24725f, 0.1995f, 0.0745f);
		m_diffuse = glm::vec3(0.75164f, 0.60648f, 0.22648f);
		m_specular = glm::vec3(0.628281f, 0.555802f, 0.366065f);
	}

	//Check if colorEnum is qual to CHROME
	//if so set the ambient, diffuse and specular values for a chrome material
	else if (m_colorEnum == CHROME)
	{
		m_ambient = glm::vec3(0.25f, 0.25f, 0.25f);
		m_diffuse = glm::vec3(0.4f, 0.4f, 0.4f);
		m_specular = glm::vec3(0.774597f, 0.774597f, 0.774597f);
	}

	//Check if colorEnum is qual to NONE
	//if so the ambient, diffuse and specular values need to be set separately
	else if (m_colorEnum == NONE)
	{
		std::cout << "Must enter ambient, diffuse and specular values yourself" << std::endl;
	}

}

void Light::SetType(TYPE type)
{
	//If type is equal to 1, set the light type to DIRECTIONAL
	if (type == 1)
	{
		m_lightType = DIRECTIONAL;
	}
	//If type is equal to 2, set the light type to POINT
	else if (type == 2)
	{
		m_lightType = POINT;
	}
}

void Light::SetAmbient(glm::vec3 ambient)
{
	m_ambient = ambient;
}

void Light::SetDiffuse(glm::vec3 diffuse)
{
	m_diffuse = diffuse;
}

void Light::SetSpecular(glm::vec3 specular)
{
	m_specular = specular;
}

void Light::Create()
{
	int shaderProgramID = TheShader::Instance()->getProgramID();

	m_vertModelUniformID = glGetUniformLocation(shaderProgramID, "vertModel");
	m_fragModelUniformID = glGetUniformLocation(shaderProgramID, "fragModel");
	m_vertexAttributeID = glGetAttribLocation(shaderProgramID, "vertexIn");
	m_colorAttributeID = glGetAttribLocation(shaderProgramID, "colorIn");
	m_isLitUniformID = glGetUniformLocation(shaderProgramID, "isLit");
	m_isLightUniformID = glGetUniformLocation(shaderProgramID, "isLight");

	//increment total lights in scene
	m_lightNumber = s_totalLights++;

	//convert light number to string
	lightStr = std::to_string(m_lightNumber);

	lightNumAttenConstStr = "lights[" + lightStr + "].attenuationConst";
	lightNumAttenLinStr = "lights[" + lightStr + "].attenuationLinear";
	lightNumAttenQuadStr = "lights[" + lightStr + "].attenuationQuad";
	lightNumPos = "lights[" + lightStr + "].position";
	lightNumAmb = "lights[" + lightStr + "].ambient";
	lightNumDiff = "lights[" + lightStr + "].diffuse";
	lightNumSpec = "lights[" + lightStr + "].specular";
	lightNumType = "lights[" + lightStr + "].type";

	m_lightPositionID = glGetUniformLocation(shaderProgramID, lightNumPos.c_str());
	m_ambientID = glGetUniformLocation(shaderProgramID, lightNumAmb.c_str());
	m_diffuseID = glGetUniformLocation(shaderProgramID, lightNumDiff.c_str());
	m_specularID = glGetUniformLocation(shaderProgramID, lightNumSpec.c_str());

	m_attenConstID = glGetUniformLocation(shaderProgramID, lightNumAttenConstStr.c_str());
	m_attenLinearID = glGetUniformLocation(shaderProgramID, lightNumAttenLinStr.c_str());
	m_attenQuadID = glGetUniformLocation(shaderProgramID, lightNumAttenQuadStr.c_str());

	m_lightTypeID = glGetUniformLocation(shaderProgramID, lightNumType.c_str());
}

void Light::Draw()
{
	//Fill colors array based on the inputted color
	GLfloat colors[] = { m_color.r, m_color.g, m_color.b,
						   m_color.r, m_color.g, m_color.b,
						   m_color.r, m_color.g, m_color.b,
						   m_color.r, m_color.g, m_color.b };

	glGenBuffers(1, &VBO);
	glGenBuffers(1, &vertexVBO);
	glGenBuffers(1, &colorVBO);

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

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	m_model = glm::mat4(1.0f);

	m_model = glm::translate(m_model, m_lightPosition);

	//Send the model (the light quad) information to the vertex shader
	glUniformMatrix4fv(m_vertModelUniformID, 1, GL_FALSE, &m_model[0][0]);

	glUniformMatrix4fv(m_fragModelUniformID, 1, GL_FALSE, &m_model[0][0]);

	glUniform1i(m_isLitUniformID, 1);
	glUniform1i(m_isLightUniformID, 1);

	glUniform1i(m_lightTypeID, m_lightType);

	glUniform3fv(m_lightPositionID, 1, &m_lightPosition.x);
	glUniform3fv(m_ambientID, 1, &m_ambient.x);
	glUniform3fv(m_diffuseID, 1, &m_diffuse.x);
	glUniform3fv(m_specularID, 1, &m_specular.x);

	glUniform1f(m_attenConstID, m_attenuationConst);
	glUniform1f(m_attenLinearID, m_attenuationLinear);
	glUniform1f(m_attenQuadID, m_attenuationQuad);

	glPointSize(25.0f);

	glBindVertexArray(VAO);
	glDrawArrays(GL_POINTS, 0, 1);
	glBindVertexArray(0);
}

void Light::Update()
{
	const Uint8* keyStates = SDL_GetKeyboardState(NULL);

	//Check if the light type is DIRECTIONAL, as do not 
	//want to manipulate the light if it is a DIRECTIONAL light
	if (m_lightType != DIRECTIONAL)
	{
		//Check if minus key is pressed and lightingOn is true
		//if so set the ambient, diffuse and specular to 0.0f
		//meaning the lights are turned off
		if (keyStates[SDL_SCANCODE_MINUS] && m_lightingOn == true)
		{
			SetAmbient(glm::vec3(0.0f));
			SetDiffuse(glm::vec3(0.0f));
			SetSpecular(glm::vec3(0.0f));
			m_lightingOn = false;
		}
		//Check if equals key (wanted the plus key but no SDL_SCANCODE for that)
		//is pressed and lightingOn is true
		//if so set the ambient, diffuse and specular to 0.5f
		//meaning the lights are turned on and emit a white light
		//values at 0.5f so the white light isn't too bright compared to all other lights
		else if (keyStates[SDL_SCANCODE_EQUALS] && m_lightingOn == false)
		{
			SetAmbient(glm::vec3(0.5f));
			SetDiffuse(glm::vec3(0.5f));
			SetSpecular(glm::vec3(0.5f));
			m_lightingOn = true;
		}

		if (m_lightingOn == true)
		{
			//Check if either the left of right shift is being held
			//if so set isHoldingShift to true, meaning the quad
			//can move faster
			if (keyStates[SDL_SCANCODE_LSHIFT] || keyStates[SDL_SCANCODE_RSHIFT])
			{
				m_isHoldingShift = true;
			}
			//Check if the left key is pressed
			//if so move the light left
			if (keyStates[SDL_SCANCODE_LEFT])
			{
				if (m_isHoldingShift)
				{
					m_lightPosition.x -= (2 * m_lightMoveSpeed);
				}
				else
				{
					m_lightPosition.x -= m_lightMoveSpeed;
				}
			}
			//Check if the right key is pressed
			//if so move the light right
			if (keyStates[SDL_SCANCODE_RIGHT])
			{
				if (m_isHoldingShift)
				{
					m_lightPosition.x += (2 * m_lightMoveSpeed);
				}
				else
				{
					m_lightPosition.x += m_lightMoveSpeed;
				}
			}
			//Check if the up key is pressed
			//if so move the light up
			if (keyStates[SDL_SCANCODE_UP])
			{
				if (m_isHoldingShift)
				{
					m_lightPosition.y += (2 * m_lightMoveSpeed);
				}
				else
				{
					m_lightPosition.y += m_lightMoveSpeed;
				}
			}
			//Check if the down key is pressed
			//if so move the light down
			if (keyStates[SDL_SCANCODE_DOWN])
			{
				if (m_isHoldingShift)
				{
					m_lightPosition.y -= (2 * m_lightMoveSpeed);
				}
				else
				{
					m_lightPosition.y -= m_lightMoveSpeed;
				}
			}
			//Check if the O key is pressed
			//if so move the light forward
			if (keyStates[SDL_SCANCODE_O])
			{
				if (m_isHoldingShift)
				{
					m_lightPosition.z -= (2 * m_lightMoveSpeed);
				}
				else
				{
					m_lightPosition.z -= m_lightMoveSpeed;
				}
			}
			//Check if the P key is pressed
			//if so move the light backwards
			if (keyStates[SDL_SCANCODE_P])
			{
				if (m_isHoldingShift)
				{
					m_lightPosition.z += (2 * m_lightMoveSpeed);
				}
				else
				{
					m_lightPosition.z += m_lightMoveSpeed;
				}
			}
			//Check if 1 key is pressed
			//if so make the light red
			if (keyStates[SDL_SCANCODE_1])
			{
				SetColor(RUBY, glm::vec3(1.0f, 0.0f, 0.0f));
			}
			//Check if 2 key is pressed
			//if so make the light green
			if (keyStates[SDL_SCANCODE_2])
			{
				SetColor(EMERALD, glm::vec3(0.0f, 1.0f, 0.0f));
			}
			//Check if 3 key is pressed
			//if so make the light blue
			if (keyStates[SDL_SCANCODE_3])
			{
				SetColor(TURQUOISE, glm::vec3(0.0f, 0.5f, 1.0f));
			}
			//Check if 4 key is pressed
			//if so make the light yellow
			if (keyStates[SDL_SCANCODE_4])
			{
				SetColor(GOLD, glm::vec3(1.0f, 1.0f, 0.0f));
			}
			//Check if 5 key is pressed
			//if so make the light purple
			if (keyStates[SDL_SCANCODE_5])
			{
				SetColor(OBSIDIAN, glm::vec3(1.0f, 0.0f, 1.0f));
			}
			//Check if 6 key is pressed
			//if so make the light white
			if (keyStates[SDL_SCANCODE_6])
			{
				SetColor(SILVER, glm::vec3(0.75f, 0.75f, 0.75f));
			}
			//Check if 7 key is pressed
			//if so make the orange
			if (keyStates[SDL_SCANCODE_7])
			{
				SetColor(COPPER, glm::vec3(0.72f, 0.45f, 0.20f));
			}
			//Check if 8 key is pressed
			//if so make the chrome
			if (keyStates[SDL_SCANCODE_8])
			{
				SetColor(CHROME, glm::vec3(0.80f, 0.75f, 0.70f));
			}
			//Check if 9 key is pressed
			//if so make the light white
			if (keyStates[SDL_SCANCODE_9])
			{
				SetColor(NONE, glm::vec3(1.0f, 1.0f, 1.0f));
				SetAmbient(glm::vec3(0.5f));
				SetDiffuse(glm::vec3(0.5f));
				SetSpecular(glm::vec3(0.5f));
			}
			//When shift is let go, set isHoldingShift back to false
			else
			{
				m_isHoldingShift = false;
			}
		}
	}
}

void Light::Destroy()
{
	//decrement amount of lights in scene
	s_totalLights--;

	//Disable both the vertex and color attributes
	glDisableVertexAttribArray(m_vertexAttributeID);
	glDisableVertexAttribArray(m_colorAttributeID);

	//Destroy the buffers
	glDeleteBuffers(1, &VBO);
	//glDeleteBuffers(1, &colorVBO);

	//Destroy the buffers
	glDeleteVertexArrays(1, &VAO);
}