#pragma once

#include "event.h"

namespace Royu
{
	class ROYU_API WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(const unsigned int w, const unsigned int h)
			:m_width(w), m_height(h)
		{
		}

		unsigned int get_width() const { return m_width; }
		unsigned int get_height() const { return m_height; }

		std::string to_string() const override
		{
			std::stringstream ss;
			ss << "WindowResizeEvent: " << m_width << ", " << m_height;
			return ss.str();
		}

		EVENT_CLASS_TYPE(Window_Resize)EVENT_CLASS_CATEGORY(Event_Category_Application)
	private:
		unsigned int m_width, m_height;
	};

	class ROYU_API WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent() = default;

		EVENT_CLASS_TYPE(Window_Close)EVENT_CLASS_CATEGORY(Event_Category_Application)
	};

	class ROYU_API AppTickEvent : public Event
	{
	public:
		AppTickEvent() = default;

		EVENT_CLASS_TYPE(App_Tick)EVENT_CLASS_CATEGORY(Event_Category_Application)
	};

	class ROYU_API AppUpdateEvent : public Event
	{
	public:
		AppUpdateEvent() = default;

		EVENT_CLASS_TYPE(App_Update)EVENT_CLASS_CATEGORY(Event_Category_Application)
	};

	class ROYU_API AppRenderEvent : public Event
	{
	public:
		AppRenderEvent() = default;

		EVENT_CLASS_TYPE(App_Render)EVENT_CLASS_CATEGORY(Event_Category_Application)
	};
}
