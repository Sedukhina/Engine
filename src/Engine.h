#pragma once

#include "core.h"

class Engine
{
public:
	Engine() {};
	~Engine() {};

	bool StartUp();
	void ShutDown();

	void Mainloop();
	void Tick();
private:
	
};

