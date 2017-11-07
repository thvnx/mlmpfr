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

type mpfr_rnd_t = To_Nearest | Toward_Zero | Toward_Plus_Infinity | Toward_Minus_Infinity | Away_From_Zero
type sign = Positive | Negative
type mpfr_prec_t = int
type mpfr_t
type ternary = Correct_Rounding | Greater | Lower
type mpfr_float = mpfr_t * ternary option

exception Base_range of int
exception Precision_range of int

let _ = Callback.register_exception "precision range exception" (Precision_range 0)
let _ = Callback.register_exception "base range exception" (Base_range 0)

let rounding_to_string = function
    _, Some Correct_Rounding -> "Correct"
  | _, Some Lower            -> "Lower"
  | _, Some Greater          -> "Greater"
  | _                        -> "No_Rounding"

external mpfr_prec_min : unit -> int = "caml_mpfr_prec_min"
external mpfr_prec_max : unit -> int = "caml_mpfr_prec_max"
let mpfr_prec_min = mpfr_prec_min ()
let mpfr_prec_max = mpfr_prec_max ()

(* Initialization Functions *)
external set_default_prec : mpfr_prec_t -> unit = "caml_mpfr_set_default_prec"
external get_default_prec : unit -> mpfr_prec_t = "caml_mpfr_get_default_prec"
external get_prec : mpfr_float -> mpfr_prec_t = "caml_mpfr_get_prec"

(* Combined Initilization and Assignment Functions (a functional way) *)
external make_from_mpfr : ?prec:int -> ?rnd:mpfr_rnd_t -> mpfr_float -> mpfr_float = "caml_mpfr_init_set_mpfr"
external make_from_int : ?prec:int -> ?rnd:mpfr_rnd_t -> int -> mpfr_float = "caml_mpfr_init_set_si"
external make_from_float : ?prec:int -> ?rnd:mpfr_rnd_t -> float -> mpfr_float = "caml_mpfr_init_set_d"
external make_from_str : ?prec:int -> ?rnd:mpfr_rnd_t -> ?base:int -> string -> mpfr_float = "caml_mpfr_init_set_str"
external make_nan : ?prec:int -> unit -> mpfr_float = "caml_mpfr_init_set_nan"
external make_inf : ?prec:int -> sign -> mpfr_float = "caml_mpfr_init_set_inf"
external make_zero : ?prec:int -> sign -> mpfr_float = "caml_mpfr_init_set_zero"

(* Conversion Functions *)
external get_float : ?rnd:mpfr_rnd_t -> mpfr_float -> float = "caml_mpfr_get_d"
external get_int : ?rnd:mpfr_rnd_t -> mpfr_float -> int = "caml_mpfr_get_si"
external get_float_2exp : ?rnd:mpfr_rnd_t -> mpfr_float -> float * int = "caml_mpfr_get_d_2exp"
external get_mpfr_2exp : ?rnd:mpfr_rnd_t -> ?prec:int -> mpfr_float -> mpfr_float * int = "caml_mpfr_frexp"
external get_str : ?rnd:mpfr_rnd_t -> ?base:int -> ?size:int -> mpfr_float -> string * string = "caml_mpfr_get_str"
external fits_int_p : ?rnd:mpfr_rnd_t -> mpfr_float -> bool = "caml_mpfr_fits_sint_p"

(* Basic Arithmetic Functions *)
external add : ?rnd:mpfr_rnd_t -> ?prec:mpfr_prec_t -> mpfr_float -> mpfr_float -> mpfr_float = "caml_mpfr_add"
external add_int : ?rnd:mpfr_rnd_t -> ?prec:mpfr_prec_t -> mpfr_float -> int -> mpfr_float = "caml_mpfr_add_si"
external add_float : ?rnd:mpfr_rnd_t -> ?prec:mpfr_prec_t -> mpfr_float -> float -> mpfr_float = "caml_mpfr_add_d"
external sub : ?rnd:mpfr_rnd_t -> ?prec:mpfr_prec_t -> mpfr_float -> mpfr_float -> mpfr_float = "caml_mpfr_sub"
external sub_int : ?rnd:mpfr_rnd_t -> ?prec:mpfr_prec_t -> mpfr_float -> int -> mpfr_float = "caml_mpfr_sub_si"
external int_sub : ?rnd:mpfr_rnd_t -> ?prec:mpfr_prec_t -> int -> mpfr_float -> mpfr_float = "caml_mpfr_si_sub"
external sub_float : ?rnd:mpfr_rnd_t -> ?prec:mpfr_prec_t -> mpfr_float -> float -> mpfr_float = "caml_mpfr_sub_d"
external float_sub : ?rnd:mpfr_rnd_t -> ?prec:mpfr_prec_t -> float -> mpfr_float -> mpfr_float = "caml_mpfr_d_sub"
external mul : ?rnd:mpfr_rnd_t -> ?prec:mpfr_prec_t -> mpfr_float -> mpfr_float -> mpfr_float = "caml_mpfr_mul"
external mul_int : ?rnd:mpfr_rnd_t -> ?prec:mpfr_prec_t -> mpfr_float -> int -> mpfr_float = "caml_mpfr_mul_si"
external mul_float : ?rnd:mpfr_rnd_t -> ?prec:mpfr_prec_t -> mpfr_float -> float -> mpfr_float = "caml_mpfr_mul_d"
external div : ?rnd:mpfr_rnd_t -> ?prec:mpfr_prec_t -> mpfr_float -> mpfr_float -> mpfr_float = "caml_mpfr_div"
external div_int : ?rnd:mpfr_rnd_t -> ?prec:mpfr_prec_t -> mpfr_float -> int -> mpfr_float = "caml_mpfr_div_si"
external int_div : ?rnd:mpfr_rnd_t -> ?prec:mpfr_prec_t -> int -> mpfr_float -> mpfr_float = "caml_mpfr_si_div"
external div_float : ?rnd:mpfr_rnd_t -> ?prec:mpfr_prec_t -> mpfr_float -> float -> mpfr_float = "caml_mpfr_div_d"
external float_div : ?rnd:mpfr_rnd_t -> ?prec:mpfr_prec_t -> float -> mpfr_float -> mpfr_float = "caml_mpfr_d_div"
external sqrt : ?rnd:mpfr_rnd_t -> ?prec:mpfr_prec_t -> mpfr_float -> mpfr_float = "caml_mpfr_sqrt"
external sqrt_int : ?rnd:mpfr_rnd_t -> ?prec:mpfr_prec_t -> int -> mpfr_float = "caml_mpfr_sqrt_ui"
external rec_sqrt : ?rnd:mpfr_rnd_t -> ?prec:mpfr_prec_t -> mpfr_float -> mpfr_float = "caml_mpfr_rec_sqrt"
external cbrt : ?rnd:mpfr_rnd_t -> ?prec:mpfr_prec_t -> mpfr_float -> mpfr_float = "caml_mpfr_cbrt"
external root : ?rnd:mpfr_rnd_t -> ?prec:mpfr_prec_t -> mpfr_float -> int -> mpfr_float = "caml_mpfr_root"
external pow : ?rnd:mpfr_rnd_t -> ?prec:mpfr_prec_t -> mpfr_float -> mpfr_float -> mpfr_float = "caml_mpfr_pow"
external pow_int : ?rnd:mpfr_rnd_t -> ?prec:mpfr_prec_t -> mpfr_float -> int -> mpfr_float = "caml_mpfr_pow_si"
external neg : ?rnd:mpfr_rnd_t -> ?prec:mpfr_prec_t -> mpfr_float -> mpfr_float = "caml_mpfr_neg"
external abs : ?rnd:mpfr_rnd_t -> ?prec:mpfr_prec_t -> mpfr_float -> mpfr_float = "caml_mpfr_abs"
external dim : ?rnd:mpfr_rnd_t -> ?prec:mpfr_prec_t -> mpfr_float -> mpfr_float -> mpfr_float = "caml_mpfr_dim"
external mul_2int : ?rnd:mpfr_rnd_t -> ?prec:mpfr_prec_t -> mpfr_float -> int -> mpfr_float = "caml_mpfr_mul_2si"
external div_2int : ?rnd:mpfr_rnd_t -> ?prec:mpfr_prec_t -> mpfr_float -> int -> mpfr_float = "caml_mpfr_div_2si"

(* Comparison Functions *)
external cmp : mpfr_float -> mpfr_float -> int = "caml_mpfr_cmp"
external cmp_int : mpfr_float -> int -> int = "caml_mpfr_cmp_si"
external cmp_float : mpfr_float -> float -> int = "caml_mpfr_cmp_d"
external cmp_int_2exp : mpfr_float -> int -> int -> int = "caml_mpfr_cmp_si_2exp"
external cmpabs : mpfr_float -> mpfr_float -> int = "caml_mpfr_cmpabs"
external nan_p : mpfr_float -> bool = "caml_mpfr_nan_p"
external inf_p : mpfr_float -> bool = "caml_mpfr_inf_p"
external number_p : mpfr_float -> bool = "caml_mpfr_number_p"
external zero_p : mpfr_float -> bool = "caml_mpfr_zero_p"
external regular_p : mpfr_float -> bool = "caml_mpfr_regular_p"
external sgn : mpfr_float -> sign = "caml_mpfr_sgn"
external greater_p : mpfr_float -> mpfr_float -> bool = "caml_mpfr_greater_p"
external greaterequal_p : mpfr_float -> mpfr_float -> bool = "caml_mpfr_greaterequal_p"
external less_p : mpfr_float -> mpfr_float -> bool = "caml_mpfr_less_p"
external lessequal_p : mpfr_float -> mpfr_float -> bool = "caml_mpfr_lessequal_p"
external equal_p : mpfr_float -> mpfr_float -> bool = "caml_mpfr_equal_p"
external lessgreater_p : mpfr_float -> mpfr_float -> bool = "caml_mpfr_lessgreater_p"
external unordered_p : mpfr_float -> mpfr_float -> bool = "caml_mpfr_unordered_p"

(* Others *)
let get_formatted_str ?rnd:(rnd = To_Nearest) ?base:(base = 10) ?size:(size = 0) x =
  let rec remove_trailing_zeros s =
    match s.[(String.length s) - 1] with
      '0' -> remove_trailing_zeros (String.sub s 0 ((String.length s) -1))
    | _ -> s
  in
  let significand, exponent = get_str ~rnd:rnd ~base:base ~size:size x in
  let neg = if significand.[0] == '-' then true else false in
  let zero = zero_p x in (* if x is zero, print 0e+00 *)
  if zero then
    Printf.sprintf "%s0%c+00" (if neg then "-" else "") (if base > 10 then '@' else 'e')
  else
    if String.contains significand '@' (* nan or inf *)
    then String.lowercase_ascii (String.concat "" (String.split_on_char '@' significand))
    else
      let mantissa = remove_trailing_zeros significand in
      let exponent = (int_of_string exponent) - 1 in
      Printf.sprintf "%s%s%s%c%+03d" (if neg then String.sub mantissa 0 2 else Char.escaped mantissa.[0])
                     (if (neg && (String.length mantissa == 2)) || (neg == false && (String.length mantissa == 1)) then "" else ".")
                     (String.sub mantissa (if neg then 2 else 1) (String.length mantissa - (if neg then 2 else 1)))
                     (if base > 10 then '@' else 'e') exponent
