#pragma once

#include "RendererInputComponent.h"
#include "..\core\AssetManager\AssetManager.h"

class IRenderer {
public:
    virtual bool StartUp() = 0;
    virtual void ShutDown() = 0;
    virtual bool ShouldClose() = 0;
    virtual void SetShouldCloseTrue() = 0;
    virtual void Tick(float DeltaTime) = 0;

    virtual void GetScreenSize(int* width, int* height) = 0;

    virtual bool IsAssetLoaded(uint64_t AssetID) = 0;

protected:
    IRenderer() : RendererInputComponent(this) {};
    CRendererInputComponent RendererInputComponent;

};