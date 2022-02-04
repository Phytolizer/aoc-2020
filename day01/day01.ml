open Helpers.File

let run () : unit =
  let input = List.map int_of_string (read_lines "day01/input.txt") in
  List.iter (fun line -> Printf.printf "%d\n" line) input
