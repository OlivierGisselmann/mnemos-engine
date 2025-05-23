#pragma once

#include <core/log.hpp>
#include <platform/types.hpp>

#include <GL/gl.h>

namespace mnm
{
    class renderer
    {
    public:
        renderer(logger& logger);
        ~renderer();

        bool init();
        void shutdown();

        void render(f64 delta_time);

    private:
        logger& m_logger;
    }; 
}
