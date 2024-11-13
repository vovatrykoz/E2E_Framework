#include "TimedPath.h"

void TimedPath::popTaskInstance() {
    if(this->tasks.empty()) {
        return;
    }

    this->tasks.pop_back();
}

int TimedPath::endToEndDelay() const { return 0; }
