#ifndef BUFFER_H
#define BUFFER_H

#include "Texture.h"
#include <glew.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

class Buffer
{
public:

	Buffer();

	void Enable(glm::vec3 color, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float shiniess,
				bool isLit, std::string shaderName, bool isTextured, std::string textureFile, std::string textureID);

	void Bind(bool isCube, bool isQuad);
	void Draw(bool isCube, bool isQuad);
	void Destroy();

	Texture m_texture;

private:

	glm::vec3 m_color;

	//Data that represents vertices for quad
	GLfloat cubeVertices[72] = { -0.5f,  0.5f,  0.5f,  0.5f,  0.5f,  0.5f,
								  0.5f, -0.5f,  0.5f, -0.5f, -0.5f,  0.5f,		//Face 1 Front Correct
								 -0.5f,  0.5f, -0.5f,  0.5f,  0.5f, -0.5f,
								  0.5f, -0.5f, -0.5f, -0.5f, -0.5f, -0.5f,		//Face 2 Back Correct
								 -0.5f,  0.5f,  0.5f, -0.5f,  0.5f, -0.5f,
								 -0.5f, -0.5f, -0.5f, -0.5f, -0.5f,  0.5f,		//Face 4 Left Correct
								  0.5f,  0.5f,  0.5f,  0.5f,  0.5f, -0.5f,
								  0.5f, -0.5f, -0.5f,  0.5f, -0.5f,  0.5f,		//Face 3 Right Correct
								 -0.5f,  0.5f, -0.5f,  0.5f,  0.5f, -0.5f,
								  0.5f,  0.5f,  0.5f, -0.5f,  0.5f,  0.5f,		//Face 5 Top Correct
								 -0.5f, -0.5f,  0.5f, -0.5f, -0.5f, -0.5f,
								  0.5f, -0.5f, -0.5f,  0.5f, -0.5f,  0.5f };	//Face 6 Bottom Correct

	GLfloat cubeUVs[72] = { 0.0f, 0.0f,		 1.0f, 0.0f,	1.0f, 1.0f,		0.0f, 1.0f,		//Front
							0.0f, 0.0f,		 1.0f, 0.0f,	1.0f, 1.0f,		0.0f, 1.0f,		//Back
							0.0f, 0.0f,		 1.0f, 0.0f,	1.0f, 1.0f,		0.0f, 1.0f,		//Left
							0.0f, 0.0f,		 1.0f, 0.0f,	1.0f, 1.0f,		0.0f, 1.0f,		//Right
							0.0f, 0.0f,		 1.0f, 0.0f,	1.0f, 1.0f,		0.0f, 1.0f,		//Top
							0.0f, 0.0f,		 1.0f, 0.0f,	1.0f, 1.0f,		0.0f, 1.0f };	//Bottom

	//data that represents normals for cube
	GLfloat cubeNormals[72] = {	0.0f,  0.0f, -1.0f,		 0.0f,  0.0f, -1.0f,	  0.0f,  0.0f, -1.0f,	  0.0f,  0.0f, -1.0f,	//Front
								0.0f,  0.0f,  1.0f,		 0.0f,  0.0f,  1.0f,	  0.0f,  0.0f,  1.0f,	  0.0f,  0.0f,  1.0f,	//Back
								1.0f,  0.0f,  0.0f,		 1.0f,  0.0f,  0.0f,	  1.0f,  0.0f,  0.0f,	  1.0f,  0.0f,  0.0f,	//Left
							   -1.0f,  0.0f,  0.0f,	    -1.0f,  0.0f,  0.0f,	 -1.0f,  0.0f,  0.0f,	 -1.0f,  0.0f,  0.0f,	//Right
								0.0f,  1.0f,  0.0f,		 0.0f,  1.0f,  0.0f,	  0.0f,  1.0f,  0.0f,	  0.0f,  1.0f,  0.0f,	//Top
								0.0f, -1.0f,  0.0f,		 0.0f, -1.0f,  0.0f,	  0.0f, -1.0f,  0.0f,	  0.0f, -1.0f,  0.0f,	//Bottom
							   };

	GLuint cubeIndices[36] = { 0,  1,  3,  3,  1,  2,			//Face 1 Front RED
							   4,  5,  7,  7,  5,  6,			//Face 2 Back GREEN
							   8,  9,  11, 11, 9,  10,			//Face 3 Left BLUE
							   12, 13, 15, 15, 13, 14,			//Face 4 Right RED
							   16, 17, 19, 19, 17, 18,			//Face 5 Top GREEN
							   20, 21, 23, 23, 21, 22 };		//Face 6 Bottom BLUE

	//Data that represents vertices for quad
	GLfloat quadVertices[12] = { -0.5f,  0.5f, 0.0f,	//Top Left - 0
								  0.5f,  0.5f, 0.0f,	//Top Right - 1
								 -0.5f, -0.5f, 0.0f,	//Bottom Left - 2
								  0.5f, -0.5f, 0.0f };	//Bottom Right - 3

	GLfloat quadNormals[12] = { 0.0f,  0.0f, -1.0f,		 0.0f,  0.0f, -1.0f,	  0.0f,  0.0f, -1.0f,	  0.0f,  0.0f, -1.0f };

	GLuint quadIndices[6] = { 0, 1, 2,		//tri 1
							  2, 1, 3 };	//tri 2

	bool m_isTextured;
	std::string m_textureFile;
	std::string m_textureID;

	bool m_isLit;

	std::string m_shaderName;
	bool m_isNoiseShader;
	GLuint m_noiseShaderUniformID = 0;
	bool m_isCircleNoiseShader;
	GLuint m_circleNoiseShaderUniformID = 0;
	bool m_isColorChangeShader;
	GLuint m_colorChangeShaderUniformID = 0;
	bool m_isFireBoxShader;
	GLuint m_fireBoxShaderUniformID = 0;

	GLuint vertexVBO;
	GLuint colorVBO;
	GLuint textureVBO;
	GLuint normalVBO;
	GLuint EBO;
	GLuint VAO;

	GLuint m_vertModelUniformID = 0;
	GLuint m_fragModelUniformID = 0;

	GLuint m_isTexturedUniformID = 0;
	GLuint m_vertexAttributeID = 0;
	GLuint m_colorAttributeID = 0;
	GLuint m_textureAttributeID = 0;
	GLuint m_normalAttributeID = 0;

	GLuint m_timeUniformID = 0;

	GLuint m_isLitUniformID = 0;
	GLuint m_isLightUniformID = 0;

	GLuint m_ambientID = 0;
	GLuint m_diffuseID = 0;
	GLuint m_specularID = 0;
	GLuint m_shininessID = 0;

	GLfloat m_shininess;
	glm::vec3 m_ambient;
	glm::vec3 m_diffuse;
	glm::vec3 m_specular;

	GLfloat m_attenuationConst;
	GLfloat m_attenuationLinear;
	GLfloat m_attenuationQuad;
	GLuint m_attenConstID = 0;
	GLuint m_attenLinearID = 0;
	GLuint m_attenQuadID = 0;

	GLuint m_lightNumber;

	std::string lightStr;

	static int s_totalLights;

	std::string lightNumAttenConstStr;
	std::string lightNumAttenLinStr;
	std::string lightNumAttenQuadStr;
};

#endif BUFFER_H