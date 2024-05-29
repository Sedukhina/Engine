#pragma once
#include <time.h>
#include "core.h"


class Engine
{
public:
	Engine() {};
	~Engine() {};

	bool StartUp();
	void ShutDown();

	void Mainloop();
	void Tick(float DeltaTime);
private:
	clock_t LastFrame;
};

