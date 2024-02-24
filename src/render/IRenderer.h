#pragma once

#include "..\core\core.h"

class IRenderer {
public:
    virtual bool StartUp() = 0;
    virtual void ShutDown() = 0;
};