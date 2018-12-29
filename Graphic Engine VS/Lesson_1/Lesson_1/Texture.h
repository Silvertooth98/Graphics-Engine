#ifndef TEXTURE_H
#define TEXTURE_H

#include <map>
#include <string>
#include <glew.h>
#include <vector>
#include <SDL_image.h>

class Texture
{

public:

	GLuint GetID(const std::string& ID);
	GLuint GetTextureID() { return m_ID; }

	bool Load(const std::string& filename, const std::string& mapIndex);

	void Unload(); //unload ALL textures
	void Unload(const std::string& ID); //unload specific texture depending on ID

private:

	static std::map<std::string, GLuint>* s_textureMap;

private:

	GLuint m_ID = 0;

};

#endif TEXTURE_H