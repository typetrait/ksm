#pragma once

namespace Ksm
{
	enum class EventType
	{
		// Window & context events
		WindowResize,

		// Keyboard events
		KeyPressed,
		KeyReleased,
		KeyTyped
	};
}