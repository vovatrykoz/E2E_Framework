#ifndef _FACTORY_H_
#define _FACTORY_H_

#include <io/logger/ILogger.h>
#include <io/reader/ITaskInstanceReader.h>
#include <io/reader/ITaskReader.h>

#include <memory>
#include <optional>

namespace e2e {
namespace setup {
namespace factory {

using namespace e2e::io;

template <typename LoggerType, typename... Args>
std::unique_ptr<ILogger> makeLogger(Args... args)
    requires std::is_base_of_v<ILogger, LoggerType>;

template <typename TaskInstanceReaderType, typename... Args>
std::unique_ptr<ITaskInstanceReader> makeTaskInstanceReader(Args... args)
    requires std::is_base_of_v<ITaskInstanceReader, TaskInstanceReaderType>;

template <typename TaskReaderType, typename... Args>
std::unique_ptr<ITaskReader> makeTaskReader(Args... args)
    requires std::is_base_of_v<ITaskReader, TaskReaderType>;

template <typename LoggerType, typename... Args>
inline std::unique_ptr<ILogger> makeLogger(Args... args)
    requires std::is_base_of_v<ILogger, LoggerType>
{
    return std::make_unique<LoggerType>(args...);
}

template <typename TaskInstanceReaderType, typename... Args>
inline std::unique_ptr<ITaskInstanceReader> makeTaskInstanceReader(Args... args)
    requires std::is_base_of_v<ITaskInstanceReader, TaskInstanceReaderType>
{
    return std::make_unique<TaskInstanceReaderType>(args...);
}

template <typename TaskReaderType, typename... Args>
inline std::unique_ptr<ITaskReader> makeTaskReader(Args... args)
    requires std::is_base_of_v<ITaskReader, TaskReaderType>
{
    return std::make_unique<TaskReaderType>(args...);
}

}  // namespace factory
}  // namespace setup
}  // namespace e2e

#endif