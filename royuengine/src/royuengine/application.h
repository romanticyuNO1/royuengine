#pragma once

#include "core.h"

#include "royuengine/event/event.h"
#include "royuengine/event/application_event.h"
#include "royuengine/layer_stack.h"
#include "window.h"

namespace Royu
{
	class ROYU_API Application
	{
	public:
		Application();
		virtual ~Application();
		void Run();

		void on_event(Event& e);

		void push_layer(Layer* layer);
		void push_overlay(Layer* layer);

		inline Window& get_window() { return *m_window; }
		inline static Application& get() { return *instance; }
	private:
		bool on_window_close(WindowCloseEvent& e);

	private:
		static Application* instance;

		std::unique_ptr<Window> m_window;
		bool m_running = true;
		LayerStack layer_stacks;
	};

	//To be defined in clint
	Application* create_application();
}

