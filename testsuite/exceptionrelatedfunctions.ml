(* This file is part of mlmpfr.

  mlmpfr is free software: you can redistribute it and/or modify it
  under the terms of the GNU Lesser General Public License as
  published by the Free Software Foundation, either version 3 of the
  License, or (at your option) any later version.

  mlmpfr is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with mlmpfr. If not, see
  <http://www.gnu.org/licenses/>. *)

open Printf
module M = Mpfr

let flags _ =
  printf "%b %b %b %b %b %b\n" (M.underflow_p ()) (M.overflow_p ()) (M.divby0_p ())
         (M.nanflag_p ()) (M.inexflag_p ()) (M.erangeflag_p ())

let all op em1 em2 =
  printf "%d %d\n" (M.get_emin ()) (M.get_emax ());
  (M.set_emin em1); (M.set_emax em2);
  printf "%d %d\n" (M.get_emin ()) (M.get_emax ());
  printf "%d %d %d %d\n" (M.get_emin_min ()) (M.get_emin_max ()) (M.get_emax_min ()) (M.get_emax_max ());
  printf "%s\n" (M.get_formatted_str (M.check_range op));
  printf "%s\n" (M.get_formatted_str (M.subnormalize op));
  flags ();
  M.set_underflow ();  M.set_overflow ();
  M.set_divby0 ();  M.set_nanflag ();
  M.set_inexflag ();  M.set_erangeflag ();
  flags ();
  M.clear_underflow ();  M.clear_overflow ();
  M.clear_divby0 ();  M.clear_nanflag ();
  M.clear_inexflag ();  M.clear_erangeflag ();
  flags ()

let _ =
  all (M.make_from_float (1. /. 3.)) (-123) 123; printf "\n";
  Gc.full_major (); (* garbage collector full major *)
