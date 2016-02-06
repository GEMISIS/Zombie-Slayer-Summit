#pragma once

#include "Application.h"
#include "Shader.h"
#include "TestShape.h"

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


