#pragma once

#include <Windows.h>
#include <GL/GL.h>

#include "Window.h"

class application_exception : public std::runtime_error
{
public:
	application_exception(const std::string& error) : std::runtime_error(error){};
};

class GameStateBase
{
public:
	virtual bool Init() = 0;
	virtual bool Update() = 0;
	virtual bool Destroy() = 0;
};

class Application
{
public:
	Application();

	bool Run();
	void Stop();

	void SetState(GameStateBase* state);

	~Application();
private:
	bool active;
	Window* window;
	GameStateBase* state = nullptr;
};

class GameState : public GameStateBase
{
public:
	GameState(Application* app)
	{
		this->app = app;
	}
protected:
	Application* app;
};

template <class StateClass>
void SetState(Application* app)
{
	app->SetState(new StateClass(app));
}

