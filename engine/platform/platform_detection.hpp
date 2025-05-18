#pragma once

// OS detection
#if defined(__linux__) || defined(__linux) || defined(linux)
    #define MNEMOS_PLATFORM_LINUX
#elif defined(__WIN32__) || defined(__WIN32) || defined(_WIN32) || defined(WIN32)
    #define MNEMOS_PLATFORM_WINDOWS
#else
    #error "Unsupported OS"
#endif

// Architecture detection
#if defined(__x86_64__) || defined(_M_X64)
    #define MNEMOS_ARCH_X64
#elif defined(i386) || defined(__i386__) || defined(__i386) || defined(_M_X86)
    #define MNEMOS_ARCH_X86
#else
    #error "Unsupported architecture"
#endif