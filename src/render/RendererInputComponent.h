#pragma once

#include "..\core\core.h"

class IRenderer;

class CRendererInputComponent : public CInputComponent
{
public:
	CRendererInputComponent(IRenderer* Renderer);
	
	void CloseWindow();
private:
	IRenderer* CahchedOwner;
};