#include "io/logger/ConsoleSystemLogger.h"

#include <chrono>
#include <iostream>

using namespace e2e::io;

ConsoleSystemLogger::ConsoleSystemLogger(
    const std::function<void(console::Color)>& setConsoleTextColor)
    : setConsoleTextColor(setConsoleTextColor) {}

void ConsoleSystemLogger::logInfo(const std::string& infoMessage) const {
    const std::string currentTime = this->currentTime();

    this->setConsoleTextColor(console::Color::White);
    std::cout << "(" << currentTime << ") ";

    this->setConsoleTextColor(console::Color::Green);
    std::cout << "INFO";

    this->setConsoleTextColor(console::Color::White);
    std::cout << ": " << infoMessage << "\n";
}

void ConsoleSystemLogger::logWarning(const std::string& warningMessage) const {
    const std::string currentTime = this->currentTime();

    this->setConsoleTextColor(console::Color::White);
    std::cout << "(" << currentTime << ") ";

    this->setConsoleTextColor(console::Color::Yellow);
    std::cout << "WARNING";

    this->setConsoleTextColor(console::Color::White);
    std::cout << ": " << warningMessage << "\n";
}

void ConsoleSystemLogger::logError(const std::string& errorMessage) const {
    const std::string currentTime = this->currentTime();

    this->setConsoleTextColor(console::Color::White);
    std::cout << "(" << currentTime << ") ";

    this->setConsoleTextColor(console::Color::Red);
    std::cout << "ERROR";

    this->setConsoleTextColor(console::Color::White);
    std::cout << ": " << errorMessage << "\n";
}

void e2e::io::ConsoleSystemLogger::logMessage(
    const std::string& message) const {
    this->setConsoleTextColor(console::Color::White);
    std::cout << message;
}

std::string ConsoleSystemLogger::currentTime() {
    const auto now = std::chrono::system_clock::now();
    const std::time_t now_time_t = std::chrono::system_clock::to_time_t(now);
#ifdef _MSC_VER
    const std::tm local_tm = *std::localtime_s(&now_time_t);
#else
    const std::tm local_tm = *std::localtime(&now_time_t);
#endif

    std::ostringstream oss;
    oss << std::put_time(&local_tm, "%Y-%m-%d %H:%M:%S");

    return oss.str();
}
