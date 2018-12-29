#include "Cube.h"
#include "ShaderManager.h"
#include <iostream>
#include <string>

Cube::Cube(glm::vec3 position, glm::vec3 scale, float rotationAngle, glm::vec3 rotationAxis,
		   bool isLit, std::string shaderName, bool isTextured, std::string textureFile, std::string textureID)
{
	m_gameObject = new GameObject(position, scale, rotationAngle, rotationAxis,
		isLit, shaderName, isTextured, textureFile, textureID);
}

void Cube::Create()
{
	m_gameObject->Create(true, false);
}

void Cube::Draw()
{
	m_gameObject->Draw(true, false);
}

void Cube::Update()
{
	m_gameObject->Update();
}

void Cube::Destroy()
{
	m_gameObject->Destroy();
}