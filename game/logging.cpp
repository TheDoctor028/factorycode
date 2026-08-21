#include "logging.h"

#include <iostream>

namespace factorycode {

    void log(LogLevel level, std::string_view message) {
        switch (level) {
            case LogLevel::Debug:
#if defined(DEBUG) || defined(ENABLE_DEBUG_LOGGING) || !defined(NDEBUG)
                std::cout << "[DEBUG]: " << message << std::endl;
#endif
                break;
            case LogLevel::Info:
                std::cout << "[INFO]: " << message << std::endl;
                break;
            case LogLevel::Warn:
                std::cout << "[WARN]: " << message << std::endl;
                break;
            case LogLevel::Error:
                std::cerr << "[ERROR]: " << message << std::endl;
                break;
        }
    }

    void debug(std::string_view message) {
#if defined(DEBUG) || defined(ENABLE_DEBUG_LOGGING) || !defined(NDEBUG)
        std::cout << "[DEBUG]: " << message << std::endl;
#else
        (void)message;
#endif
    }

    void debug(const char* message) {
#if defined(DEBUG) || defined(ENABLE_DEBUG_LOGGING) || !defined(NDEBUG)
        if (message != nullptr) {
            std::cout << "[DEBUG]: " << message << std::endl;
        }
#else
        (void)message;
#endif
    }

    void info(std::string_view message) {
        std::cout << "[INFO]: " << message << std::endl;
    }

    void warn(std::string_view message) {
        std::cout << "[WARN]: " << message << std::endl;
    }

    void error(std::string_view message) {
        std::cerr << "[ERROR]: " << message << std::endl;
    }

}
