#pragma once

#include "event.h"
#include "rypch.h"


namespace Royu
{
	class ROYU_API KeyEvent : public Event
	{
	public:
		inline int get_key_code() const { return m_key_code; }

		EVENT_CLASS_CATEGORY(Event_Category_Keyboard | Event_Category_Input);
	protected:
		KeyEvent(int key_code)
			:m_key_code(key_code)
		{ }

		int m_key_code;
	};

	class ROYU_API KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(int key_code, int repeat_count)
			:KeyEvent(key_code), m_repeat_count(repeat_count)
		{ }

		inline int get_repeat_count() { return m_repeat_count; }

		std::string to_string() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_key_code << " (repeat = " << m_repeat_count << ")";
			return ss.str();
		}

		EVENT_CLASS_TYPE(Key_Pressed)

	private:
		int m_repeat_count;
	};

	class ROYU_API KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(int key_code)
			:KeyEvent(key_code)
		{ }

		std::string to_string() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << m_key_code << ")";
			return ss.str();
		}

		EVENT_CLASS_TYPE(Key_Released)

			
	};

	class ROYU_API KeyTypedEvent : public KeyEvent
	{
	public:
		KeyTypedEvent(int key_code)
			:KeyEvent(key_code)
		{ }

		std::string to_string() const override
		{
			std::stringstream ss;
			ss << "KeyTypedEvent: " << m_key_code << ")";
			return ss.str();
		}

		EVENT_CLASS_TYPE(Key_Typed)
	};
}