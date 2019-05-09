#include "MainGame.h"
#include "Camera.h"
#include <iostream>
#include "stb_image.h"
#include <string>



Vertex vertices[] = { Vertex(glm::vec3(-0.5, -0.5, 0), glm::vec2(0.0, 0.0), glm::vec3(1.0,0.0,0.0)),
					Vertex(glm::vec3(0, 0.5, 0), glm::vec2(0.5, 1.0), glm::vec3(1.0,0.0,0.0)),
					Vertex(glm::vec3(0.5, -0.5, 0), glm::vec2(1.0, 0.0), glm::vec3(1.0,0.0,0.0)) };

unsigned int indices[] = { 0, 1, 2 };

MainGame::MainGame()
{
	_gameState = GameState::PLAY;
	Display* _gameDisplay = new Display(); //new display
	Mesh* mesh1();
	Mesh* mesh2();
	Mesh* mesh3();
	Texture* texture1();
	Texture* texture2();
	Texture* texture3();
	Texture* texture4();
	Shader* shader();
}

MainGame::~MainGame()
{
}

void MainGame::run() //this method initialises the systems and starts the game loop
{
	initialiseSystems();
	gameLoop();
}

void MainGame::initialiseSystems()
{
	_gameDisplay.initDisplay();
	mesh1.loadModel("..\\res\\Models\\sphere.obj"); //loads the sphere mesh for the reflection shader
	mesh2.loadModel("..\\res\\Models\\monkey3.obj"); //loads the monkey head mesh used for the custom graphical technique
	mesh3.loadModel("..\\res\\Models\\rat.obj"); // loads the final model used for the exploding shader

	texture1.init("..\\res\\Textures\\water.jpg"); //sets the texture for mesh 1
	texture2.init("..\\res\\Textures\\bricks.jpg"); //sets the texture for mesh 2
	texture3.init("..\\res\\Textures\\bricks.jpg"); //sets the texture for mesh 3
	shaderSkybox.initShader("..\\res\\Shaders\\skybox.vert", "..\\res\\Shaders\\skybox.frag");
	shaderReflection.initShader("..\\res\\Shaders\\shaderReflection.vert", "..\\res\\Shaders\\shaderReflection.frag");
	shaderExp.initShaderGeo("..\\res\\Shaders\\shaderGeoText.vert", "..\\res\\Shaders\\shaderGeoText.frag", "..\\res\\Shaders\\shaderGeoText.geom");
	shaderCustom.initShader("..\\res\\Shaders\\customShader.vert", "..\\res\\Shaders\\customShader.frag");


	//currentMusic = backGroundMusic1; //sets the current music to backgroundMusic1

	//audioDevice.playSound(backGroundMusic1); //plays backgroundMusic1

	myCamera.initCamera(glm::vec3(0, 0, -15), 70.0f, (float)_gameDisplay.getWidth() / _gameDisplay.getHeight(), 0.01f, 1000.0f);
	counter = 1.0f;

	colorCounter = 0.1f;
	redChange = 0.5;
	greenChange = 0.5;
	blueChange = 0.5;

	gammaChange = 1.0;

	refraction = 1.0;
#pragma region
	vector<std::string> faces
	{
		"..\\res\\skybox\\right.jpg",
		"..\\res\\skybox\\left.jpg",
		"..\\res\\skybox\\top.jpg",
		"..\\res\\skybox\\bottom.jpg",
		"..\\res\\skybox\\front.jpg",
		"..\\res\\skybox\\back.jpg"
	};
	cubemapTexture = skybox.loadCubemap(faces); //Load the cubemap using "faces" into cubemapTextures


												//The position of the vertices of the skybox, also changes its size
	float skyboxVertices[] = {
		// positions          
		-1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		-1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f
	};

	

	//use openGL functionality to generate & bind data into buffers
	glGenVertexArrays(1, &skyboxVAO);
	glGenBuffers(1, &skyboxVBO);
	glBindVertexArray(skyboxVAO);
	glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

#pragma endregion skybox

	updateModelTransform();
}

void MainGame::gameLoop()
{
	while (_gameState != GameState::EXIT) //while the game is running we run the 3 methods below
	{
		processInput();
		drawGame();
	}
}

void MainGame::processInput()
{
	SDL_Event event;

	while (SDL_PollEvent(&event)) //get and process events
	{
		switch (event.type)
		{
		case SDL_QUIT:
			_gameState = GameState::EXIT;
			break;

		case SDL_KEYDOWN:

			switch (event.key.keysym.sym)
			{
			
				// controls for model and camera movement, camera uses same coordinats variables as the model to allow for the camera to follow the model
			case SDLK_d:
				myCamera.MoveRight(1.0f);
				break;
			case SDLK_w:
				myCamera.MoveForward(1.0f);
				break;
			case SDLK_a:
				myCamera.MoveLeft(1.0f);
				break;
			case SDLK_s:
				myCamera.MoveBackward(1.0f);
				break;
			case SDLK_SPACE:
				myCamera.MoveUp(1.0f);
				break;
			case SDLK_LSHIFT:
				myCamera.MoveDown(1.0f);
				break;
			case SDLK_q:
				myCamera.Pitch(0.1f);
				break;
			case SDLK_e:
				myCamera.RotateY(0.11f);
				break;

			case SDLK_z:
				gammaChange += 0.5; //increase contrast
				break;
			case SDLK_x:
				gammaChange -= 0.5; //decrease contrast
				break;

			case SDLK_c:
				colorCounter += 0.5; //increase brightness
				break;
			case SDLK_v:
				colorCounter -= 0.5; //decrease brightness
				break;

			case SDLK_b:
				refraction += 0.01; //increase refraction amount
				break;
			case SDLK_n:
				refraction -= 0.01; //decrease refraction amount
				break;



					//controls used to change monkey head colour
				case SDLK_1:
					// green colour
					redChange = 0.5;
					greenChange = 0.1;
					blueChange = 0.5;
					break;

				case SDLK_2:
					// blue colour
					redChange = 0.5;
					greenChange = 0.5;
					blueChange = 0.1;
					break;

				case SDLK_3:
					// red colour
					redChange = 0.1;
					greenChange = 0.5;
					blueChange = 0.5;
					break;

				case SDLK_4:
					// cyan colour
					redChange = 1.0;
					greenChange = 0.5;
					blueChange = 0.5;
					break;
				case SDLK_5:
					// yellow colour
					redChange = 0.5;
					greenChange = 0.5;
					blueChange = 1.0;
					break;
				case SDLK_6:
					// purple colour
					redChange = 0.5;
					greenChange = 1.0;
					blueChange = 0.5;
					break;
				case SDLK_7:
					// no colour
					redChange = 0.5;
					greenChange = 0.5;
					blueChange = 0.5;
					break;
		

			}
		}
	}

}

bool MainGame::checkCollision(glm::vec3& m1Pos, float m1Rad, glm::vec3 m2Pos, float m2Rad)
{
	float distanceSq = ((m2Pos.x - m1Pos.x)*(m2Pos.x - m1Pos.x) + (m2Pos.y - m1Pos.y) * (m2Pos.y - m1Pos.y) + (m2Pos.z - m1Pos.z)*(m2Pos.z - m1Pos.z)); //equation used to work out the distance between the two objects

	if (distanceSq < ((m1Rad + m2Rad)*(m1Rad + m2Rad))) //if statement used to check if a collision has occurred
		return true;

	return false;



}

void MainGame::Skybox()
{
	glDepthFunc(GL_LEQUAL);  // change depth function so depth test passes when values are equal to depth buffer's content
	shaderSkybox.Bind();
	glm::mat4 view = glm::mat4(glm::mat3(myCamera.GetView())); // remove translation from the view matrix
	shaderSkybox.setMat4("view", view);
	shaderSkybox.setMat4("projection", myCamera.GetProjection());
	// skybox cube
	glBindVertexArray(skyboxVAO);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
	glDepthFunc(GL_LESS); // set depth function back to default
}

void MainGame::setExplosionValues()
{
	shaderExp.setFloat("time", 0.1f + (counter * 2));

	//the code below has been commented out as it is not being used in order to allow for the model to be rendered with a custom texture
	//shaderExp.setFloat("randColourX", rand() % 1);
	//shaderExp.setFloat("randColourY", rand() % 5);
	//shaderExp.setFloat("randColourZ", rand() % 10);

}

void MainGame::setReflectionValues()
{
	shaderReflection.setMat4("model", transform1.GetModel());
	shaderReflection.setVec3("cameraPos", myCamera.GetPos());
	shaderReflection.setInt("skybox", 0);
}



void MainGame::setCustomValues()
{
	shaderCustom.setMat4("model", transform2.GetModel()); //sets our uniform variable model
	shaderCustom.setMat4("u_vm", myCamera.GetView()); //sets the uniform variable u_vm
	shaderCustom.setMat4("u_pm", myCamera.GetProjection()); //sets the uniform variable u_pm

	shaderCustom.setVec3("cameraPos", myCamera.GetPos()); //sets the 3D vector for camera position based on the cameras current position in the scene

	shaderCustom.setInt("skybox", 0); //attains the skybox

	shaderCustom.setFloat("c_counter", colorCounter); //sets the float used for our c_counter variable

	//these 3 variables are used for our rgb colour values
	shaderCustom.setFloat("r_change", redChange);
	shaderCustom.setFloat("g_change", greenChange);
	shaderCustom.setFloat("b_change", blueChange);

	shaderCustom.setFloat("gammaChange", gammaChange); //sets the float used for our gammaChange variable

	shaderCustom.setFloat("refraction", refraction); //sets the float used for our refraction variable
}








void MainGame::drawGame()
{
	_gameDisplay.clearDisplay(0.0f, 0.0f, 0.0f, 1.0f);

	counter = counter + 0.05f;

	if (colorCounter > 100.0f)
	{
		colorCounter = 0.0f;
	}

	if (refraction < 1.0)
	{
		refraction = 1.0;
	}
	if (refraction > 1.1)
	{
		refraction = 1.1;
	}

	Skybox();

	// code for object 1 - the cube
	shaderReflection.Bind();
	setReflectionValues();
	shaderReflection.Update(transform1, myCamera);
	texture1.Bind(0);
	mesh1.draw();


	//code for object 2 - the monkey
	shaderCustom.Bind();
	setCustomValues();
	shaderCustom.Update(transform2, myCamera);
	texture2.Bind(0);
	mesh2.draw();

	//code for object 3 - the sphere
	shaderExp.Bind();
	setExplosionValues();
	shaderExp.Update(transform3, myCamera);
	texture3.Bind(0);
	mesh3.draw();



	glEnableClientState(GL_COLOR_ARRAY);
	glEnd();

	_gameDisplay.swapBuffer();

}

void MainGame::updateModelTransform()
{
	transform1.SetPos(glm::vec3(-10.0f, 0.0f, 15.0f));
	transform1.SetRot(glm::vec3(0.0f, 0.0f , 0.0f));
	transform1.SetScale(glm::vec3(5.0f, 5.0f, 5.0f));

	transform2.SetPos(glm::vec3(50.0f, 0.0f, 15.0f));
	transform2.SetRot(glm::vec3(0.0f, 180.0f, 0.0f));
	transform2.SetScale(glm::vec3(5.0f, 5.0f, 5.0f));

	transform3.SetPos(glm::vec3(0.0f, 0.0f, 15.0f));
	transform3.SetRot(glm::vec3(0.0f, 0.0f, 0.0f));
	transform3.SetScale(glm::vec3(5.0f, 5.0f, 5.0f));

	mesh1.setSphereData(*transform1.GetPos(), 10.0f);
	mesh2.setSphereData(*transform2.GetPos(), 1.0f);
}