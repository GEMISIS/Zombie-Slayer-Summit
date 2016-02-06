#pragma once

#include "Application.h"
#include "graphics/Shader.h"
#include "graphics/TestShape.h"

class TestState :
	public GameState
{
public:
	TestState(Application* app);
	bool Init();
	bool Update();
	bool Destroy();
	~TestState();
private:
	Shader* shader;
	TestShape* test;
};


