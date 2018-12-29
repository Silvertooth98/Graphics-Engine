#ifndef CUBE_H
#define CUBE_H

#include "GameObject.h"

class Cube : public GameObject
{
public:
	Cube(glm::vec3 position = glm::vec3(0.0f), glm::vec3 scale = glm::vec3(1.0f),
		float rotationAngle = 0.0f, glm::vec3 rotationAxis = glm::vec3(0.0f),
		bool isLit = false, std::string shaderName = "", bool isTextured = false, std::string textureFile = "",
		std::string textureID = "");

public:

	void Create();
	void Draw();
	void Update();
	void Destroy();

	GameObject* m_gameObject;
};

#endif CUBE_H