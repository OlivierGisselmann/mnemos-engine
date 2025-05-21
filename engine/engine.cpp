#include <engine.hpp>

#include <core/log.hpp>

// Static instances
// TODO: Implement singleton?
static mnm::logger s_logger;

void mnm::context::init(const context_config& config)
{
    // Start up engine
    m_running = true;

    init_logging();
    init_window(config.width, config.height, config.window_title);
}

void mnm::context::init_logging()
{
    s_logger.init();
    s_logger.set_verbosity(mnm::verbosity::TRACE);

    s_logger.log_trace("Engine initialization");
}

void mnm::context::init_window(u16 width, u16 height, const char* title)
{
    #if defined(MNEMOS_PLATFORM_LINUX)
        m_window = new mnm::linux_window();
        m_window->init({width, height, title});
    #elif defined(MNEMOS_PLATFORM_WINDOWS)
        // TODO: Windows implementation
    #endif
}

void mnm::context::shutdown()
{
    s_logger.log_trace("Engine shutdown");

    // Destroy window
    m_window->shutdown();
    delete m_window;

    s_logger.shutdown();
}

void mnm::context::main_loop()
{
    while(m_running)
    {
        poll_inputs();
        update_window();
        render_scene();
        swap_buffers();
    }
}

void mnm::context::poll_inputs()
{

}

void mnm::context::update_window()
{
    m_window->update();
    
    if(m_window->close_requested())
        m_running = false;
}

void mnm::context::render_scene()
{

}

void mnm::context::swap_buffers()
{

}
