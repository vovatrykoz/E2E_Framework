#include <Analysis.h>
#include <Setup.h>

#include <iostream>
#include <memory>
#include <optional>

using namespace e2e;
using namespace e2e::io;

void printUsageInfo();

int main(int argc, char* argv[]) {
    ConsoleTaskReader ctr;
    std::vector<NamedTask> tasks = ctr.readTaskChain();

    int bruh = 1;
}

void printUsageInfo() {
    std::cerr << "Usage: runner <reader_type> <logger_type>" << std::endl;
    std::cerr << "Currently supported loggers: Console, Text" << std::endl;
    std::cerr << "Currently supported readers: Console, Text" << std::endl;
}
