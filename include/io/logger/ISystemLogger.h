#ifndef _I_SYSTEM_LOGGER_H_
#define _I_SYSTEM_LOGGER_H_

#include <string>

class ISystemLogger {
   public:
    virtual void logInfo(const std::string& infoMessage) const = 0;

    virtual void logWarning(const std::string& warningMessage) const = 0;

    virtual void logError(const std::string& errorMessage) const = 0;

    /**
     * @brief logs a message
     *
     * Effectively the same as `logInfo`, except it doesn't prefix the message
     * with the "INFO:" string and current time, logging the message exactly as
     * passed. Keep in mind that this method will also not output any newline
     * character after the message has been logged, unlike all other logging
     * methods. The newline character should be included as a part of the
     * message if it is neccesarry
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