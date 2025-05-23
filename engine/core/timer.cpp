#include <core/timer.hpp>

mnm::timer::timer(logger& logger) : m_logger(logger)
{

}

mnm::timer::~timer()
{

}

void mnm::timer::init()
{
    m_prev_time = get_milliseconds();
    m_current_time = get_milliseconds();
    m_delta_time = 0.0;

    // TODO: Remove hardcoded FPS value
    m_skip_ticks = (1000.0 / 30);
    m_sleep_time = 0;

    gettimeofday(&m_time, nullptr);
    m_next_game_tick = (m_time.tv_sec * 1000.0) + (m_time.tv_usec / 1000.0);
}

void mnm::timer::update()
{
    m_current_time = get_milliseconds();
    m_delta_time = (m_current_time - m_prev_time) * 0.001;
    m_prev_time = m_current_time;
}

void mnm::timer::tick()
{
    gettimeofday(&m_time, nullptr);
    m_next_game_tick += m_skip_ticks;
    m_sleep_time = m_next_game_tick - ((m_time.tv_sec * 1000.0) + (m_time.tv_usec) / 1000.0);

    usleep((unsigned int)(m_sleep_time / 1000.0));
}

f64 mnm::timer::get_milliseconds()
{
    static timeval s_time_eval;
    gettimeofday(&s_time_eval, nullptr);

    f64 time = s_time_eval.tv_sec * 1000.0; // Seconds to Milliseconds
    time += s_time_eval.tv_usec / 1000.0; // Microseconds to Milliseconds

    return time;
}

f64 mnm::timer::get_delta_time()
{
    return m_delta_time;
}
