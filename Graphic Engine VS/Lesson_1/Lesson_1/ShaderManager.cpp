#include "ShaderManager.h"
#include <fstream>
#include <iostream>
#include <string>

ShaderManager::ShaderManager()
{

	m_shaderProgramID = 0;
	m_vertexShaderID = 0;
	m_fragmentShaderID = 0;

}

//Create the shader program which encapsulates the 2 shader objects
bool ShaderManager::CreateProgram()
{
	m_shaderProgramID = glCreateProgram();

	if (!m_shaderProgramID)
	{
		TheDebug::Instance()->ShaderProgramError();
		return false;
	}

	return true;

}

bool ShaderManager::CreateShaders()
{

	m_vertexShaderID = glCreateShader(GL_VERTEX_SHADER);

	if (!m_vertexShaderID)
	{
		TheDebug::Instance()->ShaderCreationError();
		return false;
	}

	m_fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	if (!m_fragmentShaderID)
	{
		TheDebug::Instance()->ShaderCreationError();
		return false;
	}

	return false;

}

//Add parameters for file name and enum number
bool ShaderManager::Compile(const std::string& filename, ShaderEnum enumChoice)
{
	
	lineText.clear();
	finalString.clear();

	//0 is vertex
	if (enumChoice == 0)
	{
		m_chosenEnumShader = m_vertexShaderID;
	}
	//1 is fragment
	else if (enumChoice == 1)
	{
		m_chosenEnumShader = m_fragmentShaderID;
	}

	//Open the shader file
	file.open(filename);

	if (!file)
	{
		TheDebug::Instance()->SetColour(12);
		std::cout << filename << " not found, error" << std::endl;
		TheDebug::Instance()->SetColour(7);
	}

	while (!file.eof())
	{
		getline(file, lineText);
		finalString += lineText + '\n';
	}

	file.close();

	TheDebug::Instance()->SetColour(13);
	if (enumChoice == 0)
	{
		std::cout << "Compiling vertex shader..." << std::endl;
	}
	else if (enumChoice == 1)
	{
		std::cout << "Compiling fragment shader..." << std::endl;
	}

	TheDebug::Instance()->SetColour(7);

	//Compile the shader
	const GLchar* finalCode = (const GLchar*)(finalString.c_str()); //Prepares the string and converts it to a GLchar

	//Send the address of finalCode to OpenGL
	glShaderSource(m_chosenEnumShader, 1, &finalCode, nullptr); //Send the address of the GLchar
	glCompileShader(m_chosenEnumShader);						//Compiles the shader

	//Check for errors
	GLint compileResult;
	glGetShaderiv(m_chosenEnumShader, GL_COMPILE_STATUS, &compileResult);

	if (compileResult == GL_TRUE)
	{
		TheDebug::Instance()->SetColour(10);
		if (enumChoice == 0)
		{
			std::cout << "Compile of vertex shader successful" << std::endl;
		}
		else if (enumChoice == 1)
		{
			std::cout << "Compile of fragment shader successful" << std::endl;
		}
		TheDebug::Instance()->SetColour(7);
		std::cout << "------------------------------------------------" << std::endl;

	}

	//If something went wrong during shader compiling, print the errors that occurred onto the console
	else
	{
		TheDebug::Instance()->SetColour(12);

		GLchar error[1000];
		GLsizei length = 1000;

		if (enumChoice == 0)
		{
			std::cout << "Here are the errors that occurred in the vertex shader:" << std::endl;

			glGetShaderInfoLog(m_chosenEnumShader, 1000, &length, error);

			std::cout << error << std::endl;
		}
		else if (enumChoice == 1)
		{
			std::cout << "Here are the errors that occurred in the fragment shader:" << std::endl;

			glGetShaderInfoLog(m_chosenEnumShader, 1000, &length, error);

			std::cout << error << std::endl;
		}
		
		TheDebug::Instance()->SetColour(7);

		return false;
	}

	return false;
}

void ShaderManager::Attach()
{

	glAttachShader(m_shaderProgramID, m_vertexShaderID);
	glAttachShader(m_shaderProgramID, m_fragmentShaderID);

}

bool ShaderManager::Link()
{

	GLint linkResult = 0;

	TheDebug::Instance()->SetColour(13);
	std::cout << "Linking program..." << std::endl;
	TheDebug::Instance()->SetColour(7);

	//Link the program
	glLinkProgram(m_shaderProgramID);

	//Use the program
	glUseProgram(m_shaderProgramID);

	//Checking if something went wrong during linking and storing it in linkResult
	glGetProgramiv(m_shaderProgramID, GL_LINK_STATUS, &linkResult);

	if (linkResult == GL_TRUE)
	{
		TheDebug::Instance()->SetColour(10);
		std::cout << "Linking successful" << std::endl;
		TheDebug::Instance()->SetColour(7);
		std::cout << "------------------------------------------------" << std::endl;
		return true;
	}
	else
	{
		TheDebug::Instance()->SetColour(12);

		GLchar error[1000];
		GLsizei length = 1000;

		std::cout << "Here are the errors that occurred in the linking:" << std::endl;

		glGetProgramInfoLog(m_shaderProgramID, 1000, &length, error);

		std::cout << error << std::endl;

		TheDebug::Instance()->SetColour(7);

		return false;
	}

	return true;

}

GLuint ShaderManager::getProgramID()
{
	return m_shaderProgramID;
}

bool ShaderManager::getChangeShader()
{
	return m_changeShader;
}

bool ShaderManager::changeShader()
{
	if (m_changeShader == true)
	{
		m_changeShader = false;
		return m_changeShader;
	}

	if (m_changeShader == false)
	{
		m_changeShader = true;
		return m_changeShader;
	}
}

void ShaderManager::DetachShaders()
{

	glDetachShader(m_shaderProgramID, m_vertexShaderID);
	glDetachShader(m_shaderProgramID, m_fragmentShaderID);
	glDetachShader(m_shaderProgramID, m_chosenEnumShader);

}

void ShaderManager::DestroyShaders()
{

	glDeleteShader(m_vertexShaderID);
	glDeleteShader(m_fragmentShaderID);
	glDeleteShader(m_chosenEnumShader);

}

void ShaderManager::DestroyProgram()
{

	glDeleteProgram(m_shaderProgramID);

}