#pragma once

#include <string_view>

namespace factorycode {

    /**
     * @brief Severity levels for logging output.
     */
    enum class LogLevel {
        Debug,
        Info,
        Warn,
        Error
    };

    /**
     * @brief Core logging function that outputs a formatted message with level prefix.
     * @param level Severity level of the log message.
     * @param message Text message to be logged.
     */
    void log(LogLevel level, std::string_view message);

    /**
     * @brief Logs a debug level message if debug logging is enabled by build flag.
     * @param message Text message to log.
     */
    void debug(std::string_view message);

    /**
     * @brief Overload for C-style string debug logging.
     * @param message C-string message to log.
     */
    void debug(const char* message);

    /**
     * @brief Logs an informational message.
     * @param message Text message to log.
     */
    void info(std::string_view message);

    /**
     * @brief Logs a warning message.
     * @param message Text message to log.
     */
    void warn(std::string_view message);

    /**
     * @brief Logs an error message to standard error.
     * @param message Text message to log.
     */
    void error(std::string_view message);

}
