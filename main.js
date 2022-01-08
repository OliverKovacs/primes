const primes = numbers => {
    const n = numbers.length;
    const hn = n / 2;
    for (let i = 1; i < hn; i++) {
        if (!numbers[i]) continue;
        const x = numbers[i];
        for (let j = i + x; j < n; j += x) {
            numbers[j] = 0;
        }
    }
}

const benchmark = n => {
    const numbers = Array.from({ length: n / 2 }, (_, i) => 2 * i + 1);
    let ms = Date.now();
    primes(numbers);
    ms = Date.now() - ms;
    const out = [];
    for (let i = 0; i < n; i++) { 
        if (numbers[i]) out.push(numbers[i]);
    }
    console.log(`range: ${n}`);
    console.log(`primes: ${out.length}`);
    console.log(`ms: ${ms}/sec: ${ms / 1000}`);
};

benchmark(100000000);
