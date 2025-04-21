#include "royuengine.h"

class ATEST : public Royu::Layer
{
public:
	ATEST()
		:Layer("royuengine")
	{

	}

	void on_update() override
	{
		RY_INFO("{0}  On update");
	}

	void on_event(Royu::Event& event) override
	{
		RY_INFO("{0}", event.to_string());
	}
};

class SandBox : public Royu::Application
{
public:
	SandBox()
	{
		push_layer(new ATEST());
		push_overlay(new Royu::ImguiLayer());
	}

	~SandBox()
	{

	}
};

Royu::Application* Royu::create_application()
{
	return new SandBox();
}