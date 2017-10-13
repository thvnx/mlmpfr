open Mlmpfr;;
  
let _ =
  let x = mpfr_init2 500 in
  let s = mpfr_set_d x 0.3 MPFR_RNDN in
  let n = mpfr_out_str "out.txt" 10 12 x MPFR_RNDN in
  mpfr_clear x;
  print_endline ((string_of_int n) ^ " " ^ (string_of_int s))
;;
