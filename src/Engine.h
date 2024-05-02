#pragma once

#include "core.h"

class Engine
{
public:
	Engine() {};
	~Engine() {};

	bool StartUp();
	void ShutDown();

private:
	void Mainloop();
};

