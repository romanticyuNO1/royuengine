#pragma once

#include "rypch.h"

#include "royuengine/window.h"
#include <glfw/glfw3.h>

namespace Royu
{
	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		void on_update() override;

		unsigned int get_width() const override { return m_data.width; }
		unsigned int get_height() const override { return m_data.height; }

		void set_event_callback(const event_callback_fn& callback) override { m_data.event_callback = callback; }
		void set_v_sync(bool enabled) override;
		bool is_v_sync() const override;

		void* get_native_window() const override { return gl_window; }

	private:
		virtual void init(const WindowProps& props);
		virtual void shutdown();
	private:
		GLFWwindow* gl_window;
		//Scope<GraphicsContext> m_Context;

		struct WindowData
		{
			std::string title;
			unsigned int width, height;
			bool v_sync;

			//�󶨵�GLFWWindow�ϵĻص�����
			event_callback_fn event_callback;
		};

		WindowData m_data;
	};
}
