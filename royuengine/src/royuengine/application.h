#pragma once

#include "core.h"
#include "event/event.h"
#include "window.h"

namespace Royu
{
	class ROYU_API Application
	{
	public:
		Application();
		virtual ~Application();
		void Run();

	private:
		std::unique_ptr<Window> m_window;
		bool m_running = true;
	};

	//To be defined in clint
	Application* create_application();
}

