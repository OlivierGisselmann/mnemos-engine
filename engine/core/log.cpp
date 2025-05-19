#include <core/log.hpp>

#include <chrono>
#include <iostream>

void mnm::logger::init()
{

}

void mnm::logger::shutdown()
{

}

void mnm::logger::log(mnm::verbosity verb, const std::string& message)
{
    if(verb <= m_verbosity_level)
        std::cout << get_timestamp() << verbosity_to_string(verb) << ' ' << message << '\n';
}

void mnm::logger::log_fatal(const std::string& message)
{
    log(mnm::verbosity::FATAL, message);
}

void mnm::logger::log_error(const std::string& message)
{
    log(mnm::verbosity::ERROR, message);
}

void mnm::logger::log_warn(const std::string& message)
{
    log(mnm::verbosity::WARN, message);
}

void mnm::logger::log_debug(const std::string& message)
{
    log(mnm::verbosity::DEBUG, message);
}

void mnm::logger::log_trace(const std::string& message)
{
    log(mnm::verbosity::TRACE, message);
}

void mnm::logger::set_verbosity(verbosity verb)
{
    m_verbosity_level = verb;
}

const std::string_view mnm::logger::verbosity_to_string(verbosity verb)
{
    switch (verb)
    {
    case FATAL: return "[FATAL]";
    case ERROR: return "[ERROR]";
    case WARN: return "[WARN]";
    case DEBUG: return "[DEBUG]";
    case TRACE: return "[TRACE]";
    default: return "[]";
    }
}

const std::string mnm::logger::get_timestamp()
{
    // To enhance readability
    using namespace std::chrono;

    const auto now = floor<milliseconds>(zoned_time(current_zone(), system_clock::now()).get_local_time());

    return std::format("[{:%T}]", now);
}