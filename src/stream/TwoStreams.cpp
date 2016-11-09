#include "TwoStreams.h"
#include <cassert>

TwoStreams::TwoStreams(const Stream& stream1, const Stream& stream2) : 
    stream1(const_cast<Stream&>(stream1)), 
    stream2(const_cast<Stream&>(stream2)) {
}
    
int TwoStreams::available() {
    return stream1.available() && stream2.available();
}
int TwoStreams::read() {
    return stream1.read();
}
int TwoStreams::peek() {
    return stream1.peek();
}
void TwoStreams::flush() {
    stream1.flush();
    stream2.flush();
}
size_t TwoStreams::write(uint8_t byte) {
    size_t size1 = stream1.write(byte);
    size_t size2 = stream2.write(byte);
    //assert(size1 == size2);
    return size1;
}
size_t TwoStreams::write(const uint8_t *buffer, size_t size) {
    size_t size1 = stream1.write(buffer, size);
    size_t size2 = stream2.write(buffer, size);
    //assert(size1 == size2);
    flush();
    return size1;    
}