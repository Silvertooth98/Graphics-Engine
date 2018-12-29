#include <iostream>
#include <SDL.h>
#include "ScreenManager.h"
#include "InputManager.h"
#include "DebugManager.h"
#include "GameManager.h"
#include "ShaderManager.h"
//#include "Sprite.h"
//#include <glm.hpp>
//#include <gtc/matrix_transform.hpp>

//Sprite* m_sprite = new Sprite(50, 50);

int main(int argc, char* args[]) //arguments in main parameters as overriding SDL's main
{
	//Initialize the graphics engine using the Game Manager Class
	TheGame::Instance()->Initialize();

	//Initialize Shaders
	TheShader::Instance()->CreateProgram();
	TheShader::Instance()->CreateShaders();
	TheShader::Instance()->Compile("Main.vert", TheShader::Instance()->vertex);
	TheShader::Instance()->Compile("Main.frag", TheShader::Instance()->fragment);
	TheShader::Instance()->Attach();
	TheShader::Instance()->Link();

	//************************************************
	//EMAIL CHALLENGES START
	//************************************************

	TheGame::Instance()->GameSceneSetup();

	TheGame::Instance()->GameLoop();

	TheGame::Instance()->DestroyObjects();

	//*********************************************

	//Shutdown all the shader objects
	TheShader::Instance()->DetachShaders();
	TheShader::Instance()->DestroyShaders();
	TheShader::Instance()->DestroyProgram();

	//Shutting down the OpenGL context, the SDL game window and any other SDL subsystems
	TheGame::Instance()->Shutdown();
	
	return 0;
}