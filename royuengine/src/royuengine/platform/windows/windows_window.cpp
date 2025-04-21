#include "rypch.h"
#include "windows_window.h"

#include "royuengine/event/application_event.h"
#include "royuengine/event/mouse_event.h"
#include "royuengine/event/key_event.h"

#include <glad/glad.h>


namespace Royu
{
	//类的全局唯一性成员变量
	static bool glfw_initialized = false;

	static void glfw_error_callback(int error, const char* description)
	{
		RY_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
	}

	Window* Window::create(const WindowProps& props)
	{
		return new WindowsWindow(props);
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
			RY_CORE_ASSERT(success, "Could not initialize GLFW");

			glfwSetErrorCallback(glfw_error_callback);

			glfw_initialized = true;
		}

		gl_window = glfwCreateWindow((int)m_data.width, (int)m_data.height, m_data.title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(gl_window);

		//获取opengl所需要的函数地址
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		RY_CORE_ASSERT(status, "Failed to initialize glad");

		glfwSetWindowUserPointer(gl_window, &m_data);
		set_v_sync(true);

		//绑定各类lamda事件到到m_window
		glfwSetWindowSizeCallback(gl_window, [](GLFWwindow* window, int width, int height)
			{
				WindowData& data = *(WindowData*)(glfwGetWindowUserPointer(window));
				data.width = width;
				data.height = height;

				WindowResizeEvent event(width, height);
				data.event_callback(event);
			});

		glfwSetWindowCloseCallback(gl_window, [](GLFWwindow* window)
			{
				WindowData& data = *(WindowData*)(glfwGetWindowUserPointer(window));

				WindowCloseEvent event;
				data.event_callback(event);
			});

		glfwSetKeyCallback(gl_window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				WindowData& data = *(WindowData*)(glfwGetWindowUserPointer(window));

				switch (action)
				{
				case GLFW_PRESS:
				{
					KeyPressedEvent event(key, 0);
					data.event_callback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent event(key);
					data.event_callback(event);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressedEvent event(key, 1);
					data.event_callback(event);
					break;
				}
				default:
					break;
				}
			});

		glfwSetMouseButtonCallback(gl_window, [](GLFWwindow* window, int button, int action, int mods)
			{
				WindowData& data = *(WindowData*)(glfwGetWindowUserPointer(window));

				switch (action)
				{
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent event(button);
					data.event_callback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent event(button);
					data.event_callback(event);
					break;
				}
				default:
					break;
				}
			});

		glfwSetScrollCallback(gl_window, [](GLFWwindow* window, double xOffset, double yOffset)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				MouseScrolledEvent event((float)xOffset, (float)yOffset);
				data.event_callback(event);
			});

		glfwSetCursorPosCallback(gl_window, [](GLFWwindow* window, double xpos, double ypos)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				MouseMovedEvent event((float)xpos, (float)ypos);
				data.event_callback(event);
			});

		glfwSetCharCallback(gl_window, [](GLFWwindow* window, unsigned int character)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				KeyTypedEvent event(character);
				data.event_callback(event);
			});
	}

	void WindowsWindow::shutdown()
	{
		glfwDestroyWindow(gl_window);
	}

	void WindowsWindow::on_update()
	{
		glfwPollEvents();
		glfwSwapBuffers(gl_window);
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