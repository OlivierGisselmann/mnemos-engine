#include <engine.hpp>

#include <iostream>

void game_loop();

int main()
{
    mnm::context ctx{};

    ctx.init();

    ctx.main_loop();

    game_loop();

    ctx.shutdown();
}

void game_loop()
{
    std::cout << "Game Loop\n";
}