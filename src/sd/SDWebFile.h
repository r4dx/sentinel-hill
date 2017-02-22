#ifndef SDWEBFILE_H
#define SDWEBFILE_H
#include <SD.h>
#include "web/IWebFile.h"

namespace sentinel {
    namespace sd {
        namespace file {
            class SDWebFile : public sentinel::web::IWebFile {
            public:
                SDWebFile(File* file) : file(file) {};

                size_t size() override { return file->size(); };
                String name() override { return file->name(); };
                size_t available() override { return file->available(); };

                void read(uint8_t* buffer, size_t will_send) override { 
                    file->read(buffer, will_send); 
                };

            private:
                File* file;
            };
        }
    }
}
#endif /* SDWEBFILE_H */

