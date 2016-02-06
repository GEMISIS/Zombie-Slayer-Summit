#include <GL/glew.h>
#include "Application.h"
#include "TestState.h"

#include <SDL2/SDL.h>

Application::Application()
{
	try
	{
		if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		{
			throw application_exception(SDL_GetError());
		}
		else
		{
			this->window = new Window("Demo Project", 640, 480);
			if (glewInit() != GLEW_OK)
			{
				std::cout << "Error initializing GLEW!" << std::endl;
			}
		}
	}
	catch (application_exception& exception)
	{
		std::cout << "Application Error: ";
#ifdef _DEBUG
		std::cout << "Line 20 in Application.cpp : ";
#endif
		std::cout << exception.what() << std::endl;
	}
	catch (window_exception& exception)
	{
		std::cout << "Window Error: ";
#ifdef _DEBUG
		std::cout << "Line 5 in Window.cpp : ";
#endif
		std::cout << exception.what() << std::endl;
	}
	catch (gl_context_exception& exception)
	{
		std::cout << "GL Context Error: ";
#ifdef _DEBUG
		std::cout << "in Window.cpp : ";
#endif
		std::cout << exception.what() << std::endl;
	}
}

bool Application::Run()
{
	if (this->active)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				this->Stop();
				break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					this->Stop();
					break;
				}
				break;
			}
		}

		if (this->state != nullptr && this->state->Update())
		{
			this->window->Update();
		}
	}
	return this->active;
}

void Application::Stop()
{
	this->active = false;
}

void Application::SetState(GameStateBase* state)
{
	if (this->state != nullptr)
	{
		this->state->Destroy();
	}
	this->state = state;
	this->state->Init();
}

Application::~Application()
{
	if (this->state != nullptr)
	{
		this->state->Destroy();
		delete this->state;
	}
	SDL_Quit();
}