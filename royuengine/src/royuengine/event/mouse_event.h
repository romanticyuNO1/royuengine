#pragma once

#include "event.h"
#include "rypch.h"

namespace Royu
{
	class ROYU_API MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent(const float x, const float y)
			:m_MouseX(x), m_MouseY(y)
		{
		}

		std::string to_string() const override
		{
			std::stringstream ss;
			ss << "MouseMovedEvent: " << m_MouseX << ", " << m_MouseY;
			return ss.str();
		}

		EVENT_CLASS_TYPE(Mouse_Moved) EVENT_CLASS_CATEGORY(Event_Category_Mouse | Event_Category_Input)

	private:
		float m_MouseX, m_MouseY;
	};

	class ROYU_API MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent(const float x_offset, const float y_offset)
			:m_x_offset(x_offset), m_y_offset(y_offset)
		{
		}

		float get_x_offset() const { return m_x_offset; }
		float get_y_offset() const { return m_y_offset; }

		std::string to_string() const override
		{
			std::stringstream ss;
			ss << "MouseScrolledEvent: " << get_x_offset() << ", " << get_y_offset();
			return ss.str();
		}

		EVENT_CLASS_TYPE(Mouse_Scrolled) EVENT_CLASS_CATEGORY(Event_Category_Mouse | Event_Category_Input)
	private:
		float m_x_offset, m_y_offset;
	};

	class ROYU_API MouseButtonEvent : public Event
	{
	public:
		inline int get_mouse_button() const { return m_button; }

		EVENT_CLASS_CATEGORY(Event_Category_Mouse | Event_Category_Input)
	protected:
		MouseButtonEvent(const int button)
			:m_button(button)
		{
		}

		int m_button;
	};

	class ROYU_API MouseButtonPressedEvent :public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(const int button)
			:MouseButtonEvent(button)
		{
		}

		std::string to_string() const override
		{
			std::stringstream ss;
			ss << "MouseButtonPressedEvent: " << m_button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(Mouse_Button_Pressed)
	};

	class ROYU_API MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:

		MouseButtonReleasedEvent(int button)
			:MouseButtonEvent(button)
		{
		}

		std::string to_string() const override
		{
			std::stringstream ss;
			ss << "MouseButtonPressedEvent: " << m_button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(Mouse_Button_Released)
	};
}