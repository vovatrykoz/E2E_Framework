#include <e2e/io/logger/ConsoleLogger.h>
#include <e2e/io/logger/SimplifiedConsoleLogger.h>
#include <e2e/io/reader/PlainTextTaskInstanceReader.h>
#include <e2e/io/reader/PlainTextTaskReader.h>
#include <e2e/setup/Factory.h>
#include <e2e/setup/Preset.h>

#include <iostream>

using namespace e2e::io;

std::unique_ptr<ITaskInstanceReader>
e2e::setup::preset::makeDefaultTaskInstanceReader() {
    std::string inputPath;
    std::cout << "Reader type: text" << std::endl;
    std::cout << "Enter path to input file: ";
    std::cin >> inputPath;
    return factory::makeTaskInstanceReader<PlainTextTaskInstanceReader>(
        inputPath);
}

std::unique_ptr<ITaskReader> e2e::setup::preset::makeDefaultTaskReader(
    const std::string& filePath) {
    return factory::makeTaskReader<PlainTextTaskReader>(filePath);
}

std::unique_ptr<IResultLogger> e2e::setup::preset::makeDefaultLogger() {
    std::cout << "Logger type: console" << std::endl;
    return factory::makeLogger<ConsoleLogger>();
}

std::unique_ptr<IResultLogger>
e2e::setup::preset::makeDefaultSimplifiedLogger() {
    return factory::makeLogger<SimplifiedConsoleLogger>();
}