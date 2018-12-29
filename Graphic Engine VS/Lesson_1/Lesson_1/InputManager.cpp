#include "InputManager.h"
#include <iostream>

InputManager::InputManager()
{
}

void InputManager::Update()
{
	SDL_GetGlobalMouseState(&m_mouseMotionX, &m_mouseMotionY);

	while (SDL_PollEvent(&m_events))
	{
		switch (m_events.type)
		{
			case SDL_MOUSEBUTTONDOWN:
			{
				switch (m_events.button.button)
				{
					case SDL_BUTTON_LEFT:
					{
						std::cout << "Left mouse button clicked" << std::endl;
					}
					break;

					case SDL_BUTTON_RIGHT:
					{
						std::cout << "Right mouse button clicked" << std::endl;
					}
					break;

					case SDL_BUTTON_MIDDLE:
					{
						std::cout << "Middle mouse button clicked" << std::endl;
					}
					break;
					}
				break;
			}

			case SDL_MOUSEMOTION:
			{
				std::cout << "X = " << getMouseMotionX() << ", Y = " << getMouseMotionY() << std::endl;
				break;
			}

			case SDL_QUIT:
				{
					m_isXClicked = true;
					break;
				}
			}

		//Attempt to put the keyboard input into a switch statement

		/*switch (m_events.type)
		{
			case SDL_KEYDOWN:
			{
				inputVector.push_back(m_events.key.keysym.sym);
				for (auto i = inputVector.begin(); i != inputVector.end(); i++)
				{
					std::cout << *i;
				}
				std::cout << std::endl;

				if (keyStates[SDL_SCANCODE_BACKSPACE])
				{
					inputVector.pop_back();
					std::cout << "Last char removed from vector:" << std::endl;
					for (auto i = inputVector.begin(); i != inputVector.end(); i++)
					{
						std::cout << *i << std::endl;
					}
				}
			}
			break;
		}*/

		if (keyStates[SDL_SCANCODE_Q] || keyStates[SDL_SCANCODE_ESCAPE])
		{
			m_isXClicked = true;
		}
	}
}

bool InputManager::IsXClicked()
{
	return m_isXClicked;
}