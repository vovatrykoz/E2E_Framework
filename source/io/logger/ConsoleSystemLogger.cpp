#include "io/logger/ConsoleSystemLogger.h"

#include <chrono>
#include <iostream>

using namespace e2e::io;

void ConsoleSystemLogger::logInfo(const std::string& infoMessage) const {
    std::cout << "(" << this->currentTime() << ") " << "INFO: " << infoMessage
              << "\n";
}

void ConsoleSystemLogger::logWarning(const std::string& warningMessage) const {
    std::cout << "(" << this->currentTime() << ") "
              << "WARNING: " << warningMessage << "\n";
}

void ConsoleSystemLogger::logError(const std::string& errorMessage) const {
    std::cerr << "(" << this->currentTime() << ") " << "ERROR: " << errorMessage
              << "\n";
}

void e2e::io::ConsoleSystemLogger::logMessage(
    const std::string& message) const {
    std::cout << message;
}

std::string ConsoleSystemLogger::currentTime() {
    auto now = std::chrono::system_clock::now();
    std::time_t now_time_t = std::chrono::system_clock::to_time_t(now);
    std::tm local_tm = *std::localtime(&now_time_t);

    std::ostringstream oss;
    oss << std::put_time(&local_tm, "%Y-%m-%d %H:%M:%S");

    return oss.str();
}
