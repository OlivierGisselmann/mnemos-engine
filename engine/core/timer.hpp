#pragma once

#include <platform/types.hpp>
#include <core/log.hpp>

#include <chrono>
#include <unistd.h>

namespace mnm
{
    class timer
    {
    public:
        timer(logger& logger);
        ~timer();

        void init(f32 target_framerate, bool show_fps);
        void update();
        void sleep();

        f64 get_delta_time();

    private:
        std::chrono::_V2::system_clock::time_point m_last_time;
        std::chrono::_V2::system_clock::time_point m_current_time;
        f64 m_delta_time{};
        f64 m_sleep_time{};

        i64 m_frame_count{};
        f64 m_frame_time{};
        f64 m_fps_timer{};

        bool m_show_fps;
        f32 m_target_framerate;

        // Utils
        logger& m_logger;
    };
}
