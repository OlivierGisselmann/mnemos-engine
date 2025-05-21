#include <platform/platform_linux.hpp>
#include <core/log.hpp>

#ifdef MNEMOS_PLATFORM_LINUX

void mnm::linux_window::init(const mnm::window_config& config)
{
    // Get display
    m_display = XOpenDisplay(nullptr);
    if(nullptr == m_display)
        return;

    // Get root window
    Window root = DefaultRootWindow(m_display);
    if(None == root)
        return;

    // Create window
    m_window = XCreateSimpleWindow(m_display, root, 0, 0, config.width, config.height, 0, 0, 0xffffffff);
    if(None == m_window)
        return;

    wm_delete_window = XInternAtom(m_display, "WM_DELETE_WINDOW", False);
    XSetWMProtocols(m_display, m_window, &wm_delete_window, 1);
        
    // Set window title
    XStoreName(m_display, m_window, config.title);

    // Show the window
    XMapWindow(m_display, m_window);
}

void mnm::linux_window::shutdown()
{
    XDestroyWindow(m_display, m_window);
    XCloseDisplay(m_display);
}

void mnm::linux_window::update()
{
    XNextEvent(m_display, &m_event);

    switch (m_event.type)
    {
    case ClientMessage:
        if(m_event.xclient.data.l[0] == wm_delete_window)
            m_close_requested = true;
    }
}

bool mnm::linux_window::close_requested()
{
    return m_close_requested;
}

#endif