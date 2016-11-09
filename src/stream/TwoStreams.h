#ifndef TWOSTREAMS_H
#define TWOSTREAMS_H

#include <Stream.h>

class TwoStreams : public Stream {
public:
    TwoStreams(const Stream& stream1, const Stream& stream2);
    
    int available();
    int read();
    int peek();
    void flush();
    size_t write(uint8_t);
    size_t write(const uint8_t *buffer, size_t size);
    
private:
    Stream& stream1;
    Stream& stream2;
};

#endif /* TWOSTREAMS_H */

