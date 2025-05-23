#ifndef _I_SYSTEM_LOGGER_H_
#define _I_SYSTEM_LOGGER_H_

#include <string>

/**
 * @brief Interface for a system logger that provides methods for logging
 *        information, warnings, errors, and raw messages.
 */
class ISystemLogger {
public:
    /**
     * @brief Logs an informational message.
     *
     * @param infoMessage The message to be logged as information.
     */
    virtual void logInfo(const std::string& infoMessage) const = 0;

    /**
     * @brief Logs a warning message.
     *
     * @param warningMessage The message to be logged as a warning.
     */
    virtual void logWarning(const std::string& warningMessage) const = 0;

    /**
     * @brief Logs an error message.
     *
     * @param errorMessage The message to be logged as an error.
     */
    virtual void logError(const std::string& errorMessage) const = 0;

    /**
     * @brief Logs a raw message.
     *
     * Effectively the same as `logInfo`, except it doesn't prefix the message
     * with the "INFO:" string and current time, logging the message exactly as
     * passed. Keep in mind that this method will also not output any newline
     * character after the message has been logged, unlike all other logging
     * methods. The newline character should be included as a part of the
     * message if it is necessary.
     *
     * @param message The exact message to be logged, including any newline
     * characters if needed.
     */
    virtual void logMessage(const std::string& message) const = 0;

    /**
     * @brief Virtual destructor for the logger.
     *
     * This virtual destructor ensures proper cleanup of any derived classes.
     */
    virtual ~ISystemLogger() = default;
};

#endif
