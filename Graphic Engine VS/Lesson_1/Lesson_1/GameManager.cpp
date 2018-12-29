#include "GameManager.h"

GameManager::GameManager()
{
}

void GameManager::Initialize()
{
	//Initialize SDL
	TheScreen::Instance()->Initialize("Data/GameIni.txt");

	//Setup the screen
	TheScreen::Instance()->SetupScreen();

	//Initialize GLEW
	TheScreen::Instance()->GlewInit();

	//Display the supported OpenGL hardware
	TheScreen::Instance()->DisplayProfile();

	//Display the extensions within the screenmanager
	TheScreen::Instance()->DisplayExtensions();

	//Complete checks for errors within SDL, GLEW and the Shader Program
	TheDebug::Instance()->ErrorLog();
}

void GameManager::GameSceneSetup()
{
	//Room Setup
	m_backWall = new GameObject(glm::vec3(0.0f, 0.0f, -12.25f), glm::vec3(16.0f, 4.0f, 0.3f), 0.0f, glm::vec3(0.0f, 1.0f, 0.0f), true, "NONE", true, "Textures/Brick_Wall.jpg", "wall");
	m_floor = new GameObject(glm::vec3(0.0f, -2.15f, -8.35f), glm::vec3(16.0f, 8.0f, 0.3f), 90.0f, glm::vec3(1.0f, 0.0f, 0.0f), true, "NONE", true, "Textures/Floor.jpg", "floor");
	m_leftWall = new GameObject(glm::vec3(-7.8f, 0.0f, -8.35f), glm::vec3(8.0f, 4.0f, 0.3f), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f), true, "NONE", true, "Textures/Brick_Wall.jpg", "wall");
	m_rightWall = new GameObject(glm::vec3(7.8f, 0.0f, -8.35f), glm::vec3(8.0f, 4.0f, 0.3f), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f), true, "NONE", true, "Textures/Brick_Wall.jpg", "wall");

	//Crates
	m_crateOne = new GameObject(glm::vec3(3.25f, -1.5f, -10.25f), glm::vec3(1.0f), 45.0f, glm::vec3(0.0f, 1.0f, 0.0f), true, "NONE", true, "Textures/Crate.png", "crate");
	m_crateTwo = new GameObject(glm::vec3(2.5f, -1.5f, -11.0f), glm::vec3(1.0f), 45.0f, glm::vec3(0.0f, 1.0f, 0.0f), true, "NONE", true, "Textures/Crate.png", "crate");

	//Material Blocks
	m_goldBlock = new GameObject(glm::vec3(-2.0f, 4.5f, -6.5f), glm::vec3(1.0f, 0.5f, 0.5f), 45.0f, glm::vec3(0.0f, 1.0f, 1.0f), true, "NONE", true, "Textures/goldBlock.jpeg", "goldBlock");
	m_turquoiseBlock = new GameObject(glm::vec3(3.0f, 4.5f, -8.0f), glm::vec3(0.5f, 2.0f, 0.5f), 45.0f, glm::vec3(1.0f, 0.0f, 1.0f), true, "NONE", true, "Textures/turquoiseBlock.jpeg", "turquoiseBlock");
	m_emeraldBlock = new GameObject(glm::vec3(0.0f, 3.5f, -9.5f), glm::vec3(1.0f, 1.0f, 2.0f), 60.0f, glm::vec3(0.0f, 0.0f, 1.0f), true, "NONE", true, "Textures/emeraldBlock.jpeg", "emeraldBlock");
	m_obsidianBlock = new GameObject(glm::vec3(-5.0f, 5.5f, -9.5f), glm::vec3(0.3f, 3.0f, 0.3f), 30.0f, glm::vec3(0.0f, 0.0f, 1.0f), true, "NONE", true, "Textures/obsidianBlock.jpeg", "obsidianBlock");
	m_silverBlock = new GameObject(glm::vec3(2.0f, 6.5f, -5.5f), glm::vec3(0.75f, 1.0f, 2.0f), 60.0f, glm::vec3(1.0f, 0.0f, 0.0f), true, "NONE", true, "Textures/silverBlock.jpeg", "silverBlock");
	m_copperBlock = new GameObject(glm::vec3(-3.0f, 5.5f, -7.5f), glm::vec3(1.0f, 2.0f, 0.5f), 75.0f, glm::vec3(0.0f, 1.0f, 0.0f), true, "NONE", true, "Textures/copperBlock.jpg", "copperBlock");
	m_chromeBlock = new GameObject(glm::vec3(5.0f, 3.5f, -9.5f), glm::vec3(0.5f, 1.0f, 2.0f), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f), true, "NONE", true, "Textures/chromeBlock.jpg", "chromeBlock");

	//Shader Crates
	m_noiseCrate = new Cube(glm::vec3(2.875f, -0.5f, -10.625f), glm::vec3(1.0f), 45.0f, glm::vec3(0.0f, 1.0f, 0.0f), false, "NOISE", false);
	m_circleNoiseCrate = new Cube(glm::vec3(-1.5f, -1.5f, -11.0f), glm::vec3(1.0f), 45.0f, glm::vec3(0.0f, 1.0f, 0.0f), false, "CIRCLE_NOISE", false);
	m_colorChangeCrate = new Cube(glm::vec3(-3.5f, -1.5f, -11.0f), glm::vec3(1.0f), -45.0f, glm::vec3(0.0f, 1.0f, 0.0f), false, "COLORS", false);
	m_fireBoxCrate = new Cube(glm::vec3(-5.0f, -1.5f, -9.5f), glm::vec3(1.0f), 45.0f, glm::vec3(0.0f, 1.0f, 0.0f), false, "FIREBOX", true, "Textures/Crate.png", "crate");

	//Skybox
	m_sky = new Cube(glm::vec3(0.0f, 0.0f, -5.0f), glm::vec3(200.0f, 200.0, 200.0f), 0.0f, glm::vec3(0.0f, 1.0f, 0.0f), false, "NONE", true, "Textures/Stars.jpeg", "Stars");

	//Quad
	m_quad = new Quad(glm::vec3(0.0f, 0.0f, -12.085f), glm::vec3(2.0f), 0.0f, glm::vec3(0, 1, 0), true);

	//Models
	m_bedModel = new Model();
	m_bedTableModel = new Model();
	m_tableModel = new Model();
	m_chairModel = new Model();
	m_showerModel = new Model();
	m_rugModel = new Model();
	m_plateModel = new Model();
	m_geckoModel = new Model();
	m_poufModel = new Model();
	m_binModel = new Model();
	m_spaceshipModel = new Model();

	for (int i = 0; i < total_asteroids; i++)
	{
		m_asteroidModel[i] = new Model();
	}

	//Directional light
	m_light[0] = new Light(glm::vec3(0.0f, 5.0f, -5.5f));

	//Point lights
	m_light[1] = new Light(glm::vec3(7.0f, 0.5f, -8.0f));
	m_light[2] = new Light(glm::vec3(-7.0f, 0.5f, -8.0f));

	m_camera->ProjectionSetup();

	m_light[0]->SetColor(m_light[0]->NONE, glm::vec3(1.0f, 1.0f, 1.0f));
	m_light[0]->SetType(m_light[0]->DIRECTIONAL);
	m_light[0]->SetAmbient(glm::vec3(10.0f, 10.0f, 10.0f));
	m_light[0]->SetDiffuse(glm::vec3(50.0f, 50.0f, 50.0f));
	m_light[0]->SetSpecular(glm::vec3(50.0f, 50.0f, 50.0f));
	m_light[0]->Create();
	m_light[0]->Draw();

	m_light[1]->SetColor(m_light[1]->EMERALD, glm::vec3(0.0f, 1.0f, 0.0f));
	m_light[1]->SetType(m_light[1]->POINT);
	m_light[1]->Create();
	m_light[1]->Draw();

	m_light[2]->SetColor(m_light[2]->RUBY, glm::vec3(1.0f, 0.0f, 0.0f));
	m_light[2]->SetType(m_light[2]->POINT);
	m_light[2]->Create();
	m_light[2]->Draw();

	m_backWall->SetAmbient(glm::vec3(0.5f, 0.5f, 0.5f));
	m_backWall->SetDiffuse(glm::vec3(0.5f, 0.5f, 0.5f));
	m_backWall->SetSpecular(glm::vec3(0.5f, 0.5f, 0.5f));
	m_backWall->SetShininess(0.3f);
	m_backWall->Create(true, false);
	m_backWall->Draw(true, false);

	m_crateOne->SetAmbient(glm::vec3(0.5f, 0.5f, 0.5f));
	m_crateOne->SetDiffuse(glm::vec3(0.5f, 0.5f, 0.5f));
	m_crateOne->SetSpecular(glm::vec3(0.5f, 0.5f, 0.5f));
	m_crateOne->SetShininess(0.3f);
	m_crateOne->Create(true, false);
	m_crateOne->Draw(true, false);

	m_crateTwo->SetAmbient(glm::vec3(0.5f, 0.5f, 0.5f));
	m_crateTwo->SetDiffuse(glm::vec3(0.5f, 0.5f, 0.5f));
	m_crateTwo->SetSpecular(glm::vec3(0.5f, 0.5f, 0.5f));
	m_crateTwo->SetShininess(0.3f);
	m_crateTwo->Create(true, false);
	m_crateTwo->Draw(true, false);

	m_goldBlock->SetColor(glm::vec3(1.0f, 1.0f, 0.0f));
	m_goldBlock->SetMaterial(m_goldBlock->GOLD);
	m_goldBlock->Create(true, false);
	m_goldBlock->Draw(true, false);

	m_turquoiseBlock->SetColor(glm::vec3(0.0f, 1.0f, 1.0f));
	m_turquoiseBlock->SetMaterial(m_turquoiseBlock->TURQUOISE);
	m_turquoiseBlock->Create(true, false);
	m_turquoiseBlock->Draw(true, false);

	m_emeraldBlock->SetColor(glm::vec3(0.0f, 1.0f, 0.0f));
	m_emeraldBlock->SetMaterial(m_emeraldBlock->TURQUOISE);
	m_emeraldBlock->Create(true, false);
	m_emeraldBlock->Draw(true, false);

	m_obsidianBlock->SetColor(glm::vec3(1.0f, 0.0f, 1.0f));
	m_obsidianBlock->SetMaterial(m_obsidianBlock->OBSIDIAN);
	m_obsidianBlock->Create(true, false);
	m_obsidianBlock->Draw(true, false);

	m_silverBlock->SetColor(glm::vec3(0.75f, 0.75f, 0.75f));
	m_silverBlock->SetMaterial(m_silverBlock->SILVER);
	m_silverBlock->Create(true, false);
	m_silverBlock->Draw(true, false);

	m_copperBlock->SetColor(glm::vec3(0.72f, 0.45f, 0.20f));
	m_copperBlock->SetMaterial(m_silverBlock->COPPER);
	m_copperBlock->Create(true, false);
	m_copperBlock->Draw(true, false);

	m_chromeBlock->SetColor(glm::vec3(0.80f, 0.75f, 0.70f));
	m_chromeBlock->SetMaterial(m_silverBlock->CHROME);
	m_chromeBlock->Create(true, false);
	m_chromeBlock->Draw(true, false);

	m_noiseCrate->m_gameObject->SetColor(glm::vec3(1.0f, 0.0f, 1.0f));
	m_noiseCrate->Create();
	m_noiseCrate->Draw();

	m_circleNoiseCrate->m_gameObject->SetColor(glm::vec3(1.0f, 0.5f, 0.0f));
	m_circleNoiseCrate->Create();
	m_circleNoiseCrate->Draw();

	m_colorChangeCrate->m_gameObject->SetColor(glm::vec3(1.0f, 0.0f, 1.0f));
	m_colorChangeCrate->Create();
	m_colorChangeCrate->Draw();

	m_fireBoxCrate->SetAmbient(glm::vec3(0.5f, 0.5f, 0.5f));
	m_fireBoxCrate->SetDiffuse(glm::vec3(0.5f, 0.5f, 0.5f));
	m_fireBoxCrate->SetSpecular(glm::vec3(0.5f, 0.5f, 0.5f));
	m_fireBoxCrate->SetShininess(0.1f);
	m_fireBoxCrate->m_gameObject->SetColor(glm::vec3(1.0f, 1.0f, 1.0f));
	m_fireBoxCrate->Create();
	m_fireBoxCrate->Draw();

	m_sky->Create();
	m_sky->Draw();

	m_floor->SetAmbient(glm::vec3(0.25f, 0.25f, 0.25f));
	m_floor->SetDiffuse(glm::vec3(0.7f, 0.7f, 0.7f));
	m_floor->SetSpecular(glm::vec3(0.7f, 0.7f, 0.7f));
	m_floor->SetShininess(76.8f);
	m_floor->Create(true, false);
	m_floor->Draw(true, false);

	m_leftWall->SetAmbient(glm::vec3(0.5f, 0.5f, 0.5f));
	m_leftWall->SetDiffuse(glm::vec3(0.5f, 0.5f, 0.5f));
	m_leftWall->SetSpecular(glm::vec3(0.5f, 0.5f, 0.5f));
	m_leftWall->SetShininess(0.3f);
	m_leftWall->Create(true, false);
	m_leftWall->Draw(true, false);

	m_rightWall->SetAmbient(glm::vec3(0.5f, 0.5f, 0.5f));
	m_rightWall->SetDiffuse(glm::vec3(0.5f, 0.5f, 0.5f));
	m_rightWall->SetSpecular(glm::vec3(0.5f, 0.5f, 0.5f));
	m_rightWall->SetShininess(0.3f);
	m_rightWall->Create(true, false);
	m_rightWall->Draw(true, false);

	m_quad->m_gameObject->SetColor(glm::vec3(0.0f, 0.0f, 1.0f));
	m_quad->Create();
	m_quad->Draw();

	m_bedModel->Create();
	m_bedModel->LoadTexture("Textures/Model_Textures/Bedding.jpeg", "BEDDING_TEX");
	m_bedModel->IsTextured() = true;
	m_bedModel->SetMaterial(m_bedModel->SILVER);
	m_bedModel->SetPosition(-6.25f, -2.0f, -7.0f);
	m_bedModel->SetRotation(0.0f, -90.0f, 0.0f);
	m_bedModel->SetScale(1.2f, 1.2f, 1.2f);
	m_bedModel->LoadModel("Models/Bed_1.obj");

	m_bedTableModel->Create();
	m_bedTableModel->LoadTexture("Textures/Model_Textures/Bed_Table.jpeg", "BEDTABLE_TEX");
	m_bedTableModel->IsTextured() = true;
	m_bedTableModel->SetMaterial(m_bedTableModel->RUBY);
	m_bedTableModel->SetPosition(-7.25f, -2.0f, -5.45f);
	m_bedTableModel->SetRotation(0.0f, 90.0f, 0.0f);
	m_bedTableModel->SetScale(1.15f, 1.15f, 1.15f);
	m_bedTableModel->LoadModel("Models/NightTable.obj");

	m_tableModel->Create();
	m_tableModel->LoadTexture("Textures/Model_Textures/Table.jpeg", "TABLE_TEX");
	m_tableModel->IsTextured() = true;
	m_tableModel->SetMaterial(m_tableModel->OBSIDIAN);
	m_tableModel->SetPosition(0.0f, -2.0f, -7.5f);
	m_tableModel->SetRotation(0.0f, 0.0f, 0.0f);
	m_tableModel->SetScale(0.25f, 0.25f, 0.25f);
	m_tableModel->LoadModel("Models/Table.obj");

	m_chairModel->Create();
	m_chairModel->LoadTexture("Textures/Model_Textures/Chair.jpeg", "CHAIR_TEX");
	m_chairModel->IsTextured() = true;
	m_chairModel->SetMaterial(m_chairModel->RUBY);
	m_chairModel->SetPosition(-1.0f, -2.0f, -7.5f);
	m_chairModel->SetRotation(0.0f, 0.0f, 0.0f);
	m_chairModel->SetScale(1.3f, 1.3f, 1.3f);
	m_chairModel->LoadModel("Models/Chair_1.obj");

	m_showerModel->Create();
	m_showerModel->LoadTexture("Textures/Model_Textures/Shower.jpeg", "SHOWER_TEX");
	m_showerModel->IsTextured() = true;
	m_showerModel->SetShininess(50.0f);
	m_showerModel->SetAmbient(0.25f, 0.25f, 0.25f);
	m_showerModel->SetDiffuse(0.45f, 0.95f, 0.45f);
	m_showerModel->SetSpecular(0.5f, 0.5f, 0.5f);
	m_showerModel->SetPosition(7.0f, -2.0f, -11.35f);
	m_showerModel->SetRotation(0.0f, -90.0f, 0.0f);
	m_showerModel->SetScale(1.5f, 1.5f, 1.5f);
	m_showerModel->LoadModel("Models/Shower.obj");

	m_rugModel->Create();
	m_rugModel->LoadTexture("Textures/Model_Textures/Rug.jpeg", "RUG_TEX");
	m_rugModel->IsTextured() = true;
	m_rugModel->SetMaterial(m_rugModel->TURQUOISE);
	m_rugModel->SetPosition(0.0f, -2.0f, -7.5f);
	m_rugModel->SetRotation(0.0f, -90.0f, 0.0f);
	m_rugModel->SetScale(2.5f, 2.5f, 2.5f);
	m_rugModel->LoadModel("Models/Rug.obj");

	m_plateModel->Create();
	m_plateModel->LoadTexture("Textures/Model_Textures/Plate.jpeg", "PLATE_TEX");
	m_plateModel->IsTextured() = true;
	m_plateModel->SetMaterial(m_plateModel->GOLD);
	m_plateModel->SetPosition(0.0f, -1.2f, -7.5f);
	m_plateModel->SetRotation(0.0f, -90.0f, 0.0f);
	m_plateModel->SetScale(1.75f, 1.75f, 1.75f);
	m_plateModel->LoadModel("Models/Plate.obj");

	m_geckoModel->Create();
	m_geckoModel->LoadShader("COLORS");
	m_geckoModel->IsTextured() = false;
	m_geckoModel->SetPosition(4.0f, 0.75f, -12.08f);
	m_geckoModel->SetRotation(90.0f, 0.0f, 0.0f);
	m_geckoModel->SetScale(0.05f, 0.05f, 0.05f);
	m_geckoModel->LoadModel("Models/Gecko.obj");

	m_poufModel->Create();
	m_poufModel->LoadTexture("Textures/Model_Textures/Pouf.jpeg", "POUF_TEX");
	m_poufModel->IsTextured() = true;
	m_poufModel->SetMaterial(m_poufModel->EMERALD);
	m_poufModel->SetPosition(-4.5f, -2.0f, -7.0f);
	m_poufModel->SetRotation(0.0f, 90.0f, 0.0f);
	m_poufModel->SetScale(1.0f, 1.0f, 1.0f);
	m_poufModel->LoadModel("Models/Pouf.obj");

	m_binModel->Create();
	m_binModel->LoadTexture("Textures/Model_Textures/Bin.jpeg", "BIN_TEX");
	m_binModel->IsTextured() = true;
	m_binModel->SetMaterial(m_binModel->BLACK_PLASTIC);
	m_binModel->SetPosition(-6.5f, -2.0f, -11.0f);
	m_binModel->SetRotation(0.0f, 90.0f, 0.0f);
	m_binModel->SetScale(4.0f, 4.0f, 4.0f);
	m_binModel->LoadModel("Models/Bin.obj");

	m_spaceshipModel->Create();
	m_spaceshipModel->LoadTexture("Textures/Model_Textures/Spaceship.png", "SPACESHIP_TEX");
	m_spaceshipModel->IsTextured() = true;
	m_spaceshipModel->SetMaterial(m_spaceshipModel->BLACK_PLASTIC);
	m_spaceshipModel->SetPosition(25.0f, 0.0f, -10.0f);
	m_spaceshipModel->SetRotation(0.0f, 180.0f, -45.0f);
	m_spaceshipModel->SetScale(1.0f, 1.0f, 1.0f);
	m_spaceshipModel->LoadModel("Models/Spaceship.obj");

	m_asteroidModel[0]->Create();
	m_asteroidModel[0]->LoadTexture("Textures/Model_Textures/Asteroid_1.png", "ASTEROID_1_TEX");
	m_asteroidModel[0]->IsTextured() = true;
	m_asteroidModel[0]->SetMaterial(m_asteroidModel[0]->OBSIDIAN);
	m_asteroidModel[0]->SetPosition(-6.5f, 4.5f, -11.0f);
	m_asteroidModel[0]->SetRotation(0.0f, 90.0f, 0.0f);
	m_asteroidModel[0]->SetScale(0.15f, 0.15f, 0.15f);
	m_asteroidModel[0]->LoadModel("Models/Asteroid_1.obj");

	m_asteroidModel[1]->Create();
	m_asteroidModel[1]->LoadTexture("Textures/Model_Textures/Asteroid_2.png", "ASTEROID_2_TEX");
	m_asteroidModel[1]->IsTextured() = true;
	m_asteroidModel[1]->SetMaterial(m_asteroidModel[1]->OBSIDIAN);
	m_asteroidModel[1]->SetPosition(-6.5f, 6.5f, -25.0f);
	m_asteroidModel[1]->SetRotation(0.0f, 90.0f, 0.0f);
	m_asteroidModel[1]->SetScale(0.5f, 0.5f, 0.5f);
	m_asteroidModel[1]->LoadModel("Models/Asteroid_2.obj");

	m_asteroidModel[2]->Create();
	m_asteroidModel[2]->LoadTexture("Textures/Model_Textures/Asteroid_1.png", "ASTEROID_4_TEX");
	m_asteroidModel[2]->IsTextured() = true;
	m_asteroidModel[2]->SetMaterial(m_asteroidModel[3]->OBSIDIAN);
	m_asteroidModel[2]->SetPosition(4.5f, 6.5f, -11.0f);
	m_asteroidModel[2]->SetRotation(90.0f, 0.0f, 45.0f);
	m_asteroidModel[2]->SetScale(0.15f, 0.15f, 0.15f);
	m_asteroidModel[2]->LoadModel("Models/Asteroid_1.obj");

	m_asteroidModel[3]->Create();
	m_asteroidModel[3]->LoadTexture("Textures/Model_Textures/Asteroid_2.png", "ASTEROID_5_TEX");
	m_asteroidModel[3]->IsTextured() = true;
	m_asteroidModel[3]->SetMaterial(m_asteroidModel[4]->OBSIDIAN);
	m_asteroidModel[3]->SetPosition(6.5f, 10.0f, -45.0f);
	m_asteroidModel[3]->SetRotation(0.0f, 90.0f, 45.0f);
	m_asteroidModel[3]->SetScale(0.5f, 0.5f, 0.5f);
	m_asteroidModel[3]->LoadModel("Models/Asteroid_2.obj");

	m_camera->CameraSetup();
}

void GameManager::UpdateObjects()
{
	m_bedModel->Update();
	m_bedTableModel->Update();
	m_tableModel->Update();
	m_chairModel->Update();
	m_showerModel->Update();
	m_rugModel->Update();
	m_plateModel->Update();
	m_geckoModel->Update();
	m_poufModel->Update();
	m_binModel->Update();
	m_spaceshipModel->Update();

	for (int i = 0; i < total_asteroids; i++)
	{
		m_asteroidModel[i]->Update();
	}

	const Uint8* keyStates = SDL_GetKeyboardState(NULL);

	//Input to control one of the lights only
	if (keyStates[SDL_SCANCODE_L] && keyStates[SDL_SCANCODE_I])
	{
		m_allLightsControl = false;
		m_light1Control = true;
		m_light2Control = false;
	}
	//Input to control the other light only
	if (keyStates[SDL_SCANCODE_L] && keyStates[SDL_SCANCODE_J])
	{
		m_allLightsControl = false;
		m_light1Control = false;
		m_light2Control = true;
	}
	//Inpit to control all the lights
	if (keyStates[SDL_SCANCODE_L] && keyStates[SDL_SCANCODE_K])
	{
		m_allLightsControl = true;
		m_light1Control = false;
		m_light2Control = false;
	}

	//If light1Control is true, update only the intended light and the directional light
	if (m_light1Control)
	{
		m_light[0]->Update();
		m_light[1]->Update();
	}
	//If light2Control is true, update only the intended light and the directional light
	else if (m_light2Control)
	{
		m_light[0]->Update();
		m_light[2]->Update();
	}
	//If allLightsControl is true, update all the lights together
	else if (m_allLightsControl)
	{
		for (int i = 0; i < total_lights; i++)
		{
			m_light[i]->Update();
		}
	}
}

void GameManager::DrawObjects()
{
	m_backWall->Draw(true, false);
	m_floor->Draw(true, false);
	m_leftWall->Draw(true, false);
	m_rightWall->Draw(true, false);

	m_crateOne->Draw(true, false);
	m_crateTwo->Draw(true, false);

	m_goldBlock->Draw(true, false);
	m_turquoiseBlock->Draw(true, false);
	m_emeraldBlock->Draw(true, false);
	m_obsidianBlock->Draw(true, false);
	m_silverBlock->Draw(true, false);
	m_copperBlock->Draw(true, false);
	m_chromeBlock->Draw(true, false);

	m_noiseCrate->Draw();
	m_circleNoiseCrate->Draw();
	m_colorChangeCrate->Draw();
	m_fireBoxCrate->Draw();

	m_sky->Draw();

	m_quad->Draw();

	m_bedModel->Draw();
	m_bedTableModel->Draw();
	m_tableModel->Draw();
	m_chairModel->Draw();
	m_showerModel->Draw();
	m_rugModel->Draw();
	m_plateModel->Draw();
	m_geckoModel->Draw();
	m_poufModel->Draw();
	m_binModel->Draw();
	m_spaceshipModel->Draw();

	for (int i = 0; i < total_asteroids; i++)
	{
		m_asteroidModel[i]->Draw();
	}

	for (int i = 0; i < total_lights; i++)
	{
		m_light[i]->Draw();
	}
}

void GameManager::GameLoop()
{
	//Simple game loop
	while (!isGameOver)
	{
		//Clear the frame buffer
		TheScreen::Instance()->ClearScreen();

		//Update input Manager
		TheInput::Instance()->Update();

		//Check if X is clicked and if so exit the while loop
		if (TheInput::Instance()->IsXClicked())
		{
			isGameOver = true;
		}

		m_camera->MoveCamera();

		static float count = 0.0f;
		count += 0.1f;
		GLuint m_timeID = glGetUniformLocation(TheShader::Instance()->getProgramID(), "time");
		glUniform1f(m_timeID, count);

		UpdateObjects();
		DrawObjects();

		//Swapping the frame buffer
		TheScreen::Instance()->BufferSwap();
	}
}

void GameManager::DestroyObjects()
{
	m_backWall->Destroy();
	m_floor->Destroy();
	m_leftWall->Destroy();
	m_rightWall->Destroy();

	m_crateOne->Destroy();
	m_crateTwo->Destroy();

	m_goldBlock->Destroy();
	m_turquoiseBlock->Destroy();
	m_emeraldBlock->Destroy();
	m_obsidianBlock->Destroy();
	m_silverBlock->Destroy();
	m_copperBlock->Destroy();
	m_chromeBlock->Destroy();

	m_noiseCrate->Destroy();
	m_circleNoiseCrate->Destroy();
	m_colorChangeCrate->Destroy();
	m_fireBoxCrate->Destroy();

	m_sky->Destroy();

	m_quad->Destroy();

	m_bedModel->Destroy();
	m_bedTableModel->Destroy();
	m_tableModel->Destroy();
	m_chairModel->Destroy();
	m_showerModel->Destroy();
	m_rugModel->Destroy();
	m_plateModel->Destroy();
	m_geckoModel->Destroy();
	m_poufModel->Destroy();
	m_binModel->Destroy();
	m_spaceshipModel->Destroy();

	for (int i = 0; i < total_asteroids; i++)
	{
		m_asteroidModel[i]->Destroy();
	}

	for (int i = 0; i < total_lights; i++)
	{
		m_light[i]->Destroy();
	}
}

void GameManager::Shutdown()
{
	//Shutting down the OpenGL context, the SDL game window and any other SDL subsystems
	TheScreen::Instance()->Shutdown();
}