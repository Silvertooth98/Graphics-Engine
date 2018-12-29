#ifndef QUAD_H
#define QUAD_H

#include "GameObject.h"

class Quad : public GameObject
{
public:
	Quad(glm::vec3 position = glm::vec3(0.0f), glm::vec3 scale = glm::vec3(1.0f),
		float rotationAngle = 0.0f, glm::vec3 rotationAxis = glm::vec3(0.0f),
		bool isLit = false, std::string shaderName = "",bool isTextured = false,
		std::string textureFile = "", std::string textureID = "");

	void Create();
	void Draw();
	void Update();
	void Destroy();

	GameObject* m_gameObject;
};

#endif QUAD_H