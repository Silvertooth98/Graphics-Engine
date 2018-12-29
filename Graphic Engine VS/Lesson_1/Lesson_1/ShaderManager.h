#ifndef SHADERMANAGER_H
#define SHADERMANAGER_H

#include "Singleton.h"
#include "DebugManager.h"
#include <glew.h>
#include <fstream>
#include <string>

class ShaderManager
{

public:

	friend class Singleton<ShaderManager>;

	enum ShaderEnum { vertex, fragment };

public:

	bool CreateProgram();
	bool CreateShaders();

	bool Compile(const std::string& filename, ShaderEnum enumChoice);
	void Attach();
	bool Link();

	GLuint getProgramID();
	bool getChangeShader();
	bool changeShader();
	
	void DetachShaders();
	void DestroyShaders();
	void DestroyProgram();

private:

	ShaderManager();
	ShaderManager(const ShaderManager&);
	ShaderManager& operator=(ShaderManager&);

private:

	GLuint m_chosenEnumShader;
	GLuint m_shaderProgramID;
	GLuint m_vertexShaderID;
	GLuint m_fragmentShaderID;

	std::fstream file;
	std::string lineText;
	std::string finalString;

	bool m_changeShader = false;

};

typedef Singleton<ShaderManager> TheShader;

#endif