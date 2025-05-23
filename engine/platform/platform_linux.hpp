#pragma once

#include <platform/platform_detection.hpp>
#include <platform/window.hpp>
#include <core/log.hpp>

#ifdef MNEMOS_PLATFORM_LINUX

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <GL/gl.h>
#include <GL/glx.h>

namespace mnm
{
    class linux_window : public window
    {
    public:
        linux_window(logger& logger);
        ~linux_window();

        bool init(const window_config& config);
        void shutdown();

        void update();
        void swap_buffers();
        bool close_requested();
    
    private:
        Display* m_display;
        Screen* m_screen;
        i8 m_screen_id;
        Window m_window;
        XEvent m_event;
        
        XSetWindowAttributes m_window_attributes;
        XVisualInfo* m_visual;
        GLXContext m_context{0};

        // Utils
        logger& m_logger;

        // XLib atoms
        Atom wm_delete_window;
    };
}

#endif
