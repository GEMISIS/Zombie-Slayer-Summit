#pragma once

#include <vector>
#include <iterator>
#include <SDL2/SDL.h>

class Drawable
{
public:
	Drawable();
	bool Draw(GLuint textureID = 0);
	~Drawable();
protected:
	void loadVertices(float data[], size_t size);
	void loadVertices(std::vector<float> data);

	void loadElements(GLuint data[], size_t size);
	void loadElements(std::vector<GLuint> data);

	void loadTexture(GLuint& textureID, std::string fileName);

	void bindVAO();
	void unbindVAO();
private:
	GLuint vbo, vao, ebo, totalElementsCount;
};