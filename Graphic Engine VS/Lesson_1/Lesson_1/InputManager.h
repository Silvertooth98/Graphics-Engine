#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include "Singleton.h"
#include "ShaderManager.h"
#include <SDL.h>
#include <vector>

class InputManager
{

public:

	friend class Singleton<InputManager>;

public:

	int getMouseMotionX() { return m_mouseMotionX; }
	int getMouseMotionY() { return m_mouseMotionY; }

	void Update();
	bool IsXClicked();

private:

	InputManager();
	InputManager(const InputManager&);
	InputManager& operator=(InputManager&);

private:

	SDL_Event m_events;
	const Uint8* keyStates = SDL_GetKeyboardState(NULL);

	std::vector<char> inputVector;

	//int m_mouseMotionX = m_events.motion.xrel;
	//int m_mouseMotionY = m_events.motion.yrel;

	int m_mouseMotionX;
	int m_mouseMotionY;

	bool m_isXClicked;
};

typedef Singleton<InputManager> TheInput;

#endif