#ifndef IWEBHANDLER_H
#define IWEBHANDLER_H

#include "IWebServer.h"
#include "Method.h"

namespace sentinel {
    namespace web {
        class IWebSender;
        
        class IWebHandler {
        public:
            virtual ~IWebHandler() {};
            
            virtual void setPath(Method method, std::string uri) = 0;
            virtual void setSender(IWebSender& sender) = 0;
            
            virtual bool canHandle() const = 0;
            virtual bool handle() = 0;
        };
    }
}
#endif