#pragma once

#include <string>

#include "Kreckanism/Event/EventType.h"

namespace Ksm
{
	class Event
	{
	public:
		virtual EventType GetType() const = 0;
		virtual std::string GetName() const { return "Event!"; }

	private:
		
	};
}