use itertools::Itertools;

fn input_to_ranges(input: &str) -> impl Iterator<Item = (u64, u64)> + '_ {
    input.split(',').map(|s| {
        s.split('-')
            .map(|s| s.parse::<u64>().unwrap())
            .collect_tuple::<(u64, u64)>()
            .unwrap()
    })
}

fn is_invalid_id_part1(id: u64) -> bool {
    id > 0 && {
        let digits = id.ilog10() + 1;
        digits % 2 == 0 && {
            let half_pow = 10_u64.pow(digits / 2);
            id / half_pow == id % half_pow
        }
    }
}

fn is_invalid_id_part2(id: u64) -> bool {
    id > 0 && {
        let digits = id.ilog10() + 1;
        (1..=(digits / 2))
            .filter(|slot_size| digits % slot_size == 0)
            .map(|slot_size| {
                let left_slot_pow = 10_u64.pow(slot_size);
                let right_slot_pow = 10_u64.pow(digits - slot_size);
                (left_slot_pow, right_slot_pow)
            })
            .any(|(lsp, rsp)| id / lsp == id % rsp)
    }
}

fn sum_of_invalids(input: &str, invalid_fn: fn(u64) -> bool) -> u64 {
    input_to_ranges(input)
        .map(|(min, max)| (min..max).filter(|id| invalid_fn(*id)).sum::<u64>())
        .sum()
}

fn main() {
    // let input_filename = "test_input";
    let input_filename = "input";
    let input = std::fs::read_to_string(input_filename).expect("Unable to read file");

    // Test input: 1227775574
    // Real input: 38158151648
    println!("Part 1: {}", sum_of_invalids(&input, is_invalid_id_part1));

    // Test input: 4174379265
    // Real input: 45283684555
    println!("Part 2: {}", sum_of_invalids(&input, is_invalid_id_part2));
}
