#include "Buffer.h"
#include "ShaderManager.h"
#include <iostream>

int Buffer::s_totalLights = 0;

Buffer::Buffer()
{
	m_ambient = glm::vec3(0.3f, 0.3f, 0.3f);
	m_diffuse = glm::vec3(0.0f, 0.3f, 0.8f);
	m_specular = glm::vec3(0.7f, 0.7f, 0.0f);
	m_shininess = 1.0f;

	m_attenuationConst = 0.09f;
	m_attenuationLinear = 0.09f;
	m_attenuationQuad = 0.05f;
}

void Buffer::Enable(glm::vec3 color, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float shiniess,
					bool isLit, std::string shaderName, bool isTextured, std::string textureFile, std::string textureID)
{
	m_color.r = color.r;
	m_color.g = color.g;
	m_color.b = color.b;

	m_ambient = ambient;
	m_diffuse = diffuse;
	m_specular = specular;
	m_shininess = shiniess;

	m_isLit = isLit;
	m_isTextured = isTextured;
	m_textureFile = textureFile;
	m_textureID = textureID;
	m_shaderName = shaderName;

	if (shaderName == "NOISE")
	{
		m_isNoiseShader = true;
		m_isCircleNoiseShader = false;
		m_isColorChangeShader = false;
		m_isFireBoxShader = false;
	}
	else if (shaderName == "CIRCLE_NOISE")
	{
		m_isNoiseShader = false;
		m_isCircleNoiseShader = true;
		m_isColorChangeShader = false;
		m_isFireBoxShader = false;
	}
	else if (shaderName == "COLORS")
	{
		m_isNoiseShader = false;
		m_isCircleNoiseShader = false;
		m_isColorChangeShader = true;
		m_isFireBoxShader = false;
	}
	else if (shaderName == "FIREBOX")
	{
		m_isNoiseShader = false;
		m_isCircleNoiseShader = false;
		m_isColorChangeShader = false;
		m_isFireBoxShader = true;
	}
	else
	{
		m_isNoiseShader = false;
		m_isCircleNoiseShader = false;
		m_isColorChangeShader = false;
		m_isFireBoxShader = false;
	}

	int shaderProgramID = TheShader::Instance()->getProgramID();

	m_vertModelUniformID = glGetUniformLocation(shaderProgramID, "vertModel");
	m_vertexAttributeID = glGetAttribLocation(shaderProgramID, "vertexIn");
	m_colorAttributeID = glGetAttribLocation(shaderProgramID, "colorIn");
	m_textureAttributeID = glGetAttribLocation(shaderProgramID, "textureIn");
	m_isTexturedUniformID = glGetUniformLocation(shaderProgramID, "textureFlag");
	m_normalAttributeID = glGetAttribLocation(shaderProgramID, "normalIn");

	m_isLitUniformID = glGetUniformLocation(shaderProgramID, "isLit");
	m_isLightUniformID = glGetUniformLocation(shaderProgramID, "isLight");

	m_ambientID = glGetUniformLocation(shaderProgramID, "material.ambient");
	m_diffuseID = glGetUniformLocation(shaderProgramID, "material.diffuse");
	m_specularID = glGetUniformLocation(shaderProgramID, "material.specular");
	m_shininessID = glGetUniformLocation(shaderProgramID, "material.shininess");

	//increment total lights in scene
	m_lightNumber = s_totalLights++;

	//convert light number to string
	lightStr = std::to_string(m_lightNumber);

	lightNumAttenConstStr = "lights[" + lightStr + "].attenuationConst";
	lightNumAttenLinStr = "lights[" + lightStr + "].attenuationLinear";
	lightNumAttenQuadStr = "lights[" + lightStr + "].attenuationQuad";

	m_attenConstID = glGetUniformLocation(shaderProgramID, lightNumAttenConstStr.c_str());
	m_attenLinearID = glGetUniformLocation(shaderProgramID, lightNumAttenLinStr.c_str());
	m_attenQuadID = glGetUniformLocation(shaderProgramID, lightNumAttenQuadStr.c_str());

	m_noiseShaderUniformID = glGetUniformLocation(shaderProgramID, "isNoiseShader");
	m_circleNoiseShaderUniformID = glGetUniformLocation(shaderProgramID, "isCircleNoiseShader");
	m_colorChangeShaderUniformID = glGetUniformLocation(shaderProgramID, "isColorChangeShader");
	m_fireBoxShaderUniformID = glGetUniformLocation(shaderProgramID, "isFireBoxShader");
}

void Buffer::Bind(bool isCube, bool isQuad)
{
	if (isCube)
	{
		//Data that represents colors for quad
		GLfloat cubeColors[72] = { m_color.r, m_color.g, m_color.b, m_color.r, m_color.g, m_color.b,
								   m_color.r, m_color.g, m_color.b, m_color.r, m_color.g, m_color.b,		//Face 1 Front RED

								   m_color.r, m_color.g, m_color.b, m_color.r, m_color.g, m_color.b,
								   m_color.r, m_color.g, m_color.b, m_color.r, m_color.g, m_color.b,		//Face 2 Back MAGENTA

								   m_color.r, m_color.g, m_color.b, m_color.r, m_color.g, m_color.b,
								   m_color.r, m_color.g, m_color.b, m_color.r, m_color.g, m_color.b,		//Face 3 Left BLUE

								   m_color.r, m_color.g, m_color.b, m_color.r, m_color.g, m_color.b,
								   m_color.r, m_color.g, m_color.b, m_color.r, m_color.g, m_color.b,		//Face 4 Right RED

								   m_color.r, m_color.g, m_color.b, m_color.r, m_color.g, m_color.b,
								   m_color.r, m_color.g, m_color.b, m_color.r, m_color.g, m_color.b,		//Face 5 Top MAGENTA

								   m_color.r, m_color.g, m_color.b, m_color.r, m_color.g, m_color.b,
								   m_color.r, m_color.g, m_color.b, m_color.r, m_color.g, m_color.b			//Face 6 Bottom BLUE
		};

		//generate buffers
		glGenBuffers(1, &vertexVBO);
		glGenBuffers(1, &colorVBO);

		if (m_isTextured)
		{
			glGenBuffers(1, &textureVBO);
		}

		glGenBuffers(1, &normalVBO);
		glGenBuffers(1, &EBO);
		glGenVertexArrays(1, &VAO);

		//Bind all VBOs and EBOs within vertex array object (VAO)
		glBindVertexArray(VAO);

			//bind the buffers and fill them and Link VBO with the shader attrib and enable the attrib
			glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);
			glVertexAttribPointer(m_vertexAttributeID, 3, GL_FLOAT, GL_FALSE, 0, 0);
			glEnableVertexAttribArray(m_vertexAttributeID);

			//bind the buffers and fill them and Link VBO with the shader attrib and enable the attrib
			glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(cubeColors), cubeColors, GL_STATIC_DRAW);
			glVertexAttribPointer(m_colorAttributeID, 3, GL_FLOAT, GL_FALSE, 0, 0);
			glEnableVertexAttribArray(m_colorAttributeID);

			if (m_isTextured)
			{
				glBindBuffer(GL_ARRAY_BUFFER, textureVBO);
				glBufferData(GL_ARRAY_BUFFER, sizeof(cubeUVs), cubeUVs, GL_STATIC_DRAW);
				glVertexAttribPointer(m_textureAttributeID, 2, GL_FLOAT, GL_FALSE, 0, 0);
				glEnableVertexAttribArray(m_textureAttributeID);
			}

			if (m_isLit)
			{
				glBindBuffer(GL_ARRAY_BUFFER, normalVBO);
				glBufferData(GL_ARRAY_BUFFER, sizeof(cubeNormals), cubeNormals, GL_STATIC_DRAW);
				glVertexAttribPointer(m_normalAttributeID, 3, GL_FLOAT, GL_FALSE, 0, 0);
				glEnableVertexAttribArray(m_normalAttributeID);
			}
			
			//bind the buffers and fill them and Link VBO with the shader attrib
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cubeIndices), cubeIndices, GL_STATIC_DRAW);

			//Unbind Buffer
			glBindBuffer(GL_ARRAY_BUFFER, 0);

		glBindVertexArray(0);

		if (m_isTextured)
		{
			m_texture.Load(m_textureFile, m_textureID);
		}
	}

	else if (isQuad)
	{
		//Data that represents colors for quad
		GLfloat quadColors[12] = { m_color.r, m_color.g, m_color.b,
								   m_color.r, m_color.g, m_color.b,
								   m_color.r, m_color.g, m_color.b,
								   m_color.r, m_color.g, m_color.b };

		//Create all the VBOs, the EBO and the VAO
		glGenBuffers(1, &vertexVBO);
		glGenBuffers(1, &colorVBO);
		glGenBuffers(1, &normalVBO);
		glGenBuffers(1, &EBO);
		glGenVertexArrays(1, &VAO);

		//bind the VAO which has all the VBOs and EBO inside
		glBindVertexArray(VAO);

			glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);
			glVertexAttribPointer(m_vertexAttributeID, 3, GL_FLOAT, GL_FALSE, 0, 0);
			glEnableVertexAttribArray(m_vertexAttributeID);

			glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(quadColors), quadColors, GL_STATIC_DRAW);
			glVertexAttribPointer(m_colorAttributeID, 3, GL_FLOAT, GL_FALSE, 0, 0);
			glEnableVertexAttribArray(m_colorAttributeID);

			if (m_isLit)
			{
				glBindBuffer(GL_ARRAY_BUFFER, normalVBO);
				glBufferData(GL_ARRAY_BUFFER, sizeof(quadNormals), quadNormals, GL_STATIC_DRAW);
				glVertexAttribPointer(m_normalAttributeID, 3, GL_FLOAT, GL_FALSE, 0, 0);
				glEnableVertexAttribArray(m_normalAttributeID);
			}

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(quadIndices), quadIndices, GL_STATIC_DRAW);

			glBindBuffer(GL_ARRAY_BUFFER, 0);

		glBindVertexArray(0);
	}
}

void Buffer::Draw(bool isCube, bool isQuad)
{
	if (isCube)
	{
		if (m_isTextured)
		{
			if (m_isLit)
			{
				glBindTexture(GL_TEXTURE_2D, m_texture.GetTextureID());
				glUniform1i(m_isLitUniformID, 1);
				glUniform1i(m_isLightUniformID, 0);
				glUniform3fv(m_ambientID, 1, &m_ambient.x);
				glUniform3fv(m_diffuseID, 1, &m_diffuse.x);
				glUniform3fv(m_specularID, 1, &m_specular.x);
				glUniform1f(m_shininessID, m_shininess);

				glUniform1i(m_isTexturedUniformID, 1);
				glUniform1i(m_noiseShaderUniformID, 0);
				glUniform1i(m_circleNoiseShaderUniformID, 0);
				glUniform1i(m_colorChangeShaderUniformID, 0);
				glUniform1i(m_fireBoxShaderUniformID, 0);
			}
			else if (m_isFireBoxShader)
			{
				glBindTexture(GL_TEXTURE_2D, m_texture.GetTextureID());
				glUniform1i(m_isLitUniformID, 0);
				glUniform1i(m_isTexturedUniformID, 1);
				glUniform1i(m_noiseShaderUniformID, 0);
				glUniform1i(m_circleNoiseShaderUniformID, 0);
				glUniform1i(m_colorChangeShaderUniformID, 0);
				glUniform1i(m_fireBoxShaderUniformID, 1);
			}
			else
			{
				glBindTexture(GL_TEXTURE_2D, m_texture.GetTextureID());
				glUniform1i(m_isLitUniformID, 0);
				glUniform1i(m_isTexturedUniformID, 1);
				glUniform1i(m_noiseShaderUniformID, 0);
				glUniform1i(m_circleNoiseShaderUniformID, 0);
				glUniform1i(m_colorChangeShaderUniformID, 0);
				glUniform1i(m_fireBoxShaderUniformID, 0);
			}
		}

		else
		{
			if (m_isNoiseShader)
			{
				glUniform1i(m_isLitUniformID, 0);
				glUniform1i(m_isTexturedUniformID, 0);
				glUniform1i(m_noiseShaderUniformID, 1);
				glUniform1i(m_circleNoiseShaderUniformID, 0);
				glUniform1i(m_colorChangeShaderUniformID, 0);
				glUniform1i(m_fireBoxShaderUniformID, 0);
			}
			else if (m_isCircleNoiseShader)
			{
				glUniform1i(m_isLitUniformID, 0);
				glUniform1i(m_isTexturedUniformID, 0);
				glUniform1i(m_noiseShaderUniformID, 0);
				glUniform1i(m_circleNoiseShaderUniformID, 1);
				glUniform1i(m_colorChangeShaderUniformID, 0);
				glUniform1i(m_fireBoxShaderUniformID, 0);
			}
			else if (m_isColorChangeShader)
			{
				glUniform1i(m_isLitUniformID, 0);
				glUniform1i(m_isTexturedUniformID, 0);
				glUniform1i(m_noiseShaderUniformID, 0);
				glUniform1i(m_circleNoiseShaderUniformID, 0);
				glUniform1i(m_colorChangeShaderUniformID, 1);
				glUniform1i(m_fireBoxShaderUniformID, 0);
			}
			else if (m_isFireBoxShader)
			{
				glBindTexture(GL_TEXTURE_2D, m_texture.GetTextureID());
				glUniform1i(m_isLitUniformID, 0);
				glUniform1i(m_isTexturedUniformID, 0);
				glUniform1i(m_noiseShaderUniformID, 0);
				glUniform1i(m_circleNoiseShaderUniformID, 0);
				glUniform1i(m_colorChangeShaderUniformID, 0);
				glUniform1i(m_fireBoxShaderUniformID, 1);
			}
			else if (m_isLit)
			{
				glUniform1i(m_isLitUniformID, 1);
				glUniform1i(m_isLightUniformID, 0);
				glUniform3fv(m_ambientID, 1, &m_ambient.x);
				glUniform3fv(m_diffuseID, 1, &m_diffuse.x);
				glUniform3fv(m_specularID, 1, &m_specular.x);
				glUniform1f(m_shininessID, m_shininess);

				glUniform1i(m_isTexturedUniformID, 0);
				glUniform1i(m_noiseShaderUniformID, 0);
				glUniform1i(m_circleNoiseShaderUniformID, 0);
				glUniform1i(m_colorChangeShaderUniformID, 0);
				glUniform1i(m_fireBoxShaderUniformID, 0);
			}
			else
			{
				glUniform1i(m_isLitUniformID, 0);
				glUniform1i(m_isTexturedUniformID, 0);
				glUniform1i(m_noiseShaderUniformID, 0);
				glUniform1i(m_circleNoiseShaderUniformID, 0);
				glUniform1i(m_colorChangeShaderUniformID, 0);
				glUniform1i(m_fireBoxShaderUniformID, 0);
			}
		}

		glBindVertexArray(VAO);
			glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		if (m_isTextured)
		{
			glBindTexture(GL_TEXTURE_2D, 0);
		}
	}
	
	else if (isQuad)
	{
		if (m_isNoiseShader)
		{
			glUniform1i(m_isLitUniformID, 0);
			glUniform1i(m_isTexturedUniformID, 0);
			glUniform1i(m_noiseShaderUniformID, 1);
			glUniform1i(m_circleNoiseShaderUniformID, 0);
			glUniform1i(m_colorChangeShaderUniformID, 0);
			glUniform1i(m_fireBoxShaderUniformID, 0);
		}
		else if (m_isCircleNoiseShader)
		{
			glUniform1i(m_isLitUniformID, 0);
			glUniform1i(m_isTexturedUniformID, 0);
			glUniform1i(m_noiseShaderUniformID, 0);
			glUniform1i(m_circleNoiseShaderUniformID, 1);
			glUniform1i(m_colorChangeShaderUniformID, 0);
			glUniform1i(m_fireBoxShaderUniformID, 0);
		}
		else if (m_isColorChangeShader)
		{
			glUniform1i(m_isLitUniformID, 0);
			glUniform1i(m_isTexturedUniformID, 0);
			glUniform1i(m_noiseShaderUniformID, 0);
			glUniform1i(m_circleNoiseShaderUniformID, 0);
			glUniform1i(m_colorChangeShaderUniformID, 1);
			glUniform1i(m_fireBoxShaderUniformID, 0);
		}
		else if (m_isLit)
		{
			glUniform1i(m_isLitUniformID, 1);
			glUniform1i(m_isLightUniformID, 0);
			glUniform3fv(m_ambientID, 1, &m_ambient.x);
			glUniform3fv(m_diffuseID, 1, &m_diffuse.x);
			glUniform3fv(m_specularID, 1, &m_specular.x);
			glUniform1f(m_shininessID, m_shininess);

			glUniform1i(m_isTexturedUniformID, 0);
			glUniform1i(m_noiseShaderUniformID, 0);
			glUniform1i(m_circleNoiseShaderUniformID, 0);
			glUniform1i(m_colorChangeShaderUniformID, 0);
			glUniform1i(m_fireBoxShaderUniformID, 0);
		}
		else
		{
			glUniform1i(m_isLitUniformID, 0);
			glUniform1i(m_isLightUniformID, 0);
			glUniform1i(m_isTexturedUniformID, 0);
			glUniform1i(m_noiseShaderUniformID, 0);
			glUniform1i(m_circleNoiseShaderUniformID, 0);
			glUniform1i(m_colorChangeShaderUniformID, 0);
			glUniform1i(m_fireBoxShaderUniformID, 0);
		}
		
		glBindVertexArray(VAO);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}
}

void Buffer::Destroy()
{
	s_totalLights--;

	//Disable both the vertex and color attributes
	glDisableVertexAttribArray(m_vertexAttributeID);
	glDisableVertexAttribArray(m_colorAttributeID);

	if (m_isTextured)
	{
		glDisableVertexAttribArray(m_textureAttributeID);
		glDeleteBuffers(1, &textureVBO);
		m_texture.Unload();
	}

	//Destroy the buffers
	glDeleteBuffers(1, &vertexVBO);
	glDeleteBuffers(1, &colorVBO);
	glDeleteBuffers(1, &normalVBO);
	glDeleteBuffers(1, &EBO);

	//Destroy the buffers
	glDeleteVertexArrays(1, &VAO);
}