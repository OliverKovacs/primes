function now() return round(Int64, time() * 1000) end

function primes!(numbers)
    n = length(numbers)
    hn = n / 2
    i = 1
    while (i += 1) < hn
        if numbers[i] == 0
            continue
        end
        x = numbers[i]
        j = i
        while (j += x) <= n
            numbers[j] = 0
        end
    end
end

function benchmark(n)
    numbers = collect(1:2:n)
    ms = now()
    primes!(numbers)
    ms = now() - ms
    out = numbers[numbers .!= 0]
    println("range: ", length(numbers))
    println("primes: ", length(out))
    println("ms: ", ms, "/sec: ", ms / 1000)
end

benchmark(100000000)
