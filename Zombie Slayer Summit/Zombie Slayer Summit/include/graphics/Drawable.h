#pragma once

#include <vector>
#include <iterator>

class Drawable
{
public:
	Drawable();
	bool Draw();
	~Drawable();
protected:
	void loadVertices(float data[], size_t size);
	void loadVertices(std::vector<float> data);

	void loadElements(GLuint data[], size_t size);
	void loadElements(std::vector<GLuint> data);

	void bindVAO();
	void unbindVAO();
private:
	GLuint vbo, vao, ebo;
	std::vector<GLuint> elements;
	std::vector<float> vertices;
};