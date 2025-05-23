#include <core/timer.hpp>

using Clock = std::chrono::high_resolution_clock;

mnm::timer::timer(logger& logger) : m_logger(logger)
{

}

mnm::timer::~timer()
{

}

void mnm::timer::init(bool show_fps)
{
    m_last_time = Clock::now();
    m_show_fps = show_fps;
}

void mnm::timer::update()
{
    m_current_time = Clock::now();
    std::chrono::duration<f64> delta = m_current_time - m_last_time;
    m_delta_time = delta.count();

    m_last_time = m_current_time;
}

void mnm::timer::sleep()
{
    m_frame_time = (Clock::now() - m_current_time).count() / 1e9;
    m_sleep_time = (1.0 / 120.0) - m_frame_time;

    // Sleep if frame was shorter than targeted fps
    if(m_sleep_time > 0)
        usleep(static_cast<useconds_t>(m_sleep_time * 1e6));

    // Debug printing
    if(m_show_fps)
    {
        // Output FPS each second
        m_fps_timer += m_delta_time;
        m_frame_count++;
        if(m_fps_timer >= 1.0)
        {
            m_logger.log_debug(std::format("FPS: {}", m_frame_count));
            m_fps_timer = 0;
            m_frame_count = 0;
        }
    }
}

f64 mnm::timer::get_delta_time()
{
    return m_delta_time;
}
