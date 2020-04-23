#include <GL/glew.h>
#include "states/TestState.h"
#include "states/TestState2.h"
#include "Application.h"

TestState::TestState(Application* app) : GameState(app)
{
}

bool TestState::Init()
{
	glClearColor(1, 0, 0, 1);
	this->shader = new Shader("test_shader2.vert", "test_shader2.frag");
	this->shader->Use();
	this->hasTextureUniform = this->shader->getUniformLocation("hasTexture");

	this->test = new TestShape(this->shader);
	this->testL = new ObjLoader(this->shader, "test.obj");
	this->room = new RoomCube(this->shader);

	this->camera = new Camera(this->shader);
	this->camera->SetTranslation(0, 0, -2);
	SDL_GetGlobalMouseState(&this->startX, &this->startY);
	ShowCursor(false);

	return true;
}

#define mouse_speed 0.05f

bool TestState::Update()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUniform1i(this->hasTextureUniform, true);
	this->test->Draw();
	glUniform1i(this->hasTextureUniform, false);
	this->testL->Draw();
	this->room->Draw();
	this->camera->Update();

	const uint8_t* state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_A])
	{
		this->camera->Translate(cos(glm::radians(rot.y)) * 0.1f, 0, sin(glm::radians(rot.y)) * 0.1f);
	}
	if (state[SDL_SCANCODE_D])
	{
		this->camera->Translate(cos(glm::radians(rot.y)) * -0.1f, 0, sin(glm::radians(rot.y)) * -0.1f);
	}
	if (state[SDL_SCANCODE_W])
	{
		this->camera->Translate(sin(glm::radians(rot.y)) * -0.1f, 0, cos(glm::radians(rot.y)) * 0.1f);
	}
	if (state[SDL_SCANCODE_S])
	{
		this->camera->Translate(sin(glm::radians(rot.y)) * 0.1f, 0, cos(glm::radians(rot.y)) * -0.1f);
	}

	if (state[SDL_SCANCODE_LEFT])
	{
		this->rot.y -= 1;
	}
	if (state[SDL_SCANCODE_RIGHT])
	{
		this->rot.y += 1;
	}
	if (state[SDL_SCANCODE_UP])
	{
		this->rot.x -= 1;
	}
	if (state[SDL_SCANCODE_DOWN])
	{
		this->rot.x += 1;
	}

	int xPos, yPos;
	SDL_GetGlobalMouseState(&xPos, &yPos);
	SDL_WarpMouseGlobal(startX, startY);

	rot.y -= mouse_speed * float(startX - xPos);
	rot.x -= mouse_speed * float(startY - yPos);

	this->camera->SetRotation(0, 1, 1, 1);
	this->camera->Rotate(rot.x, 1, 0, 0);
	this->camera->Rotate(rot.y, 0, 1, 0);

	return true;
}

bool TestState::Destroy()
{
	delete this->test;
	delete this->shader;
	return true;
}

TestState::~TestState()
{
}
