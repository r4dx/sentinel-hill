#ifndef UNIT_TEST
#include "TimeString.h"
#include "Arduino.h"

namespace sentinel {
    namespace time {
        std::string MillisTimeProvider::now() const {
            std::time_t rawTime = getUnixTime();   
            char* time = std::ctime(&rawTime);
            std::string result = std::string(time);
            return result;
        }

        std::time_t MillisTimeProvider::getUnixTime() const {
            return millis() / 1000;
        }
    }
}
#endif