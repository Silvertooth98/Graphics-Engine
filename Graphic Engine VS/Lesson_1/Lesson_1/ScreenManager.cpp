#include "ScreenManager.h"
#include <iostream>
#include <fstream>
#include <vector>

ScreenManager::ScreenManager()
{
	m_screenWidth = 0;
	m_screenHeight = 0;
	m_isFullScreen = false;
	m_window = nullptr;
}

bool ScreenManager::Initialize(const std::string& filenameInit)
{
	LoadInitFile(filenameInit);

	std::cout << "My First Window WOOHOO" << std::endl;

	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);

	//enable blending for transparency
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	return true;
}

bool ScreenManager::SetupScreen()
{
	if (m_openGLContext == "CORE")
	{
		//Set a core OpenGL context
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	}
	else if (m_openGLContext == "COMPATIBILITY")
	{
		//Set a compatibility OpenGL context
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
	}
	
	//Set the OpenGL version we wish to use within the context, 4.0
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, m_openGLMajorVersion);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, m_openGLMinorVersion);

	//assign normal window or fullscreen flag based on value passed
	Uint32 screenFlag = (m_isFullScreen) ? SDL_WINDOW_FULLSCREEN : 0;

	//create a game window using caption, width, height and screen mode flag
	m_window = SDL_CreateWindow(m_gameName.c_str(),
								SDL_WINDOWPOS_CENTERED,
								SDL_WINDOWPOS_CENTERED,
								m_screenWidth, m_screenHeight, SDL_WINDOW_OPENGL | screenFlag);

	//Create our game window
	//If wanting fullscreen, put "| SDL_WINDOW_FULLSCREEN" at the end
	//m_window = SDL_CreateWindow("The First Window",
								 //SDL_WINDOWPOS_UNDEFINED,
								 //SDL_WINDOWPOS_UNDEFINED, 1280, 720, SDL_WINDOW_OPENGL);

	//If the window failed to create, it will return 0
	//Meaning we can use error trapping to test it worked
	if (m_window == 0)
	{
		Debug->SetColour(12);
		std::cout << "Game window could not be created" << std::endl;
		Debug->SetColour(7);
	}

	//Use the newly created window handle to create the context
	m_context = SDL_GL_CreateContext(m_window);

	if (m_context == 0)
	{
		Debug->SetColour(12);
		std::cout << "OpenGL context could not be created" << std::endl;
		Debug->SetColour(7);
	}

	return true;
}

void ScreenManager::GlewInit()
{
	//Set glewExperimental to true to expose of all
	//extension functions before intializing glew
	glewExperimental = GL_TRUE;

	//Initialize GLEW
	glewInit();
}

void ScreenManager::DisplayProfile()
{
	//Display the manufacturer of the graphics hardware
	const GLubyte* vendor = glGetString(GL_VENDOR);
	std::cout << vendor << std::endl;

	//Display the make and model of the graphics card
	const GLubyte* renderer = glGetString(GL_RENDERER);
	std::cout << renderer << std::endl;

	//Display the current OpenGL version and mode set
	const GLubyte* gl_version = glGetString(GL_VERSION);
	std::cout << gl_version << std::endl;

	//Display which GLSL version is supported by the graphics card
	const GLubyte* gl_shadingLanguageVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);
	std::cout << gl_shadingLanguageVersion << std::endl;
}

void ScreenManager::DisplayExtensions()
{
	//Uncomment to hide the extensions on the console
	//PFNGLGETSTRINGIPROC glGetStringi = nullptr;

	//Get total number of extensions supported by our graphics card
	GLint totalExtensions;
	glGetIntegerv(GL_NUM_EXTENSIONS, &totalExtensions);

	if (glGetStringi == nullptr)
	{
		Debug->SetColour(14);
		std::cout << "Extension function not supported by your graphics card" << std::endl;
		Debug->SetColour(7);
	}
	else
	{
		//glGetStringi(...)
		Debug->SetColour(11);
		for (GLint i = 0; i < totalExtensions; i++)
		{
			std::cout << "Extension #" << i << " : "
				<< (const char*)glGetStringi(GL_EXTENSIONS, i) << std::endl;
		}
		Debug->SetColour(7);
	}
}

void ScreenManager::ClearScreen()
{
	//Enable the test for depth, allowing for proper 3D
	glEnable(GL_DEPTH_TEST);

	//Clear the frame buffer so next iteration of data can be loaded in
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void ScreenManager::RenderQuad()
{
	//Render a simple quad on the screen (using OLD way)
	glBegin(GL_QUADS);

		//top left colour and vertex of quad
		glColor3f(1, 0, 0);
		glVertex3f(-0.25f, 0.25f, 0.0f);

		//top right colour and vertex of quad
		glColor3f(0, 1, 0);
		glVertex3f(0.25f, 0.25f, 0.0f);

		//bottom right colour and vertex of quad
		glColor3f(0, 0, 1);
		glVertex3f(0.25f, -0.25f, 0.0f);

		//bottom left colour and vertex of quad
		glColor3f(0, 0, 1);
		glVertex3f(-0.25f, -0.25f, 0.0f);

	glEnd();
}

void ScreenManager::BufferSwap()
{
	//Swap the back and front buffers, if double buffering is enabled
	//So that what was rendered in memory can be displayed
	SDL_GL_SwapWindow(m_window);
}

void ScreenManager::Shutdown()
{
	//free OpenGL context
	SDL_GL_DeleteContext(m_context);

	//free SDL game window
	SDL_DestroyWindow(m_window);

	//shut down all SDL subsystems
	SDL_Quit();
}

bool ScreenManager::LoadInitFile(const std::string & filename)
{
	std::cout << "------------------------------------------------" << std::endl;
	std::cout << "PARSE STRING" << std::endl;
	std::cout << std::endl;

	std::fstream gameFile("Data/GameIni.txt", std::ios_base::in);

	std::string line;
	std::vector<std::string> vector;

	if (!gameFile)
	{
		std::cout << "Error opening file" << std::endl;
	}

	else
	{
		while (!gameFile.eof())
		{
			std::getline(gameFile, line);
			std::cout << line << std::endl;

			Debug->ParseString(line, vector, "=");

			std::cout << std::endl;
		}

		m_gameName = vector[1];
		m_screenWidth = (int)(atoi(vector[3].c_str()));
		m_screenHeight = (int)(atoi(vector[5].c_str()));
		m_isFullScreen = (vector[7] == "TRUE");
		m_openGLMajorVersion = (int)(atoi(vector[9].c_str()));
		m_openGLMinorVersion = (int)(atoi(vector[11].c_str()));
		m_openGLContext = (vector[13]);
	}

	gameFile.close();

	std::cout << "------------------------------------------------" << std::endl;

	return false;
}
