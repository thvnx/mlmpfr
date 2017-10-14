open Mlmpfr
open Printf

let set n m rnd =
  mpfr_set n m rnd

let set_int n i rnd =
  mpfr_set_int n i rnd
   
let set_float n d rnd =
  mpfr_set_float n d rnd

let set_str n s base rnd =
  mpfr_set_str n s base rnd

let strtofr n s base rnd =
  mpfr_strtofr n s base rnd

let set_nan n =
  mpfr_set_nan n

let set_inf n s =
  mpfr_set_inf n s

let set_zero n s =
  mpfr_set_zero n s

let swap n m =
  mpfr_swap n m

let _ =
  let m = mpfr_init2 53 in
  let r = set m m MPFR_RNDN in
  printf "%d\n" r;
  let r = set_int m 1 MPFR_RNDN in
  printf "%d\n" r;
  let r = set_float m 1. MPFR_RNDN in
  printf "%d\n" r;
  let r = set_str m "1" 10 MPFR_RNDN in
  printf "%d\n" r;
  let r = strtofr m "1" 10 MPFR_RNDN in
  printf "%d\n" r;
  set_nan m;
  set_inf m 0;
  set_zero m 0;
  swap m m;
  
  mpfr_clear m
