#include "royuengine.h"

class SandBox : public Royu::Application
{
public:
	SandBox()
	{

	}

	~SandBox()
	{

	}
};

Royu::Application* Royu::create_application()
{
	return new SandBox();
}