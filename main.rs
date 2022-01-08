const SIZE: usize = std::mem::size_of::<usize>();

fn primes(numbers: &mut Vec<bool>, n: usize) {
    let hn = n / 2;
    for i in 1..hn {
        if !numbers[i] { continue; }
        let x = 2 * i + 1;
        for j in (i + x..hn).step_by(x) {
            numbers[j] = false;
        }
    }
}

fn benchmark(n: usize) {
    let length = n / 2;
    let mut numbers = vec!(true; length);
    let now = std::time::Instant::now();
    primes(&mut numbers, n);
    let end = now.elapsed();
    let mut count = 0;
    for i in 0..length {
        if numbers[i] { count += 1; }
    }
    let mut out = vec!(0; count);
    let mut j = 0;
    for i in 0..length {
        if !numbers[i] { continue; }
        out[j] = 2 * i + 1;
        j += 1;
    }

    println!("range: {}", n);
    println!("count: {}", count);
    println!("{:?}", end);
    println!("size: {} chunck: {}", SIZE, numbers.len() / SIZE);
}

fn main() {
    benchmark(100000000);
}
