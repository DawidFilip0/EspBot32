#ifndef RINGBUFFER_H
#define RINGBUFFER_H

#include <globals.h>
#include <array>

template <typename T, std::size_t N>
class RingBuffer {
public:
    RingBuffer();

    void recordReading(const T& value);
    void copyBuffer(std::array<T, N>& out) const;

private:
    std::array<T, N> readings;
    std::size_t head = 0;
    std::size_t count = 0;
};

#endif
