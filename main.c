#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

long now() {
    struct timespec tp;
    clock_gettime(CLOCK_REALTIME, &tp);     // this only works on linux
    return (tp.tv_sec * 1000) + (tp.tv_nsec / 1000000);
}

void primes(int64_t* numbers, int64_t n) {
    int64_t hn = n / 2;
    for (int64_t i = 1; i < hn; i++) {
        if (numbers[i] == 0) continue;
        int64_t x = numbers[i];
        for (int64_t j = i + x; j < n; j += x) {
            numbers[j] = 0;
        }
    }
}

void benchmark(int64_t n) {
    int64_t length = n / 2;
    int64_t* numbers = (int64_t*)malloc(length * sizeof(int64_t));
    for (int64_t i = 0; i < length; i++) {
        numbers[i] = 2 * i + 1;
    }
    int64_t ms = now();
    primes(numbers, length);
    ms = now() - ms;
    int64_t count = 0;
    for (int64_t i = 0; i < length; i++) {
        if (numbers[i]) count++;
    }
    int64_t* out = (int64_t*)malloc(count * sizeof(int64_t));
    int64_t j = 0;
    for (int64_t i = 0; i < count; i++) {
        if (numbers[i]) out[j++] = numbers[i];
    }
    printf("range: %ld\nprimes: %ld\nms: %ld/sec: %f\n", n, count, ms, ms * 0.001);
}

int main(int argc, char *argv[]) {
    benchmark(100000000);
}
