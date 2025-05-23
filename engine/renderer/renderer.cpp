#include <renderer/renderer.hpp>

mnm::renderer::renderer(logger& logger) : m_logger(logger)
{

}

mnm::renderer::~renderer()
{
}

bool mnm::renderer::init()
{
    m_logger.log_trace("Renderer initialized");
    return true;
}

void mnm::renderer::shutdown()
{
    m_logger.log_trace("Renderer destroyed");
}

void mnm::renderer::render(f64 delta_time)
{
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_TRIANGLES);
        glColor3f(1.0f, 0.0f, 0.0f); glVertex3f(0.0f, 1.0f, 0.0f);
        glColor3f(0.0f, 1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 0.0f);
        glColor3f(0.0f, 0.0f, 1.0f); glVertex3f(1.0f, -1.0f, 0.0f);
    glEnd();
}
