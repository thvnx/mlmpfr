open Mlmpfr
open Printf

let t_init2 _ =
  let x = mpfr_init2 500 in
  let s = mpfr_set_d x 0.3 MPFR_RNDN in
  if s <> 0
  then printf "Fail while set_d\n";
  let ch = open_out "t_init2.txt" in
  let n = mpfr_out_str ch 10 12 x MPFR_RNDN in
  mpfr_clear x;
  close_out ch;
  printf "Write %d characters\n" n
;;

let t_inits2 _ =
  let x = mpfr_inits2 500 5 in
  printf "Created list size: %d\n" (List.length x);
  let ch = open_out  "t_inits2.txt" in
  List.iteri (fun i j ->
      let _ = mpfr_set_d j ((float_of_int i) *. 0.1) MPFR_RNDN in
      let _ = mpfr_out_str ch 10 0 j MPFR_RNDN in
      fprintf ch "\n";
    ) x;
  close_out ch
;;

let _ =
  t_init2 ();
  t_inits2 ()
