#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Texture.h"
#include "ShaderManager.h"
#include "Buffer.h"
#include "Material.h"
#include <glew.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

class GameObject
{
public:

	//My enum for the material of the models
	enum MaterialType {
		RUBY, EMERALD, OBSIDIAN, PEARL, TURQUOISE,
		BLACK_PLASTIC, COPPER, SILVER, GOLD, CHROME
	};

public:
	GameObject(glm::vec3 position = glm::vec3(0.0f), glm::vec3 scale = glm::vec3(1.0f),
		float rotationAngle = 0.0f, glm::vec3 rotationAxis = glm::vec3(0.0f),
		bool isLit = false, std::string shaderName = "", bool isTextured = false,
		std::string textureFile = "", std::string textureID = "");

	void SetColor(glm::vec3 color = glm::vec3(1.0f));

	void SetMaterial(MaterialType materialType);

	void SetAmbient(glm::vec3 ambient);
	void SetDiffuse(glm::vec3 diffuse);
	void SetSpecular(glm::vec3 specular);
	void SetShininess(float shininess);

public:

	void Create(bool isCube, bool isQuad);
	void Draw(bool isCube, bool isQuad);
	void Update();
	void Destroy();

	Texture m_texture;
	Material* m_material;

private:

	Buffer* m_buffer = new Buffer;

	glm::vec3 m_color;

	float m_MoveSpeed = 0.05f;
	float m_RotationAngle;
	glm::vec3 m_RotationAxis;
	glm::vec3 m_Scale;
	glm::vec3 m_Position;
	glm::mat4 m_model;

	glm::mat3 normalMatrix;
	GLuint m_normalMatrixUniformID = 0;

	GLuint m_vertModelUniformID = 0;
	GLuint m_fragModelUniformID = 0;

	bool m_isHoldingShift;

	bool m_isLit;
	bool m_isTextured;
	std::string m_textureFile;
	std::string m_textureID;
	std::string m_shaderName;

	glm::vec3 m_ambient;
	glm::vec3 m_diffuse;
	glm::vec3 m_specular;
	float m_shininess;
};

#endif GAMEOBJECT_H