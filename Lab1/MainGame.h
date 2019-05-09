#pragma once
#include <SDL\SDL.h>
#include <GL/glew.h>
#include "Display.h" 
#include "Shader.h"
#include "Mesh.h"
#include "Audio.h"
#include "Texture.h"
#include "transform.h"

enum class GameState { PLAY, EXIT };

class MainGame
{
public:
	MainGame();
	~MainGame();

	void run(); //method used to run game
	

private:

	void initialiseSystems(); //method used to initialise game systems
	void processInput(); //method used to process key inputs
	void gameLoop(); //method used for game loop
	void drawGame(); //method used to draw game
	bool checkCollision(glm::vec3&, float, glm::vec3, float); //boolean method used for checking if collision has occurred
	void updateModelTransform(); //method used to allow ability to update model transform outside drawGame()
	void setExplosionValues();
	void setReflectionValues();
	void setCustomValues();

	Display _gameDisplay; 
	GameState _gameState;
	Mesh mesh1;
	Mesh mesh2;
	Mesh mesh3;
	Camera myCamera;
	Texture texture1;
	Texture texture2;
	Texture texture3;
	Transform transform1;
	Transform transform2;
	Transform transform3;
	Shader shader;
	Shader shaderExp;
	Shader shaderReflection;
	Shader shaderCustom;
	Audio audioDevice;


	//unsigned int used for audio within game
	unsigned int backGroundMusic1;
	unsigned int currentMusic;

	glm::mat4  modelView;

	float currentShader;
	float counter;
	float colorCounter;
	float redChange;
	float greenChange;
	float blueChange;
	float gammaChange;
	float refraction;

	//Skybox code
	void Skybox();

	GLuint skyboxVAO, skyboxVBO, cubemapTexture;
	vector<std::string> faces;
	Texture skybox;
	Shader shaderSkybox;

};

