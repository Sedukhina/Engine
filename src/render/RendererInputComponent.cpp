#include "IRenderer.h"

CRendererInputComponent::CRendererInputComponent(IRenderer* Renderer)
{
	CahchedOwner = Renderer;
	GetInputController().GetCurrentInputScheme()->BindInputAction(std::bind(&CRendererInputComponent::CloseWindow, this), InputKey::ESC, InputAction::PRESSED);
}

void CRendererInputComponent::CloseWindow()
{
	CahchedOwner->SetShouldCloseTrue();
}
