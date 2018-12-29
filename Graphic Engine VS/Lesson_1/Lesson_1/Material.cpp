#include "Material.h"

Material::Material()
{
}

float Material::SetShininess(float shininess)
{
	return shininess;
}

glm::vec3 Material::SetAmbient(glm::vec3 ambient)
{
	return glm::vec3(ambient.x, ambient.y, ambient.z);
}

glm::vec3 Material::SetDiffuse(glm::vec3 diffuse)
{
	return glm::vec3(diffuse.x, diffuse.y, diffuse.z);
}

glm::vec3 Material::SetSpecular(glm::vec3 specular)
{
	return glm::vec3(specular.x, specular.y, specular.z);
}