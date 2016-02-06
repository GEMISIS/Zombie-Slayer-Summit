#include "TestState.h"
#include "TestState2.h"
#include "Application.h"

TestState::TestState(Application* app) : GameState(app)
{
}

bool TestState::Init()
{
	glClearColor(1, 0, 0, 1);
	this->shader = new Shader("test_shader.vert", "test_shader.frag");
	this->shader->Use();
	this->test = new TestShape(this->shader);
	return true;
}

bool TestState::Update()
{
	glClear(GL_COLOR_BUFFER_BIT);
	this->test->Draw();
	GLenum error = glGetError();

	const uint8_t* state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_RIGHT])
	{
		SetState<TestState2>(this->app);
	}

	return true;
}

bool TestState::Destroy()
{
	return true;
}

TestState::~TestState()
{
}
