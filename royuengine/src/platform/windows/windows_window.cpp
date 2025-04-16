#include "rypch.h"
#include "windows_window.h"


namespace Royu
{
	static bool glfw_initialized = false;

	Window* Window::create(const WindowProps& props)
	{
		return (Window*)new WindowsWindow(props);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		init(props);
	}

	WindowsWindow::~WindowsWindow()
	{
		shutdown();
	}

	void WindowsWindow::init(const WindowProps& props)
	{
		m_data.title = props.title;
		m_data.width = props.width;
		m_data.height = props.height;

		RY_CORE_INFO("Creating window {0} ({1}, {2})", props.title, props.width, props.height);

		if (!glfw_initialized)
		{
			int success = glfwInit();

			RY_ASSERT(success, "Success Init");

			glfw_initialized = true;
		}

		m_window = glfwCreateWindow((int)m_data.width, (int)m_data.height, m_data.title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_window);
		glfwSetWindowUserPointer(m_window, &m_data);
		set_v_sync(true);

	}

	void WindowsWindow::shutdown()
	{
		glfwDestroyWindow(m_window);
	}

	void WindowsWindow::on_update()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_window);
	}

	void WindowsWindow::set_v_sync(bool enable)
	{
		if (enable)
		{
			glfwSwapInterval(1);
		}
		else
		{
			glfwSwapInterval(0); //nothing
		}

		m_data.v_sync = enable;
	}

	bool WindowsWindow::is_v_sync() const
	{
		return m_data.v_sync;
	}
}