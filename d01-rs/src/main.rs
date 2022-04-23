fn main() {
    let xs = std::fs::read_to_string("input.txt")
        .unwrap()
        .split('\n')
        .filter(|x| !x.is_empty())
        .map(|x| x.parse::<i32>().unwrap())
        .collect::<Vec<_>>();
    let n = xs.len();
    'first: for i in 0..(n - 1) {
        for j in (i + 1)..n {
            if xs[i] + xs[j] == 2020 {
                println!("{}", xs[i] * xs[j]);
                break 'first;
            }
        }
    }

    'second: for i in 0..(n - 2) {
        for j in (i + 1)..(n - 1) {
            for k in (j + 1)..n {
                if xs[i] + xs[j] + xs[k] == 2020 {
                    println!("{}", xs[i] * xs[j] * xs[k]);
                    break 'second;
                }
            }
        }
    }
}
