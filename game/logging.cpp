#include "logging.h"

#include <iostream>

namespace factorycode {

    void log(LogLevel level, std::string_view message) {
        switch (level) {
            case LogLevel::Debug:
                std::cout << "[DEBUG]: " << message << std::endl;
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
        std::cout << "[DEBUG]: " << message << std::endl;
    }

    void debug(const char* message) {
        if (message != nullptr) {
            std::cout << "[DEBUG]: " << message << std::endl;
        }
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
