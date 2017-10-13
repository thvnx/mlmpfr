open Mlmpfr

let init2 prec =
  let m = mpfr_init2 prec in
  mpfr_clear m

let inits2 prec n =
  let m = mpfr_inits2 prec n in
  mpfr_clears m

let _ =
  init2 2;
  inits2 2 2
