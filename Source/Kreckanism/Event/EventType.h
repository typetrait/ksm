#pragma once

namespace Ksm
{
    enum class EventType
    {
        // Window & context events
        WindowResize,

        // Keyboard events
        KeyPress,
        KeyRelease,
        KeyType,

        // Mouse events
        MouseMove,
        MousePress,
        MouseRelease
    };
}
