function primes(numbers: number[]): void {
    const n: number = numbers.length;
    const hn: number = n / 2;
    for (let i: number = 1; i < hn; i++) {
        if (!numbers[i]) continue;
        const x: number = numbers[i];
        for (let j: number = i + x; j < n; j += x) {
            numbers[j] = 0;
        }
    }
}

function benchmark(n: number): void {
    const numbers: number[] = Array.from({ length: n / 2 }, (_, i) => 2 * i + 1);
    let ms: number = Date.now();
    primes(numbers);
    ms = Date.now() - ms;
    const out: number[] = [];
    for (let i: number = 0; i < n; i++) { 
        if (numbers[i]) out.push(numbers[i]);
    }
    console.log(`range: ${n}`);
    console.log(`primes: ${out.length}`);
    console.log(`ms: ${ms}/sec: ${ms / 1000}`);
};

benchmark(100000000);
