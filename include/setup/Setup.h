#ifndef _SETUP_H_
#define _SETUP_H_

#include <io/logger/IResultLogger.h>
#include <io/reader/ITaskInstanceReader.h>
#include <io/reader/ITaskReader.h>

#include <memory>
#include <optional>

namespace e2e {
namespace setup {

using namespace e2e::io;

std::unique_ptr<IResultLogger> logger(const std::string& loggerStr);
std::unique_ptr<IResultLogger> simpleLogger(const std::string& loggerStr);
std::unique_ptr<ITaskInstanceReader> taskInstanceReader(
    const std::string& readerStr);
std::unique_ptr<ITaskReader> taskReader(const std::string& readerStr);

}  // namespace setup
}  // namespace e2e

#endif