#pragma once

#include <platform/types.hpp>

namespace mnm
{
    struct window_config
    {
        u16 width;
        u16 height;
        const char* title;
    };

    class window
    {
    public:
        virtual bool init(const window_config& config) = 0;
        virtual void shutdown() = 0;
        virtual ~window(){}

        virtual void update() = 0;
        virtual void swap_buffers() = 0;
        virtual bool close_requested() = 0;

    protected:
        bool m_close_requested;
    };
}
