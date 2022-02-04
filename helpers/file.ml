let maybe_input_line ic = try Some (input_line ic) with End_of_file -> None

(* Construct the list in the wrong order, then reverse it. *)
(* This allows for tail recursion. *)
let input_lines ic =
  let rec input lines =
    match maybe_input_line ic with
    | Some line -> input (line :: lines)
    | None -> List.rev lines
  in
  input []

let read_all path =
  let ic = open_in path in
  really_input_string ic (in_channel_length ic)

let read_lines path = input_lines (open_in path)
