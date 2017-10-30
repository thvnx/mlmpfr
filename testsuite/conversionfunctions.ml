open Printf
module M = Mpfr

let _ =
  let x = M.make_from_float (1. /. 3.) in
  printf "%e\n" (M.get_float x);
  printf "%d\n" (M.get_int x);
  let m, n = M.get_float_2exp x in
  printf "%e %d\n" m n;
  let _, n = M.get_mpfr_2exp x in
  printf "%d\n" n;
  let m, n = M.get_str x in
  printf "%s %s\n" m n;
  printf "%s\n" (M.get_formatted_str x);
  printf "%b\n" (M.fits_int_p x)
