#ifndef IWEBFILE_H
#define IWEBFILE_H

#include <stddef.h>

namespace sentinel {
    namespace web {
        class IWebFile {
        public:
            virtual ~IWebFile() {};
            virtual size_t size() = 0;
            virtual String name() = 0;
            virtual size_t available() = 0;
            virtual void read(uint8_t* buffer, size_t will_send) = 0;
        };
    }
}
#endif /* IWEBFILE_H */

