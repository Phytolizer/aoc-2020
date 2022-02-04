open Helpers.File

let solve (input : int list) : int =
  let rec check_rest xs =
    let rec check x ys =
      match ys with
      | [] -> None
      | y :: ys -> if x + y = 2020 then Some (x * y) else check x ys
    in
    match xs with
    | [] -> assert false
    | x :: xs -> (
        match check x input with None -> check_rest xs | Some value -> value)
  in
  check_rest input

let run () : unit =
  let input = List.map int_of_string (read_lines "day01/input.txt") in
  print_endline (string_of_int (solve input))
