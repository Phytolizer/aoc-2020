match Array.length Sys.argv with
| 2 -> (
    match Sys.argv.(1) with
    | "day01" -> Day01.run ()
    | x ->
        prerr_endline ("Invalid command '" ^ x ^ "'.");
        exit 1)
| _ ->
    prerr_endline "Expected exactly 1 argument.";
    exit 1
