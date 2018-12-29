#ifndef SPRITE_H
#define SPRITE_H

#include "GameObject.h"

class Sprite : public GameObject
{
public:
	//Sprite(glm::vec3 position = glm::vec3(0.0f), glm::vec3 scale = glm::vec3(0.0f),
	//	   std::string textureFile = "", std::string textureID = "");
	Sprite(GLuint width, GLuint height);

	void Create();
	void Draw();
	void Update();
	void Destroy();

private:

	Texture* m_texture = new Texture;

	GLuint vertices[12] = { 0, 1, 0,
							1, 1, 0,
							1, 0, 0,
							0, 0, 0 };

	GLuint colors[12] = { 1, 0, 0,
						  0, 1, 0,
						  0, 0, 1,
						  1, 0, 0 };

	GLuint indices[6] = { 0, 1, 2,
						  2, 1, 3 };

	glm::vec3 m_dimesion;

	GLuint VAO;
	GLuint EBO;
	GLuint vertexVBO;
	GLuint colorVBO;

	glm::vec3 m_spritePosition;
	glm::mat4 m_model;
	GLuint m_modelUniformID = 0;
	GLuint m_vertexAttributeID = 0;
	GLuint m_colorAttributeID = 0;
};

#endif SPRITE_H