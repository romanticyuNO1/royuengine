#pragma once

#include "royuengine/layer.h"
#include "royuengine/event/mouse_event.h"
#include "royuengine/event/key_event.h"
#include "royuengine/event/application_event.h"

namespace Royu
{
	class ROYU_API ImguiLayer : public Layer
	{
	public:
		ImguiLayer();
		~ImguiLayer();

		void on_attach();
		void on_detach();
		void on_update();
		void on_event(Event& event);

	private:
		bool on_mouse_button_pressed_event(MouseButtonPressedEvent& e);
		bool on_mouse_button_released_event(MouseButtonReleasedEvent& e);
		bool on_mouse_moved_event(MouseMovedEvent& e);
		bool on_mouse_scrolled_event(MouseScrolledEvent& e);
		bool on_key_pressed_event(KeyPressedEvent& e);
		bool on_key_released_event(KeyReleasedEvent& e);
		bool on_key_typed_event(KeyTypedEvent& e);
		bool on_window_resize_event(WindowResizeEvent& e);
	private:
		float m_time = 0.0f;
	};
}
