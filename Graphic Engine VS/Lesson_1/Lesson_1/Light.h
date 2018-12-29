#ifndef LIGHT_H
#define LIGHT_H

#include "ShaderManager.h"
#include <glew.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

class Light
{
public:
	enum TYPE { DIRECTIONAL = 1, POINT, SPOT, FLASHLIGHT };
	enum COLOR {
		RUBY, EMERALD, OBSIDIAN, PEARL, TURQUOISE,
		BLACK_PLASTIC, COPPER, SILVER, GOLD, CHROME, NONE
	};

	Light(glm::vec3 position = glm::vec3(0.0f));

	void SetColor(COLOR colorEnum, glm::vec3 color = glm::vec3(1.0f));
	void SetType(TYPE type);
	void SetAmbient(glm::vec3 ambient);
	void SetDiffuse(glm::vec3 diffuse);
	void SetSpecular(glm::vec3 specular);

	void Create();
	void Draw();
	void Update();
	void Destroy();

private:

	//Data that represents vertices for quad
	GLfloat vertices[18] = { -0.5f,  0.5f, 0.0f,
							  0.5f,  0.5f, 0.0f,
							 -0.5f, -0.5f, 0.0f,
							 -0.5f, -0.5f, 0.0f,
							  0.5f,  0.5f, 0.0f,
							  0.5f, -0.5f, 0.0f };

	GLuint VBO;
	GLuint vertexVBO;
	GLuint colorVBO;
	GLuint VAO;

	glm::vec3 m_color;

	glm::vec3 m_lightPosition = glm::vec3(0.0f);
	glm::mat4 m_model;

	float m_lightMoveSpeed = 0.05f;
	bool m_isHoldingShift = false;

	GLuint m_vertModelUniformID = 0;
	GLuint m_fragModelUniformID = 0;

	GLuint m_vertexAttributeID = 0;
	GLuint m_colorAttributeID = 0;

	GLuint m_lightingUniformID = 0;

	GLuint m_lightPositionID = 0;
	GLuint m_ambientID = 0;
	GLuint m_diffuseID = 0;
	GLuint m_specularID = 0;

	GLuint m_isLitUniformID = 0;
	GLuint m_isLightUniformID = 0;

	glm::vec3 m_ambient;
	glm::vec3 m_diffuse;
	glm::vec3 m_specular;

	GLfloat m_attenuationConst;
	GLfloat m_attenuationLinear;
	GLfloat m_attenuationQuad;
	GLuint m_attenConstID = 0;
	GLuint m_attenLinearID = 0;
	GLuint m_attenQuadID = 0;

	GLuint m_lightTypeID = 0;
	TYPE m_lightType;

	GLuint m_lightNumber = 0;

	std::string lightStr;

	static int s_totalLights;

	std::string lightNumPos;
	std::string lightNumAmb;
	std::string lightNumDiff;
	std::string lightNumSpec;
	std::string lightNumAttenConstStr;
	std::string lightNumAttenLinStr;
	std::string lightNumAttenQuadStr;
	std::string lightNumType;

	COLOR m_colorEnum;

	bool m_lightingOn = true;
};

#endif LIGHT_H