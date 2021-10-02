#pragma once

#include "Kreckanism/Event/Event.h"

namespace Ksm
{
	class EventDispatcher
	{
	public:
		EventDispatcher(Event& event) : event(event)
		{
		}

		template<typename T, typename F>
		void Dispatch(const F& f)
		{
			if (event.GetType() == T::GetStaticType())
			{
				f(static_cast<T&>(event));
			}
		}

	private:
		Event& event;
	};
}