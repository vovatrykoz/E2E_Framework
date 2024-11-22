#ifndef _SETUP_H_
#define _SETUP_H_

#include <io/ConsoleLogger.h>
#include <io/InputReader.h>
#include <io/SimpleTextReader.h>
#include <io/TextLogger.h>

#include <memory>
#include <optional>

namespace e2e {
namespace setup {

using namespace e2e::io;

enum class SupportedLogger { Console, Text };
enum class SupportedReader { Console, Text };

std::optional<SupportedLogger> getSupportedLoggerFromString(
    const std::string& loggerStr);
std::optional<SupportedReader> getSupportedReaderFromString(
    const std::string& readerStr);

std::unique_ptr<ILogger> getLoggerFromType(SupportedLogger loggerType);
std::unique_ptr<IReader> getReaderFromType(SupportedReader readerType);

std::unique_ptr<ILogger> logger(const std::string& loggerStr);
std::unique_ptr<IReader> reader(const std::string& readerStr);

}  // namespace setup
}  // namespace e2e

#endif