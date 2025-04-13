#pragma once


#ifdef RY_PLAYFROM_WINDOWS

extern Royu::Application* Royu::create_application();

void main(int argc, char** argv)
{
	Royu::Log::init();
	RY_CORE_WARN("Initialized Log");

	auto app = Royu::create_application();
	app->Run();
	delete(app);
}
#endif