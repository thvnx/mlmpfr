open Printf

module M = Mpfr

let _ =
  M.set_default_precision 12345;
  printf "default_precision: %d\n" (M.get_default_precision ());
  let one = M.make_from_int 1 in
  printf "%s\n" (M.rounding_to_string one);
  let x = M.make_from_mpfr one in
  printf "%s\n" (M.rounding_to_string x);
  let x = M.make_from_float 1. in
  printf "%s\n" (M.rounding_to_string x);
  let x = M.make_from_str "1" in
  printf "%s\n" (M.rounding_to_string x);
  let x = M.make_nan () in
  printf "%s\n" (M.rounding_to_string x);
  let x = M.make_inf M.Positive in
  printf "%s\n" (M.rounding_to_string x);
  let x = M.make_zero M.Negative in
  printf "%s\n" (M.rounding_to_string x);
  printf "%d\n" (M.get_precision x);
  Gc.full_major (); (* garbage collector full major *)
