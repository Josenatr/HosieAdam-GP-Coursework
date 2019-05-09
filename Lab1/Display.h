#pragma once
#include <SDL/SDL.h>
#include <GL\glew.h>
#include <iostream>
#include <string>
using namespace std;


class Display
{
public:
	Display(); //constructor for display
	~Display(); //destructor for display
	void initDisplay(); //method used to initialise the display
	void swapBuffer(); //method used to swap buffer
	void clearDisplay(float r, float g, float b, float a); //method used to set display a certain rgba value

	float getWidth(); //method used for getting the screen width float
	float getHeight(); //method used for getting the screen height float

private:

	void returnError(std::string errorString); //private method used to return an error message if an error occurs during setting the display
	
	SDL_GLContext glContext; //global variable to hold the context
	SDL_Window* sdlWindow; //holds pointer to out window
	float screenWidth; //float used to store screen width
	float screenHeight; //float used to store screen height
};

