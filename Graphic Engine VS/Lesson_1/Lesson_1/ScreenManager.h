#ifndef SCREENMANAGER_H
#define SCREENMANAGER_H

#include "Singleton.h"
#include "DebugManager.h"
#include <SDL.h>
#include <glew.h>

class ScreenManager
{

public:

	friend class Singleton<ScreenManager>;

public:
	ScreenManager();

	bool Initialize(const std::string& filenameInit);
	bool SetupScreen();
	void GlewInit();
	void DisplayProfile();
	void DisplayExtensions();
	void ClearScreen();
	void RenderQuad();
	void BufferSwap();
	void Shutdown();

private:

	bool LoadInitFile(const std::string& filename);

private:

	DebugManager* Debug;

	SDL_Window* m_window;
	SDL_GLContext m_context;

	int m_screenWidth;
	int m_screenHeight;
	bool m_isFullScreen;
	std::string m_gameName;
	int m_openGLMajorVersion;
	int m_openGLMinorVersion;
	std::string m_openGLContext;
};

typedef Singleton<ScreenManager> TheScreen;

#endif