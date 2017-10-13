open Mlmpfr
open Printf
   
let set_d n d rnd =
  mpfr_set_d n d rnd

let _ =
  let m = mpfr_init2 53 in
  let r = set_d m 1. MPFR_RNDN in
  printf "%d\n" r;
  mpfr_clear m
