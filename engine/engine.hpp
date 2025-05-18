#pragma once

namespace mnm
{
    class context
    {
    public:
        void init();
        void main_loop();
        void shutdown();

    private:
        void poll_inputs();
        void update_window();
        void render_scene();
        void swap_buffers();
    };
}
