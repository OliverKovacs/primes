#include <iostream>
#include <cmath>
#include <cstdlib>
#include <cstdint>
#include <chrono>

using chunk = uint64_t;
size_t const SIZE = 8 * sizeof(chunk);

auto now() -> int64_t;
void primes(chunk* numbers, uint64_t n);
void benchmark(uint64_t n);

auto main(int argc, char *argv[]) -> int {
    benchmark(100000000);
}

auto now() -> int64_t {
    return std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::system_clock::now().time_since_epoch()
    ).count();
}

class BitArray {
    public:
        chunk* array;
        uint64_t length;

        explicit BitArray(uint64_t length)
            : array(static_cast<chunk*>(malloc((length / SIZE) * sizeof(chunk))))
            , length(ceil(static_cast<double>(length) / static_cast<double>(SIZE)) * SIZE)
        {
            chunk fill = -1;
            for (size_t i = 0; i < length / SIZE + 1; i++) {
                this->array[i] = fill;
            }
        }

        auto getBit(uint64_t index) -> bool {
            return ((this->array[index / SIZE]) & (static_cast<chunk>(1) << (index % SIZE))) != 0;
        }

        void clearBit(uint64_t index) {
            this->array[index / SIZE] &= ~(static_cast<chunk>(1) << (index % SIZE)); 
        }
};

void primes(chunk* numbers, uint64_t n) {
    uint64_t hn = n / 2;
    for (uint64_t i = 1; i < hn; i++) {
        if (!static_cast<bool>(numbers[i / SIZE] & (static_cast<chunk>(1) << (i % SIZE)))) continue;
        uint64_t x = 2 * i + 1;
        for (uint64_t j = i + x; j < hn; j += x) {
            numbers[j / SIZE] &= ~(static_cast<chunk>(1) << (j % SIZE));
        }
    }
}

void benchmark(uint64_t n) {
    uint64_t length = n / 2;
    BitArray numbers(n);
    int64_t ms = now();
    primes(numbers.array, n);
    ms = now() - ms;
    uint64_t count = 0;
    for (size_t i = 0; i < length; i++) {
        if (numbers.getBit(i)) count++;
    }
    auto *out = static_cast<uint64_t*>(malloc(count * sizeof(uint64_t)));
    uint64_t j = 0;
    for (uint64_t i = 0; i < length; i++) {
        if (numbers.getBit(i)) out[j++] = 2 * i + 1;
    }
    std::cout << "range: " << n << std::endl;
    std::cout << "primes: " << count << std::endl;
    std::cout << "ms: " << ms << "/sec: " << ms * 0.001 << std::endl;
    std::cout << "size: " << SIZE << " chunks: " << numbers.length / SIZE << std::endl;
}
