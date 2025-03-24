#ifndef _I_SYSTEM_LOGGER_H_
#define _I_SYSTEM_LOGGER_H_

#include <string>

class ISystemLogger {
   public:
    virtual void logInfo(const std::string& infoMessage) const = 0;

    virtual void logWarning(const std::string& warningMessage) const = 0;

    virtual void logError(const std::string& errorMessage) const = 0;

    /**
     * @brief Virtual destructor for the logger.
     *
     * This virtual destructor ensures proper cleanup of any derived classes.
     */
    virtual ~ISystemLogger() = default;
};

#endif