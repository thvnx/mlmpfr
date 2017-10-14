open Mlmpfr
open Printf
   
let set_float n d rnd =
  mpfr_set_float n d rnd

let _ =
  let m = mpfr_init2 53 in
  let r = set_float m 1. MPFR_RNDN in
  printf "%d\n" r;
  mpfr_clear m
