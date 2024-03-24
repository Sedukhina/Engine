#pragma once

#include "RendererInputComponent.h"

class IRenderer {
public:
    virtual bool StartUp() = 0;
    virtual void ShutDown() = 0;
    virtual bool ShouldClose() = 0;
    virtual void SetShouldCloseTrue() = 0;
    virtual void Tick() = 0;

protected:
    IRenderer() : RendererInputComponent(this) {};
    CRendererInputComponent RendererInputComponent;
};