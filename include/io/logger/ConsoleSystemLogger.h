#ifndef _CONSOLE_LOGGER_H_
#define _CONSOLE_LOGGER_H_

#include <io/logger/ISystemLogger.h>

namespace e2e {
namespace io {

class ConsoleSystemLogger : public ISystemLogger {
   public:
    virtual void logInfo(const std::string& infoMessage) const override;

    virtual void logWarning(const std::string& warningMessage) const override;

    virtual void logError(const std::string& errorMessage) const override;

    virtual void logMessage(const std::string& message) const override;

   private:
    static std::string currentTime();
};

}  // namespace io
}  // namespace e2e

#endif