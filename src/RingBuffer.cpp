#include "RingBuffer.h"
#include "globals.h"


template <typename T, std::size_t N>
RingBuffer<T, N>::RingBuffer() {
    readings.fill(T{});  
}

template <typename T, std::size_t N>
void RingBuffer<T,N>::recordReading(const T& reading) {
    head = (head + 1) % N;
    readings[head] = reading;
    if (count < N) {
        ++count;
    };
}

template <typename T, std::size_t N>
void RingBuffer<T, N>::copyBuffer(std::array<T, N>& out, int& headIndex) const {
    for (std::size_t i = 0; i < count; ++i) {
        std::size_t index = (head + i + N - count) % N;
        out[i] = readings[index];
    }
    headIndex = (head + N - 1) % N;
}

template class RingBuffer<IRreading, 50>;