#include <e2e/io/logger/ConsoleColor.h>

using namespace e2e::io;

#include <iostream>

#ifdef __linux__

namespace {
static constexpr const int ansiRedColor = 31;
static constexpr const int ansiGreenColor = 32;
static constexpr const int ansiYellowColor = 33;
static constexpr const int ansiWhiteColor = 37;
}  // namespace

void console::setColorTo(Color color) {
    switch (color) {
        case Color::Red:
            std::cout << "\033[1;" << ansiRedColor << "m";
            break;

        case Color::Yellow:
            std::cout << "\033[1;" << ansiYellowColor << "m";
            break;

        case Color::Green:
            std::cout << "\033[1;" << ansiGreenColor << "m";
            break;

        case Color::White:
            std::cout << "\033[1;" << ansiWhiteColor << "m";
            break;

        case Color::Default:
            std::cout << "\033[0m";
            break;

        default:
            break;
    }
}

#endif

#ifdef _WIN32

#include <windows.h>

namespace {
static constexpr const int winRedColor = 12;
static constexpr const int winGreenColor = 10;
static constexpr const int winYellowColor = 14;
static constexpr const int winWhiteColor = 7;
static constexpr const int winDefaultColor = 7;
}  // namespace

void console::setColorTo(Color color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    switch (color) {
        case Color::Red:
            SetConsoleTextAttribute(hConsole, winRedColor);
            break;

        case Color::Yellow:
            SetConsoleTextAttribute(hConsole, winYellowColor);
            break;

        case Color::Green:
            SetConsoleTextAttribute(hConsole, winGreenColor);
            break;

        case Color::White:
            SetConsoleTextAttribute(hConsole, winWhiteColor);
            break;

        case Color::Default:
            SetConsoleTextAttribute(hConsole, winDefaultColor);
            break;

        default:
            break;
    }
}

#endif
