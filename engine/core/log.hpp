#pragma once

#include <string>

namespace mnm
{
    enum verbosity
    {
        FATAL,
        ERROR,
        WARN,
        DEBUG,
        TRACE
    };

    class logger
    {
    public:
        void init();
        void shutdown();

        void log_fatal(const std::string& message);
        void log_error(const std::string& message);
        void log_warn(const std::string& message);
        void log_debug(const std::string& message);
        void log_trace(const std::string& message);

        void set_verbosity(verbosity verb);
    
    private:
        void log(verbosity verb, const std::string& message);
        const std::string_view verbosity_to_string(verbosity verb);
        const std::string get_timestamp();

        verbosity m_verbosity_level{verbosity::FATAL};
    };
}
