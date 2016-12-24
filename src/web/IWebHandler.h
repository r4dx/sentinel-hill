#ifndef IWEBHANDLER_H
#define IWEBHANDLER_H

#include "IWebServer.h"
#include "Method.h"

namespace sentinel {
    namespace web {
        class IWebHandler {
        public:
            virtual ~IWebHandler() {};
            virtual std::string path() const = 0;
            virtual Method method() const = 0;

            virtual void setSender(IWebSender& sender) = 0;
            virtual void process() = 0;
        };
    }
}
#endif