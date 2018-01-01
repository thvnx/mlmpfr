module M = Mpfr

let _ =
let op = M.make_from_float (~-. 1. /. 3.) in
Printf.printf "%s\n" (M.get_formatted_str (M.cos op))
