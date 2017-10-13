open Mlmpfr
open Printf

let init2 prec =
  let m = mpfr_init2 prec in
  mpfr_clear m

let inits2 prec n =
  let m = mpfr_inits2 prec n in
  mpfr_clears m

let init _ =
  let m = mpfr_init () in
  mpfr_clear m

let inits n =
  let m = mpfr_inits n in
  mpfr_clears m

let set_default_prec n =
  mpfr_set_default_prec n

let get_default_prec _ =
  mpfr_get_default_prec ()

let set_prec op prec =
  mpfr_set_prec op prec

let get_prec op =
  mpfr_get_prec op
  
let _ =
  init2 2;
  inits2 2 2;
  init ();
  inits 2;
  let p = 64 in
  set_default_prec p;
  printf "%d\n" (if p == (get_default_prec ()) then 1 else 0);
  let op = mpfr_init () in
  set_prec op 1234;
  printf "%d\n" (get_prec op);
  mpfr_clear op
