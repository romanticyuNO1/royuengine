#pragma once

#include "royuengine/core.h"
#include "rypch.h"

namespace Royu
{
	// Events in Hazel are currently blocking, meaning when an event occurs it
	// immediately gets dispatched and must be dealt with right then an there.
	// For the future, a better strategy might be to buffer events in an event
	// bus and process them during the "event" part of the update stage.

	enum class EventType
	{
		Nome = 0,
		Window_Close, Window_Resize, Window_Focus, Window_Lost_Focus, Window_Moved,
		App_Tick, App_Update, App_Render,
		Key_Pressed, Key_Released, Key_Typed,
		Mouse_Button_Pressed, Mouse_Button_Released, Mouse_Moved, Mouse_Scrolled
	};

	enum EventCategory
	{
		None = 0,
		Event_Category_Application = BIT(0),
		Event_Category_Input = BIT(1),
		Event_Category_Keyboard = BIT(2),
		Event_Category_Mouse = BIT(3),
		Event_Category_Mouse_Buttom = BIT(4)
	};


#define EVENT_CLASS_TYPE(type) static EventType get_static_type() {return EventType::type;}\
																	virtual EventType get_event_type() const override {return get_static_type();}\
																	virtual const char* get_name() const override {return #type;}

#define EVENT_CLASS_CATEGORY(category) virtual int get_category_flags() const override {return EventCategory::category;}

	class ROYU_API Event
	{
		friend class EventDispatcher;
	public:
		virtual EventType get_event_type() const = 0;
		virtual const char* get_name() const = 0;
		virtual int get_category_flags() const = 0;
		virtual std::string to_string() const { return get_name(); }

		inline bool is_category(EventCategory category) const
		{
			return get_category_flags() & category;
		}

	protected:
		bool m_handled = false;
	};

	class EventDispatcher
	{
		template<typename T>
		using event_fn = std::function<bool(T&)>; //return bool 

	public:
		EventDispatcher(Event& event)
			:m_event(event)
		{
		}

		template<typename T>
		bool Dispatch(event_fn<T> func)
		{
			if (m_event.get_event_type() == T::get_static_type())
			{
				//&取地址 *解引用
				//Event* -> Event派生类* -> *解引用 ->obj
				m_event.m_handled = func(*(T*)&m_event);
				return true;
			}

			return false;
		}
	private:
		Event& m_event;
	};

	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.to_string();
	}
}