//temp
#include<cstdio>

#include "Engine.h"

int main()
{
    Engine engine;
    if (engine.StartUp())
    {
        engine.Mainloop();
        engine.ShutDown();
    }
    getchar();
}