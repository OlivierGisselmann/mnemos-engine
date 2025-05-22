#include <platform/platform_linux.hpp>
#include <core/log.hpp>

#include <cstring>

#ifdef MNEMOS_PLATFORM_LINUX

// GLX Utils
typedef GLXContext (*glXCreateContextAttribsARBProc)(Display*, GLXFBConfig, GLXContext, Bool, const int*);

static bool is_extension_supported(const char* extensions_list, const char* extension)
{
    return strstr(extensions_list, extension);
}

mnm::linux_window::linux_window(logger& logger) : m_logger(logger)
{
    
}

mnm::linux_window::~linux_window()
{
    
}

bool mnm::linux_window::init(const mnm::window_config& config)
{
    // Get display
    m_display = XOpenDisplay(nullptr);
    if(nullptr == m_display)
        return false;

    // Get screen and id
    m_screen = DefaultScreenOfDisplay(m_display);
    m_screen_id = DefaultScreen(m_display);

    // Query GLX version
    GLint majorGLX, minorGLX = 0;
    glXQueryVersion(m_display, &majorGLX, &minorGLX);
    if(majorGLX <= 1 && minorGLX < 2)
    {
        m_logger.log_fatal("GLX 1.2 or greater is required");
        return false;
    }

    // GLX Configuration
    GLint glxAttribs[] = 
    {
        GLX_X_RENDERABLE, True,
        GLX_DRAWABLE_TYPE, GLX_WINDOW_BIT,
        GLX_RENDER_TYPE, GLX_RGBA_BIT,
        GLX_X_VISUAL_TYPE, GLX_TRUE_COLOR,
        GLX_RED_SIZE, 8,
        GLX_GREEN_SIZE, 8,
        GLX_BLUE_SIZE, 8,
        GLX_ALPHA_SIZE, 8,
        GLX_DEPTH_SIZE, 24,
        GLX_STENCIL_SIZE, 8,
        GLX_DOUBLEBUFFER, True,
        None
    };

    // GLX framebuffer config
    int framebuffer_count;
    GLXFBConfig* framebuffer_config = glXChooseFBConfig(m_display, m_screen_id, glxAttribs, &framebuffer_count);
    if(framebuffer_config == 0)
    {
        m_logger.log_fatal("Failed to retrieve framebuffer");
        return false;
    }

    // Pick best available framebuffer config
    int best_config = -1, worst_config = -1, best_samples = -1, worst_samples = 999;
    for(int i = 0; i < framebuffer_count; ++i)
    {
        XVisualInfo* visual_info = glXGetVisualFromFBConfig(m_display, framebuffer_config[i]);

        if(visual_info != 0)
        {
            int sample_buffers, samples;
            glXGetFBConfigAttrib(m_display, framebuffer_config[i], GLX_SAMPLE_BUFFERS, &sample_buffers);
            glXGetFBConfigAttrib(m_display, framebuffer_config[i], GLX_SAMPLES, &samples);

            if(best_config < 0 || (sample_buffers && samples > best_samples))
            {
                best_config = i;
                best_samples = samples;
            }

            if (worst_config < 0 || !sample_buffers || samples < worst_samples)
            {
                worst_config = i;
                worst_samples = samples;
            }
        }

        XFree(visual_info);
    }

    // Set best available config and free query variables
    GLXFBConfig best_framebuffer_config = framebuffer_config[best_config];
    XFree(framebuffer_config);

    // Create visual window
    m_visual = glXGetVisualFromFBConfig(m_display, best_framebuffer_config);
    if(m_visual == 0)
    {
        m_logger.log_fatal("Could not create correct visual window");
        return false;
    }

    if(m_screen_id != m_visual->screen)
    {
        m_logger.log_fatal(std::format("screenID({}) does not match visual->screen({})", m_screen_id, m_visual->screen));
        return false;
    }

    // Set Window attributes
    m_window_attributes.border_pixel = BlackPixel(m_display, m_screen_id);
    m_window_attributes.background_pixel = WhitePixel(m_display, m_screen_id);
    m_window_attributes.override_redirect = True;
    m_window_attributes.colormap = XCreateColormap(m_display, RootWindow(m_display, m_screen_id), m_visual->visual, AllocNone);
    m_window_attributes.event_mask = ExposureMask;

    // Create Window
    m_window = XCreateWindow(
        m_display, RootWindow(m_display, m_screen_id),
        0, 0, config.width, config.height, 0,
        m_visual->depth, InputOutput, m_visual->visual,
        CWBackPixel | CWColormap | CWBorderPixel | CWEventMask,
        &m_window_attributes
    );

    m_logger.log_trace("Linux Window initialized");

    // Redirect close event
    wm_delete_window = XInternAtom(m_display, "WM_DELETE_WINDOW", False);
    XSetWMProtocols(m_display, m_window, &wm_delete_window, 1);
        
    // Set window title
    XStoreName(m_display, m_window, config.title);

    // Create OpenGL context
    glXCreateContextAttribsARBProc glXCreateContextAttribsARB = 0;
    glXCreateContextAttribsARB = (glXCreateContextAttribsARBProc)glXGetProcAddressARB((const GLubyte*) "glXCreateContextAttribsARB");

    int context_attribs[] = 
    {
        GLX_CONTEXT_MAJOR_VERSION_ARB, 3,
        GLX_CONTEXT_MINOR_VERSION_ARB, 2,
        GLX_CONTEXT_FLAGS_ARB, GLX_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
        None
    };

    // Get context extensions
    const char* glx_extensions = glXQueryExtensionsString(m_display, m_screen_id);
    if(!is_extension_supported(glx_extensions, "GLX_ARB_create_context"))
    {
        m_logger.log_warn("GLX_ARB_create_context not supported");
        m_context = glXCreateNewContext(m_display, best_framebuffer_config, GLX_RGBA_TYPE, 0, True);
    }
    else
    {
        m_context = glXCreateContextAttribsARB(m_display, best_framebuffer_config, 0, true, context_attribs);
    }
    XSync(m_display, false);

    // Check acquired context
    if(!glXIsDirect(m_display, m_context))
        m_logger.log_debug("Indirect GLX rendering context acquired");
    else
        m_logger.log_debug("Direct GLX rendering context acquired");

    // Make context current
    glXMakeCurrent(m_display, m_window, m_context);

    //m_logger.log_trace(std::format("GL Renderer: {}", glGetString(GL_RENDERER)));
    //m_logger.log_trace(std::format("GL Version: {}", glGetString(GL_VERSION)));
    //m_logger.log_trace(std::format("GLSL Version: {}", glGetString(GL_SHADING_LANGUAGE_VERSION)));

    // Show the window
    XClearWindow(m_display, m_window);
    XMapRaised(m_display, m_window);

    // Set clear color and initial viewport size
    glClearColor(0.5f, 0.6f, 0.7f, 1.0f);
    glViewport(0, 0, config.width, config.height);

    return true;
}

void mnm::linux_window::shutdown()
{
    glXDestroyContext(m_display, m_context);
    XFree(m_visual);
    XFreeColormap(m_display, m_window_attributes.colormap);

    XDestroyWindow(m_display, m_window);
    XCloseDisplay(m_display);

    m_logger.log_trace("Linux Window destroyed");
}

void mnm::linux_window::update()
{
    // Poll events
    if(XPending(m_display) > 0)
    {
        XNextEvent(m_display, &m_event);
        if(m_event.type == Expose)
        {
            XWindowAttributes attribs;
            XGetWindowAttributes(m_display, m_window, &attribs);
            glViewport(0, 0, attribs.width, attribs.height);
        }

        // Close event
        if(m_event.xclient.data.l[0] == wm_delete_window)
            m_close_requested = true;
        else if(m_event.type == DestroyNotify)
            m_close_requested = true;
    }
}

void mnm::linux_window::swap_buffers()
{
    glXSwapBuffers(m_display, m_window);
}

bool mnm::linux_window::close_requested()
{
    return m_close_requested;
}

#endif