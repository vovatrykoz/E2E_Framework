#ifndef _COMMAND_LINE_ARGS_H_
#define _COMMAND_LINE_ARGS_H_

#include <optional>
#include <string>

namespace e2e {
namespace io {

struct CommandLineArgs {
    std::string filePath;
    std::optional<std::string> readerType;
    std::optional<std::string> loggerType;
};

}  // namespace io
}  // namespace e2e

#endif