#include <engine.hpp>

#include <iostream>

void game_loop();

int main()
{
    // TODO: Fill config struct from JSON file
    constexpr mnm::context_config conf
    {
        .width = 800,
        .height = 600,
        .window_title = "Game application",
        .fullscreen = false
    };

    mnm::context ctx{};
    ctx.init(conf);

    ctx.main_loop();

    game_loop();

    ctx.shutdown();
}

void game_loop()
{
    std::cout << "Game Loop\n";
}