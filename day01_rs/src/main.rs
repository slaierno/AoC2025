const MAX_DIAL: i64 = 99;
const START_DIAL: i64 = 50;

fn input_to_instructions(input: &String) -> impl Iterator<Item = i64> + '_ {
    input
        .lines()
        .map(|line| (if &line[..1] == "R" { 1 } else { -1 }) * line[1..].parse::<i64>().unwrap())
}

fn inv_pos(pos: i64) -> i64 {
    let inv = MAX_DIAL + 1 - pos;
    if inv == MAX_DIAL + 1 {
        0
    } else {
        inv
    }
}

fn rotate_v1(from: i64, rotation: i64) -> i64 {
    let res = from + rotation;
    if res > MAX_DIAL {
        res % (MAX_DIAL + 1)
    } else if res < 0 {
        (MAX_DIAL + 1 + res) % (MAX_DIAL + 1)
    } else {
        res
    }
}

fn rotate(from: i64, rotation: i64) -> (u64, i64) {
    if rotation < 0 {
        let (num_zeros, pos) = rotate(inv_pos(from), -rotation);
        (num_zeros, inv_pos(pos))
    } else {
        let res = from + rotation;
        if res <= MAX_DIAL {
            (0, res)
        } else {
            ((res / (MAX_DIAL + 1)) as u64, res % (MAX_DIAL + 1))
        }
    }
}

fn part1(instructions: &mut impl Iterator<Item = i64>) -> u64 {
    instructions
        .fold((START_DIAL, 0 as u64), |(pos, zeros), instr| {
            let new_pos = rotate_v1(pos, instr);
            (new_pos, zeros + ((new_pos == 0) as u64))
        })
        .1
}
fn part2(instructions: &mut impl Iterator<Item = i64>) -> u64 {
    instructions
        .fold((START_DIAL, 0 as u64), |(pos, zeros), instr| {
            let (passed_zeros, new_pos) = rotate(pos, instr);
            (new_pos, zeros + passed_zeros as u64)
        })
        .1
}
fn main() {
    // let _input_filename = "test_input";
    let input_filename = "input";
    let input = std::fs::read_to_string(input_filename).expect("Unable to read file");
    // Test input: 3
    // Real input: 1078
    println!("Part 1: {}", part1(&mut input_to_instructions(&input)));

    // Test input: 6
    // Real input: 6412
    println!("Part 2: {}", part2(&mut input_to_instructions(&input)));
}
