#pragma once

#include "royuengine/core.h"
#include "royuengine/event/event.h"

namespace Royu
{
	class ROYU_API Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer() = default;

		virtual void on_attach() {}
		virtual void on_detach() {}
		virtual void on_update() {}
		virtual void on_event(Event& event) {}

		inline const std::string& get_name() { return debug_name; }

	protected:
		std::string debug_name;
	};
}
