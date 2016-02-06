#pragma once

#include "Drawable.h"
#include "Shader.h"

class TestShape : public Drawable
{
public:
	TestShape(Shader* shader);
	~TestShape();
private:
	GLint positionAttribute, colorAttribute;
};