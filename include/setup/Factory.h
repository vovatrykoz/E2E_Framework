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

/**
 * @brief Creates a logger of the specified type.
 *
 * This function creates a logger based on the provided type, which
 * must be derived from `ILogger`. Any necessary arguments to the
 * constructor of the logger type can be passed directly into this function.
 *
 * @tparam LoggerType The type of the logger. Must inherit from `ILogger`.
 * @tparam Args Any additional arguments for the logger constructor.
 * @param args Arguments forwarded to the constructor of the logger type.
 * @return A unique pointer to the created logger instance.
 */
template <typename LoggerType, typename... Args>
std::unique_ptr<ILogger> makeLogger(Args... args)
    requires std::is_base_of_v<ILogger, LoggerType>;

/**
 * @brief Creates a task instance reader of the specified type.
 *
 * This function creates a task instance reader based on the provided type,
 * which must be derived from `ITaskInstanceReader`. Any arguments
 * required for the constructor of the reader type can be passed directly into
 * this function.
 *
 * @tparam TaskInstanceReaderType The type of the task instance reader. Must
 * inherit from `ITaskInstanceReader`.
 * @tparam Args Any additional arguments for the task instance reader
 * constructor.
 * @param args Arguments forwarded to the constructor of the task instance
 * reader type.
 * @return A unique pointer to the created task instance reader.
 */
template <typename TaskInstanceReaderType, typename... Args>
std::unique_ptr<ITaskInstanceReader> makeTaskInstanceReader(Args... args)
    requires std::is_base_of_v<ITaskInstanceReader, TaskInstanceReaderType>;

/**
 * @brief Creates a task reader of the specified type.
 *
 * This function creates a task reader based on the provided type, which must
 * be derived from `ITaskReader`. Any necessary arguments for
 * the constructor of the reader type can be passed directly into this function.
 *
 * @tparam TaskReaderType The type of the task reader. Must inherit from
 * `ITaskReader`.
 * @tparam Args Any additional arguments for the task reader constructor.
 * @param args Arguments forwarded to the constructor of the task reader type.
 * @return A unique pointer to the created task reader.
 */
template <typename TaskReaderType, typename... Args>
std::unique_ptr<ITaskReader> makeTaskReader(Args... args)
    requires std::is_base_of_v<ITaskReader, TaskReaderType>;

// INLINE FUNCTION DEFINITIONS BELOW
// ---------------------------------------------

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