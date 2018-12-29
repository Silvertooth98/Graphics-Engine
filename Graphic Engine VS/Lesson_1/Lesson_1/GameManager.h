#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "Singleton.h"
#include "ScreenManager.h"
#include "DebugManager.h"
#include "InputManager.h"
#include "ShaderManager.h"
#include "Camera.h"
#include "Texture.h"
#include "Quad.h"
#include "GameObject.h"
#include "Cube.h"
#include "Light.h"
#include "Model.h"
#include "Material.h"

class GameManager
{

public:

	friend class Singleton<GameManager>;

public:

	GameManager();

	void Initialize();
	void GameSceneSetup();
	void UpdateObjects();
	void DrawObjects();
	void GameLoop();
	void DestroyObjects();
	void Shutdown();

private:

	const Uint8* keyStates = SDL_GetKeyboardState(NULL);

	bool m_canMoveCrate;

	Camera* m_camera = new Camera;

	//Room Setup
	GameObject* m_backWall;
	GameObject* m_floor;
	GameObject* m_leftWall;
	GameObject* m_rightWall;

	//Cubes
	GameObject* m_crateOne;
	GameObject* m_crateTwo;

	//Blocks
	GameObject* m_goldBlock;
	GameObject* m_turquoiseBlock;
	GameObject* m_emeraldBlock;
	GameObject* m_obsidianBlock;
	GameObject* m_silverBlock;
	GameObject* m_copperBlock;
	GameObject* m_chromeBlock;

	//Shader Cubes
	Cube* m_noiseCrate;
	Cube* m_circleNoiseCrate;
	Cube* m_colorChangeCrate;
	Cube* m_fireBoxCrate;

	//Skybox
	Cube* m_sky;

	//Quad
	Quad* m_quad;

	//Lights
	static const int total_lights = 3;
	Light* m_light[total_lights];

	//Models
	Model* m_bedModel;
	Model* m_bedTableModel;
	Model* m_tableModel;
	Model* m_chairModel;
	Model* m_showerModel;
	Model* m_rugModel;
	Model* m_plateModel;
	Model* m_geckoModel;
	Model* m_poufModel;
	Model* m_binModel;
	Model* m_spaceshipModel;

	//Asteroids
	static const int total_asteroids = 4;
	Model* m_asteroidModel[total_asteroids];

	bool isGameOver = false;

	bool m_allLightsControl = true;
	bool m_light1Control = false;
	bool m_light2Control = false;
};

typedef Singleton<GameManager> TheGame;

#endif