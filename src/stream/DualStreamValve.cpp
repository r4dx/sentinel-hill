#include "DualStreamValve.h"
#include <cassert>

namespace sentinel {
    namespace stream {
        DualStreamValve::DualStreamValve(Stream& stream1, Stream& stream2) : 
            streams({ { stream1, true }, { stream2, true } }) {
        }
        size_t DualStreamValve::write(uint8_t byte) {           
            size_t result = -1;
            
            for (int i = 0; i < ELEMENTS; i++) {
                if (streams[i].isOn) {
                    result = streams[i].stream.write(byte);
                    streams[i].stream.flush();
                }
            }
            return result;
        }
        
        size_t DualStreamValve::write(const uint8_t *buffer, size_t size) {
            size_t result = -1;
            for (int i = 0; i < ELEMENTS; i++) {
                if (streams[i].isOn) {
                    result = streams[i].stream.write(buffer, size);
                    streams[i].stream.flush();
                }
            }
            return result;
        }
        
        void DualStreamValve::off(StreamNum streamNum) {
            streams[streamNum].isOn = false;
        }
        
        void DualStreamValve::on(StreamNum streamNum) {
            streams[streamNum].isOn = true;
        }
        
        bool DualStreamValve::substitute(StreamNum streamNum, const Stream& stream) {
            if (streams[streamNum].isOn)
                return false;
            
            streams[streamNum].stream = stream;
            return true;
        }
    }
}