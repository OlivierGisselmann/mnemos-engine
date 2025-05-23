#include <engine.hpp>

#include <iostream>

int main()
{
    // TODO: Fill config struct from JSON file
    constexpr mnm::context_config conf
    {
        .width = 1280,
        .height = 720,
        .window_title = "Game - Mnemos Engine",
        .fullscreen = false,
        .target_framerate = 120.0,
        .vsync = true
    };

    mnm::context ctx{};
    ctx.init(conf);

    ctx.main_loop();

    ctx.shutdown();
}