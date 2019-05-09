#pragma once
#include <string>
#include <GL\glew.h>
#include <vector>

class Texture
{
public:
	Texture();

	void Bind(unsigned int unit); // bind upto 32 textures
	void init(const std::string& fileName); //used to initialise the textures
	GLuint loadCubemap(std::vector<std::string> faces);
	GLint getTexHandler() { return textureHandler; }
	~Texture();

protected:
private:

	GLuint textureHandler;

};

