#pragma once

#include <platform/platform_detection.hpp>
#include <platform/window.hpp>

#ifdef MNEMOS_PLATFORM_LINUX

#include <X11/Xlib.h>

namespace mnm
{
    class linux_window : public window
    {
    public:
        void init(const window_config& config);
        void shutdown();

        void update();
        bool close_requested();
    
    private:
        Display* m_display;
        Window m_window;
        XEvent m_event;

        // Events
        Atom wm_delete_window;
    };
}

#endif
