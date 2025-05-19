#pragma once

#include <platform/types.hpp>

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
        void poll_inputs();
        void update_window();
        void render_scene();
        void swap_buffers();
    };
}
