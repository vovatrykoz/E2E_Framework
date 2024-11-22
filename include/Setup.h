#ifndef _SETUP_H_
#define _SETUP_H_

#include <io/ConsoleLogger.h>
#include <io/ConsoleTaskReader.h>
#include <io/TaskInstanceInputReader.h>
#include <io/TaskInstanceSimpleTextReader.h>
#include <io/TextLogger.h>

#include <memory>
#include <optional>

namespace e2e {
namespace setup {

using namespace e2e::io;

enum class SupportedLogger { Console, Text };
enum class SupportedTaskInstanceReader { Console, Text };
enum class SupportedTaskReader { Console };

// Get supported types from string-----------------------------------

std::optional<SupportedLogger> getSupportedLoggerFromString(
    const std::string& loggerStr);

std::optional<SupportedTaskInstanceReader>
getSupportedTaskInstanceReaderFromString(const std::string& readerStr);

std::optional<SupportedTaskReader> getSupportedTaskReaderFromString(
    const std::string& readerStr);

// Get supported types from string-----------------------------------

// Get objects from supported types----------------------------------

std::unique_ptr<ILogger> getLoggerFromType(SupportedLogger loggerType);
std::unique_ptr<ITaskInstanceReader> getTaskInstanceReaderFromType(
    SupportedTaskInstanceReader readerType);
std::unique_ptr<ITaskReader> getTaskReaderFromType(
    SupportedTaskReader readerType);

// Get objects from supported types----------------------------------

// Get objects from strings types------------------------------------

std::unique_ptr<ILogger> logger(const std::string& loggerStr);
std::unique_ptr<ITaskInstanceReader> taskInstancereader(
    const std::string& readerStr);
std::unique_ptr<ITaskReader> taskReader(const std::string& readerStr);

// Get objects from strings types------------------------------------

}  // namespace setup
}  // namespace e2e

#endif