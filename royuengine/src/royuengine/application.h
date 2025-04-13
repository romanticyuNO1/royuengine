#pragma once

#include "core.h"

namespace Royu
{
	class ROYUYU_API Application
	{
	public:
		Application();
		virtual ~Application();
		void Run();
	};

	//To be defined in clint
	Application* create_application();
}

