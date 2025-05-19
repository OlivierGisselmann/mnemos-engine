#include <engine.hpp>

#include <core/log.hpp>

// Static instances
// TODO: Implement singleton?

static mnm::logger s_logger;

void mnm::context::init(const context_config& config)
{
    // Set up logging
    s_logger.init();
    s_logger.set_verbosity(mnm::verbosity::TRACE);

    s_logger.log_trace("Engine initialization");
}

void mnm::context::shutdown()
{
    s_logger.shutdown();
}

void mnm::context::main_loop()
{
    poll_inputs();
    update_window();
    render_scene();
    swap_buffers();
}

void mnm::context::poll_inputs()
{

}

void mnm::context::update_window()
{

}

void mnm::context::render_scene()
{

}

void mnm::context::swap_buffers()
{

}
