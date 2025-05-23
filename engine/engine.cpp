#include <engine.hpp>

#include <core/log.hpp>

// Static instances
// TODO: Implement singleton?
static mnm::logger s_logger;

mnm::context::context() : m_renderer(s_logger), m_timer(s_logger)
{

}

mnm::context::~context()
{

}

void mnm::context::init(const context_config& config)
{
    // Start up engine
    m_running = true;

    // Init subsystems
    init_logging();
    init_window(config.width, config.height, config.window_title);
    init_renderer();
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
        m_window = new mnm::linux_window(s_logger);

        if(!m_window->init({width, height, title}))
            s_logger.log_fatal("Failed to initialize window");
    #elif defined(MNEMOS_PLATFORM_WINDOWS)
        // TODO: Windows implementation
    #endif
}

void mnm::context::init_renderer()
{
    if(!m_renderer.init())
        s_logger.log_fatal("Failed to initialize renderer");

    m_timer.init();
}

void mnm::context::shutdown()
{
    s_logger.log_trace("Engine shutdown");

    // Shutdown renderer
    m_renderer.shutdown();

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
        update_timer();
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
    
    // Stop main loop if user closes the window
    if(m_window->close_requested())
        m_running = false;
}

void mnm::context::update_timer()
{
    m_timer.update();
}

void mnm::context::render_scene()
{
    m_renderer.render();
}

void mnm::context::swap_buffers()
{
    m_window->swap_buffers();
    m_timer.tick();
}
