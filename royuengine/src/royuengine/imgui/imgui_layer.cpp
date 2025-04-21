#include "rypch.h"
#include "imgui_layer.h"
#include "royuengine/application.h"

#include "imgui.h"
#include "royuengine/platform/opengl/imgui_opengl_renderer.h"
#include  "GLFW/glfw3.h"
#include "glad/glad.h"

namespace Royu
{
	ImguiLayer::ImguiLayer()
		:Layer("ImguiLayer")
	{
	}

	ImguiLayer::~ImguiLayer()
	{
	}

	void ImguiLayer::on_attach()
	{
		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		ImGuiIO& io = ImGui::GetIO();
		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

		Application& app = Application::get();
		GLFWwindow* native_window = static_cast<GLFWwindow*>(app.get_window().get_native_window());
		ImGui_ImplOpenGL3_Init("#version 410");
	}

	void ImguiLayer::on_detach()
	{

	}

	void ImguiLayer::on_update()
	{
		ImGuiIO& io = ImGui::GetIO();
		Application& app = Application::get();
		io.DisplaySize = ImVec2(app.get_window().get_width(), app.get_window().get_height());

		float time = (float)glfwGetTime();
		io.DeltaTime = m_time > 0.0f ? (time - m_time) : (1.0f / 60.0f);
		m_time = time;

		//update new frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		static bool show = true;
		ImGui::ShowDemoWindow(&show);

		//push render data to opengl
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}


	void ImguiLayer::on_event(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.dispatch<MouseButtonPressedEvent>(RY_BIND_EVENT_FN(ImguiLayer::on_mouse_button_pressed_event));
		dispatcher.dispatch<MouseButtonReleasedEvent>(RY_BIND_EVENT_FN(ImguiLayer::on_mouse_button_released_event));
		dispatcher.dispatch<MouseMovedEvent>(RY_BIND_EVENT_FN(ImguiLayer::on_mouse_moved_event));
		dispatcher.dispatch<MouseScrolledEvent>(RY_BIND_EVENT_FN(ImguiLayer::on_mouse_scrolled_event));
		dispatcher.dispatch<KeyPressedEvent>(RY_BIND_EVENT_FN(ImguiLayer::on_key_pressed_event));
		dispatcher.dispatch<KeyReleasedEvent>(RY_BIND_EVENT_FN(ImguiLayer::on_key_released_event));
		dispatcher.dispatch<KeyTypedEvent>(RY_BIND_EVENT_FN(ImguiLayer::on_key_typed_event));
		dispatcher.dispatch<WindowResizeEvent>(RY_BIND_EVENT_FN(ImguiLayer::on_window_resize_event));
	}

	bool ImguiLayer::on_mouse_button_pressed_event(MouseButtonPressedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[e.get_mouse_button()] = true;

		return false;
	}

	bool ImguiLayer::on_mouse_button_released_event(MouseButtonReleasedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[e.get_mouse_button()] = false;

		return false;
	}

	bool ImguiLayer::on_mouse_moved_event(MouseMovedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MousePos = ImVec2(e.get_x(), e.get_y());

		return false;
	}

	bool ImguiLayer::on_mouse_scrolled_event(MouseScrolledEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseWheel += e.get_x_offset();
		io.MouseWheelH += e.get_y_offset();

		return false;
	}

	bool ImguiLayer::on_key_pressed_event(KeyPressedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.KeysDown[e.get_key_code()] = true;

		io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
		io.KeyAlt = io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_RIGHT_ALT];
		io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT] || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
		io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER] || io.KeysDown[GLFW_KEY_RIGHT_SUPER];

		return false;
	}

	bool ImguiLayer::on_key_released_event(KeyReleasedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.KeysDown[e.get_key_code()] = false;

		return false;
	}

	bool ImguiLayer::on_key_typed_event(KeyTypedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		int keycode = (e.get_key_code());
		if (keycode > 0 && keycode < 0x10000)
		{
			io.AddInputCharacter((unsigned short)keycode);
		}

		return false;
	}

	bool ImguiLayer::on_window_resize_event(WindowResizeEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize = ImVec2(e.get_width(), e.get_height());
		io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
		glViewport(0, 0, e.get_width(), e.get_height());

		return false;
	}
}