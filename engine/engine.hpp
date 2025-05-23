#pragma once

#include <platform/types.hpp>
#include <platform/window.hpp>
#include <renderer/renderer.hpp>
#include <core/timer.hpp>

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

        f64 target_framerate{};
        bool vsync{};
    };

    class context
    {
    public:
        context();
        ~context();

        void init(const context_config& config);
        void main_loop();
        void shutdown();

    private:
        void init_logging();
        void init_window(u16 width, u16 height, const char* title, bool vsync);
        void init_renderer(f64 target_framerate);

        void poll_inputs();
        void update_window();
        void render_scene();
        void swap_buffers();
        void update_timer();

        bool m_running{};

        // Subsystems
        window* m_window{};
        renderer m_renderer;
        timer m_timer;
    };
}
