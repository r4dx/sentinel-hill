#ifndef IWEBSERVER_H
#define IWEBSERVER_H

#include "IWebHandler.h"
#include "logger/logger.h"
#include "IWebFile.h"

namespace sentinel {
    namespace web {
        
        class IWebHandler;
        
        class IWebServer {
        public:
            virtual ~IWebServer() { };

            virtual bool on(IWebHandler& handler) = 0;
            virtual void start() = 0;
            virtual void process() = 0;
            virtual void stop() = 0;
        };
        
        class IWebSender {
        public:
            virtual ~IWebSender() { };
            
            virtual void send(int code, const std::string& content_type, 
                const std::string& content) = 0;
            
            virtual void sendContent(const std::string& content) = 0;
            
            virtual size_t streamFile(IWebFile& file, 
                const std::string& contentType) = 0;

        };
    }
}
#endif