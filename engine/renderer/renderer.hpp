#pragma once

#include <core/log.hpp>

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

        void render();

    private:
        logger& m_logger;
    }; 
}
