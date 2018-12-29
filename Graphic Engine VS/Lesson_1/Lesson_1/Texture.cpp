#include "Texture.h"
#include <iostream>

//Initialize the static pointer
std::map<std::string, GLuint>* Texture::s_textureMap = new std::map<std::string, GLuint>;

GLuint Texture::GetID(const std::string& ID)
{

	//first check if texture ID exists within map and if not then you need to load it first
	//if there then just return the ID

	auto it = s_textureMap->find(ID);

	if (it != s_textureMap->end())
	{
		std::cout << "Texture not found in map!" << std::endl;
		return 0;
	}

	return it->second;
}

//function that loads raw image data into memory
//data is then linked to openGL for sampling later
bool Texture::Load(const std::string& filename, const std::string& mapIndex)
{
	std::cout << "Opening texture file..." << std::endl;

	//variables to store all RAW image data
	unsigned char* pixels = nullptr;
	unsigned int width = 0;
	unsigned int height = 0;
	unsigned int depth = 0;
	unsigned int format = 0;

	SDL_Surface* textureData;

	//pointer to reference the raw SDL image data
	textureData = 0;

	//read texture data from file
	textureData = IMG_Load(filename.c_str());

	if (!textureData)
	{
		std::cout << "Error opening texture file!" << std::endl;
		return false;
	}

	//use SDL raw image data and assign to our properties
	pixels = (unsigned char*)textureData->pixels;
	width = textureData->w;
	height = textureData->h;
	depth = textureData->format->BytesPerPixel;
	format = ((depth == 4) ? GL_RGBA : GL_RGB);

	//create an openGL texture object
	glGenTextures(1, &m_ID);

	//bind the texture and set all the properties
	glBindTexture(GL_TEXTURE_2D, m_ID);

		//set magnification and minification filters
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		//set wrap filters
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		//finally create the OGL texture using the above properties
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, pixels);

		//free the original image
		SDL_FreeSurface(textureData);

		//create mipmaps
		glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);

	//add texture ID into our map
	s_textureMap->insert(std::pair<std::string, GLuint>(mapIndex, m_ID));

	std::cout << "File opened OK" << std::endl;

	return true;
}

void Texture::Unload()
{
	glDeleteTextures(1, &m_ID);
}

void Texture::Unload(const std::string & ID)
{
}
