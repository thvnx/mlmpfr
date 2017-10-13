open Mlmpfr
open Printf

let t_init2 _ =
  let x = mpfr_init2 500 in
  let s = mpfr_set_d x 0.3 MPFR_RNDN in
  if s <> 0 then printf "Fail while set_d\n";
  let n = mpfr_out_str "t_init2.txt" 10 100 x MPFR_RNDN in
  mpfr_clear x;
  printf "Write %d characters\n" n
;;

let t_inits2 _ =
  let x = mpfr_inits2 500 5 in
  printf "Created list size: %d\n" (List.length x);
  List.iteri (fun i j ->
      let _ = mpfr_set_d j ((float_of_int i) *. 0.1) MPFR_RNDN in
      let _ = mpfr_out_str "t_inits2.txt" 10 100 j MPFR_RNDN in
      let c = open_out_gen [Open_append] 0o640 "t_inits2.txt" in
      fprintf c "\n";
      close_out c
    ) x
;;

let _ =
  t_init2 ();
  t_inits2 ()
