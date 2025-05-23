#pragma once

#include <platform/types.hpp>
#include <core/log.hpp>

#include <sys/time.h>
#include <unistd.h>

namespace mnm
{
    class timer
    {
    public:
        timer(logger& logger);
        ~timer();

        void init();
        void update();
        void tick();

        f64 get_delta_time();

    private:
        f64 get_milliseconds();

        f64 m_prev_time;
        f64 m_current_time;
        f64 m_delta_time;
        f64 m_skip_ticks;

        timeval m_time;
        long m_sleep_time;
        long m_next_game_tick;

        // Utils
        logger& m_logger;
    };
}
