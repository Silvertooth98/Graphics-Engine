#include "Quad.h"
#include <string>
#include <iostream>

Quad::Quad(glm::vec3 position, glm::vec3 scale, float rotationAngle, glm::vec3 rotationAxis,
		   bool isLit, std::string shaderName, bool isTextured, std::string textureFile, std::string textureID)
{
	m_gameObject = new GameObject(position, scale, rotationAngle, rotationAxis,
		isLit, shaderName, isTextured, textureFile, textureID);
}

void Quad::Create()
{
	m_gameObject->Create(false, true);
}

void Quad::Draw()
{
	m_gameObject->Draw(false, true);
}

void Quad::Update()
{
	m_gameObject->Update();
}

void Quad::Destroy()
{
	m_gameObject->Destroy();
}