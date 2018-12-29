#ifndef MATERIAL_H
#define MATERIAL_H

#include <string>
#include <glew.h>
#include <glm.hpp>
#include "Texture.h"

class Material
{
public:
	Material();

	float SetShininess(float shininess);
	glm::vec3 SetAmbient(glm::vec3 ambient);
	glm::vec3 SetDiffuse(glm::vec3 diffuse);
	glm::vec3 SetSpecular(glm::vec3 specular);

private:

	float m_shininess;
	glm::vec3 m_ambient;
	glm::vec3 m_diffuse;
	glm::vec3 m_specular;
};

#endif MATERIAL_H