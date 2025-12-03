use itertools::Itertools;

fn best_n_digits_value(line: Vec<u64>, n_of_digits: usize) -> u64 {
    // best_digits index is also the 10-exponent
    // i.e. best_digits[2] == 3 ---> 2*10^3
    let mut best_digits = vec![0u64; n_of_digits];
    for (idx, &n) in line.iter().enumerate() {
        // From result most significant possible digit checks if current digit is better
        // than the currently stored one. If so, fill any less significant digit with 0
        // and let them be replaced in the next iteration with the following digits of the line
        for digit in (0..n_of_digits).rev() {
            if idx >= n_of_digits - digit - 1 // Nth result digit can't be any of the first (N-<max result digits>-1) line digits
                && idx <= line.len() - digit - 1 // Nth result digit can't be any of the last N-1 line digits
                && n > best_digits[digit]
            {
                best_digits[digit] = n;
                best_digits[0..digit].fill(0);
                break;
            }
        }
    }
    best_digits
        .iter()
        .enumerate()
        .map(|(idx, &digit)| digit * 10u64.pow(idx as u32))
        .sum()
}

fn sum_of_best(input: &String, n_of_digits: usize) -> u64 {
    input
        .lines()
        .map(|line| {
            line.chars()
                .map(|c| c.to_digit(10).unwrap() as u64)
                .collect_vec()
        })
        .map(|line| best_n_digits_value(line, n_of_digits))
        .sum()
}

fn main() {
    // let input_filename = "test_input";
    let input_filename = "input";
    let input = std::fs::read_to_string(input_filename).expect("Unable to read file");

    // Test input: 357
    // Real input: 17554
    println!("Part 1: {}", sum_of_best(&input, 2));

    // Test input: 3121910778619
    // Real input: 175053592950232
    println!("Part 2: {}", sum_of_best(&input, 12));
}
