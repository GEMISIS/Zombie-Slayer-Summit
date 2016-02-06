#include <Windows.h>
#include <GL/glew.h>

#include "Drawable.h"

Drawable::Drawable()
{
	glGenVertexArrays(1, &this->vao);
}

void Drawable::loadVertices(float data[], size_t size)
{
	this->vertices.insert(this->vertices.end(), data, data + size);

	glGenBuffers(1, &this->vbo);
	glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);
}

void Drawable::loadVertices(std::vector<float> data)
{
	this->vertices.insert(this->vertices.end(), data.begin(), data.end());

	glGenBuffers(1, &this->vbo);
	glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(this->vertices), &this->vertices, GL_STATIC_DRAW);
}

void Drawable::loadElements(GLuint data[], size_t size)
{
	this->elements.insert(this->elements.end(), data, data + size);

	glGenBuffers(1, &this->ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);
}
void Drawable::loadElements(std::vector<GLuint> data)
{
	this->elements.insert(this->elements.end(), data.begin(), data.end());

	glGenBuffers(1, &this->ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(this->elements), &this->elements, GL_STATIC_DRAW);
}

void Drawable::bindVAO()
{
	glBindVertexArray(this->vao);
}

void Drawable::unbindVAO()
{
	glBindVertexArray(0);
}

bool Drawable::Draw()
{
	if (!this->vao || !this->vbo || !this->ebo)
	{
		return false;
	}
	this->bindVAO();
	glDrawElements(GL_TRIANGLES, this->elements.size(), GL_UNSIGNED_INT, 0);
	this->unbindVAO();
	return true;
}

Drawable::~Drawable()
{
	if (this->ebo)
	{
		glDeleteBuffers(1, &this->ebo);
	}
	if (this->vbo)
	{
		glDeleteBuffers(1, &this->vbo);
	}
	glDeleteVertexArrays(1, &this->vao);
}


