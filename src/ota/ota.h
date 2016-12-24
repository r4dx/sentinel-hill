#ifndef UNIT_TEST
#ifndef OTA_H
#define OTA_H

#define OTA_ENABLED 1

#include "logger/logger.h"
#include <string>

namespace sentinel {
    namespace ota {
        class OverTheAirUploadReceiver {
        public:
            OverTheAirUploadReceiver(log::Logger& logger, const std::string& ssid, 
                    const std::string& password);
            bool process();

        private:
            bool started = false;
        };
    }
}
#endif
#endif