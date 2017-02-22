#include "RemoveLogHandler.h"
#include <SPI.h>
#include "time/TimeString.h"
#include <logger/ConsoleFileLoggerWrapper.h>
#include "sd/File.h"
#include "sd/SDWebFile.h"
#include "web/IWebFile.h"


/*
 * Proper way to do it:
 * Logger is interface (N.B. problems with template functions!!)
 * 
 * There's ILogger implementation which handles file:
 * constructor gets filename and Stream and creates TwoStreams
 * destructor closes file.
 * 
 * There's a wrapper around default logger implementation that manages state - 
 * class ManagedLogger : public ILogger with 3 new public methods 
 * if stop() is called it stops processing log commands - e.g. does nothing on info()
 * if start() is called it starts processing log commands
 * setLoggger(ILogger*) is a way to substitute underlying logger.
  * 
 * This class must get ManagedLogger as a parameter and reinitialize 
 * underlying logger each time it's required to remove logs.
 * 
 * Other classes must work with ILogger.
 * 
 * 
 * Another way around:
 * Save TwoStreams pointer in LoggerFactory
 * Support stop/start methods and streams substitution in TwoStreams
 * Support erase method in LoggerFactory which 
 * - stops 1 stream from TwoStreams (logs go only to console)
 * - closes file
 * - removes file
 * - creates file
 * - substitute stream in TwoStreams
 * - starts stream in TwoStreams (logs go both to new file and to console)
 * 
 * Make LoggerFactory non-static
 * Rename LoggerFactory to FileLoggerWrapper
 * 
 * class FileLoggerWrapper {
 * public:
 *   FileLoggerWrapper(fileName);
 *   ~FileLoggerWrapper() { twoStreams.close(); };
 *   Logger* get();
 *   void erase();
 * }
 * 
 * Pass FileLoggerWrapper to constructor of this class
 * Other classes work with Logger
 * 
 */

namespace sentinel {
    namespace handler {
        namespace log {
            
            void RemoveLogHandler::setPath(web::Method method, std::shared_ptr<std::string> uri) {   
                this->uri = uri;
                this->method = method;
            }                
                
            bool RemoveLogHandler::canHandle() const {   
                return uri->compare("/logs") == 0 && 
                        method == web::Method::DELETE;
            }

            RemoveLogHandler::RemoveLogHandler(
                sentinel::log::ConsoleFileLoggerWrapper& loggerWrapper) : 
                    loggerWrapper(loggerWrapper), 
                    sender(nullptr),
                    uri(std::shared_ptr<std::string>()),
                    method(web::Method::GET)
            {

            }

            void RemoveLogHandler::setSender(web::IWebSender& sender) {
                this->sender = &sender;
            }

            bool RemoveLogHandler::handle() {
                if (!loggerWrapper.erase()) {
                    sender->send(500, "text/html", "Failure");
                    return false;
                }
                sender->send(200, "text/html", "OK");
                return true;
            }
        }
    }
}