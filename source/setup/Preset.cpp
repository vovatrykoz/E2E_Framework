#include <io/logger/ConsoleLogger.h>
#include <io/logger/SimplifiedConsoleLogger.h>
#include <io/reader/PlainTextTaskInstanceReader.h>
#include <io/reader/PlainTextTaskReader.h>
#include <setup/Preset.h>

#include <iostream>

using namespace e2e::io;

std::unique_ptr<ITaskInstanceReader>
e2e::setup::preset::makeDefaultTaskInstanceReader() {
    std::string inputPath;
    std::cout << "Reader type: text" << std::endl;
    std::cout << "Enter path to input file: ";
    std::cin >> inputPath;
    return makeTaskInstanceReader<PlainTextTaskInstanceReader>(inputPath);
}

std::unique_ptr<ITaskReader> e2e::setup::preset::makeDefaultTaskReader() {
    std::string inputPath;
    std::cout << "Reader type: text" << std::endl;
    std::cout << "Enter path to input file: ";
    std::cin >> inputPath;
    return makeTaskReader<PlainTextTaskReader>(inputPath);
}

std::unique_ptr<ILogger> e2e::setup::preset::makeDefaultLogger() {
    return makeLogger<ConsoleLogger>();
}

std::unique_ptr<ILogger> e2e::setup::preset::makeDefaultSimplifiedLogger() {
    return makeLogger<SimplifiedConsoleLogger>();
}