#pragma once

#include "Application.h"
#include "graphics/Shader.h"
#include "graphics/TestShape.h"
#include "graphics/RoomCube.h"
#include "graphics/ObjLoader.h"
#include "Camera.h"

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
	int startX, startY;
	Shader* shader;
	ObjLoader* testL;
	TestShape* test;
	RoomCube* room;
	Camera* camera;
	glm::vec3 rot;
	GLint hasTextureUniform;
};


