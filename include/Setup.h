#ifndef _SETUP_H_
#define _SETUP_H_

#include <memory>
#include <optional>

#include <io/logger/ILogger.h>
#include <io/reader/ITaskReader.h>
#include <io/reader/ITaskInstanceReader.h>

namespace e2e {
namespace setup {

using namespace e2e::io;

enum class SupportedLogger { Console, Text, TaskConsole, TaskText };
enum class SupportedTaskInstanceReader { Console, Text };
enum class SupportedTaskReader { Console, Text };

// Get supported types from string-----------------------------------

std::optional<SupportedLogger> getSupportedLoggerFromString(
    const std::string& loggerStr);

std::optional<SupportedLogger> getSupportedSimpleLoggerFromString(
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
std::unique_ptr<ILogger> simpleLogger(const std::string& loggerStr);
std::unique_ptr<ITaskInstanceReader> taskInstanceReader(
    const std::string& readerStr);
std::unique_ptr<ITaskReader> taskReader(const std::string& readerStr);

// Get objects from strings types------------------------------------

}  // namespace setup
}  // namespace e2e

#endif