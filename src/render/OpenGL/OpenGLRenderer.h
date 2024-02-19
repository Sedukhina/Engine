#include "../BaseRenderer.h"

class OpenGLRenderer : public IRenderer
{
public:
	virtual bool StartUp() override;
	virtual void ShutDown() override;
private:

};