#ifndef _CONSOLE_COLOR_H_
#define _CONSOLE_COLOR_H_

namespace e2e {
namespace io {
namespace console {

enum class Color { Red, Green, Yellow, White, Default };

void setColorTo(Color color);

}  // namespace console
}  // namespace io
}  // namespace e2e

#endif