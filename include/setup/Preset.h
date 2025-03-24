#ifndef _PRESET_H_
#define _PRESET_H_

#include <setup/Setup.h>

namespace e2e {
namespace setup {
namespace preset {

std::unique_ptr<ITaskInstanceReader> makeDefaultTaskInstanceReader();
std::unique_ptr<ITaskReader> makeDefaultTaskReader();
std::unique_ptr<IResultLogger> makeDefaultLogger();
std::unique_ptr<IResultLogger> makeDefaultSimplifiedLogger();

}  // namespace preset
}  // namespace setup
}  // namespace e2e

#endif