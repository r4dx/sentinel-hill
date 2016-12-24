#ifndef DUALSTREAMVALVE_H
#define DUALSTREAMVALVE_H

#include <Stream.h>
#include <Print.h>

namespace sentinel {
    namespace stream {
        
        enum StreamNum {
            First,
            Second
        };
        
        class DualStreamValve : public Print {
        public:
            DualStreamValve(Stream& stream1, Stream& stream2);

            size_t write(uint8_t) override;
            size_t write(const uint8_t *buffer, size_t size) override;

            void off(StreamNum printNum);
            void on(StreamNum printNum);
            bool substitute(StreamNum printNum, const Stream& stream);

        private:
            const static int ELEMENTS = StreamNum::Second + 1;
            
            struct StoppableStream {
                Stream& stream;
                bool isOn;
            };
            
            DualStreamValve::StoppableStream streams[ELEMENTS];
        };
    }
}
#endif /* DUALSTREAMVALVE_H */

