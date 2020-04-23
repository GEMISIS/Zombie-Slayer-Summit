#pragma once

#include "Drawable.h"
#include "Shader.h"

class TestShape : public Drawable
{
public:
	TestShape(Shader* shader);
	bool Draw();
	~TestShape();
private:
	GLuint textureID;
	GLint positionAttribute, uvAttribute, colorAttribute;
};