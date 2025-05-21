#pragma once

#include <platform/types.hpp>
#include <platform/window.hpp>

#include <platform/platform_detection.hpp>

#if defined(MNEMOS_PLATFORM_LINUX)
    #include <platform/platform_linux.hpp>
#elif defined(MNEMOS_PLATFORM_WINDOWS)
    #include <platform/platform_windows.hpp>
#endif

namespace mnm
{
    struct context_config
    {
        u16 width{};
        u16 height{};
        const char* window_title{};
        bool fullscreen{};
    };

    class context
    {
    public:
        void init(const context_config& config);
        void main_loop();
        void shutdown();

    private:
        void init_logging();
        void init_window(u16 width, u16 height, const char* title);

        void poll_inputs();
        void update_window();
        void render_scene();
        void swap_buffers();

        window* m_window{};
        bool m_running{};
    };
}
