import time

def now():
    return round(time.time() * 1000)

def primes(numbers):
    n = len(numbers)
    hn = n / 2
    i = 1
    while (i < hn):
        if (not numbers[i]):
            i += 1 
            continue
        x = numbers[i]
        j = i + x
        while (j < n):
            numbers[j] = 0
            j += x
        i += 1

def benchmark(n):
    numbers = list(range(1, n, 2))
    ms = now()
    primes(numbers)
    ms = now() - ms
    out = []
    i = 0
    while (i < n / 2):
        if (numbers[i]): out.append(numbers[i])
        i += 1
    print("range: {}".format(n))
    print("primes: {}".format(len(out)))
    print("ms: {}/sec: {}".format(ms, ms / 1000))

benchmark(100000000)
