#include "TestState.h"

int main(int argc, char *argv[])
{
	Application* app = new Application();
	SetState<TestState>(app);
	while(app->Run());
	return 0;
}
