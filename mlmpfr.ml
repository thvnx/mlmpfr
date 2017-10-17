type mpfr_rnd_t =
  MPFR_RNDN (* round to nearest (roundTiesToEven in IEEE 754-2008) *)
| MPFR_RNDZ (* round toward zero (roundTowardZero in IEEE 754-2008) *)
| MPFR_RNDU (* round toward plus infinity (roundTowardPositive in IEEE 754-2008) *)
| MPFR_RNDD (* round toward minus infinity (roundTowardNegative in IEEE 754-2008) *)
| MPFR_RNDA (* round away from zero *)

type mpfr_t

type mpfr_exception =
  Underflow | Overflow | DivideByZero | NaN | Inexact | RangeError

external get_mpfr_prec_min_macro : unit -> int = "caml_mpfr_prec_min"
external get_mpfr_prec_max_macro : unit -> int = "caml_mpfr_prec_max"
let mpfr_prec_min = get_mpfr_prec_min_macro ()
let mpfr_prec_max = get_mpfr_prec_max_macro ()


(* 5.1 Initialization Functions *)
external mpfr_init2 : int -> mpfr_t = "caml_mpfr_init2"
external mpfr_inits2 : int -> int -> mpfr_t list = "caml_mpfr_inits2"
external mpfr_clear : mpfr_t -> unit = "caml_mpfr_clear"
let mpfr_clears ops =
  List.iter (fun op -> mpfr_clear op) ops
external mpfr_init : unit -> mpfr_t = "caml_mpfr_init"
external mpfr_inits : int -> mpfr_t list = "caml_mpfr_inits"
external mpfr_set_default_prec : int -> unit = "caml_mpfr_set_default_prec"
external mpfr_get_default_prec : unit -> int = "caml_mpfr_get_default_prec"
external mpfr_set_prec : mpfr_t -> int -> unit = "caml_mpfr_set_prec"
external mpfr_get_prec : mpfr_t -> int = "caml_mpfr_get_prec"


(* 5.2 Assignment Functions *)
external mpfr_set : mpfr_t -> mpfr_t -> mpfr_rnd_t -> int = "caml_mpfr_set"
external mpfr_set_int : mpfr_t -> int -> mpfr_rnd_t -> int = "caml_mpfr_set_si"
external mpfr_set_float : mpfr_t -> float -> mpfr_rnd_t -> int = "caml_mpfr_set_d"
external mpfr_set_str : mpfr_t -> string -> int -> mpfr_rnd_t -> int = "caml_mpfr_set_str"
external mpfr_strtofr : mpfr_t -> string -> int -> mpfr_rnd_t -> int = "caml_mpfr_strtofr"
external mpfr_set_nan : mpfr_t -> unit = "caml_mpfr_set_nan"
external mpfr_set_inf : mpfr_t -> int -> unit = "caml_mpfr_set_inf"
external mpfr_set_zero : mpfr_t -> int -> unit = "caml_mpfr_set_zero"
external mpfr_swap : mpfr_t -> mpfr_t -> unit = "caml_mpfr_swap"


(* 5.3 Combined Initialization and Assignment Functions *)
external mpfr_init_set : mpfr_t -> mpfr_rnd_t -> mpfr_t * int = "caml_mpfr_init_set"
external mpfr_init_set_int : int -> mpfr_rnd_t -> mpfr_t * int = "caml_mpfr_init_set_si"
external mpfr_init_set_float : float -> mpfr_rnd_t -> mpfr_t * int = "caml_mpfr_init_set_d"
external mpfr_init_set_str : string -> int -> mpfr_rnd_t -> mpfr_t * int = "caml_mpfr_init_set_str"


(* 5.4 Conversion Functions *)
external mpfr_get_float : mpfr_t -> mpfr_rnd_t -> float = "caml_mpfr_get_d"
external mpfr_get_int : mpfr_t -> mpfr_rnd_t -> int = "caml_mpfr_get_si"
external mpfr_get_float_2exp : mpfr_t -> mpfr_rnd_t -> float * int = "caml_mpfr_get_d_2exp"
external mpfr_frexp : int -> mpfr_t -> mpfr_rnd_t -> int * mpfr_t = "caml_mpfr_frexp"
external mpfr_get_str : int -> int -> mpfr_t -> mpfr_rnd_t -> string * int = "caml_mpfr_get_str"
external mpfr_fits_int_p : mpfr_t -> mpfr_rnd_t -> int = "caml_mpfr_fits_sint_p"


(* 5.5 Basic Arithmetic Functions *)
external mpfr_add : int -> mpfr_t -> mpfr_t -> mpfr_rnd_t -> mpfr_t * int = "caml_mpfr_add"
external mpfr_add_int : int -> mpfr_t -> int -> mpfr_rnd_t -> mpfr_t * int = "caml_mpfr_add_si"
external mpfr_add_float : int -> mpfr_t -> float -> mpfr_rnd_t -> mpfr_t * int = "caml_mpfr_add_d"
external mpfr_sub : int -> mpfr_t -> mpfr_t -> mpfr_rnd_t -> mpfr_t * int = "caml_mpfr_sub"
external mpfr_int_sub : int -> int -> mpfr_t -> mpfr_rnd_t -> mpfr_t * int = "caml_mpfr_si_sub"
external mpfr_sub_int : int -> mpfr_t -> int -> mpfr_rnd_t -> mpfr_t * int = "caml_mpfr_sub_si"
external mpfr_float_sub : int -> float -> mpfr_t -> mpfr_rnd_t -> mpfr_t * int = "caml_mpfr_d_sub"
external mpfr_sub_float : int -> mpfr_t -> float -> mpfr_rnd_t -> mpfr_t * int = "caml_mpfr_sub_d"
external mpfr_mul : int -> mpfr_t -> mpfr_t -> mpfr_rnd_t -> mpfr_t * int = "caml_mpfr_mul"
external mpfr_mul_int : int -> mpfr_t -> int -> mpfr_rnd_t -> mpfr_t * int = "caml_mpfr_mul_si"
external mpfr_mul_float : int -> mpfr_t -> float -> mpfr_rnd_t -> mpfr_t * int = "caml_mpfr_mul_d"
external mpfr_sqr : int -> mpfr_t -> mpfr_rnd_t -> mpfr_t * int = "caml_mpfr_sqr"
external mpfr_div : int -> mpfr_t -> mpfr_t -> mpfr_rnd_t -> mpfr_t * int = "caml_mpfr_div"
external mpfr_int_div : int -> int -> mpfr_t -> mpfr_rnd_t -> mpfr_t * int = "caml_mpfr_si_div"
external mpfr_div_int : int -> mpfr_t -> int -> mpfr_rnd_t -> mpfr_t * int = "caml_mpfr_div_si"
external mpfr_float_div : int -> float -> mpfr_t -> mpfr_rnd_t -> mpfr_t * int = "caml_mpfr_d_div"
external mpfr_div_float : int -> mpfr_t -> float -> mpfr_rnd_t -> mpfr_t * int = "caml_mpfr_div_d"
external mpfr_sqrt : int -> mpfr_t -> mpfr_rnd_t -> mpfr_t * int = "caml_mpfr_sqrt"
external mpfr_sqrt_int : int -> int -> mpfr_rnd_t -> mpfr_t * int = "caml_mpfr_sqrt_ui"
external mpfr_rec_sqrt : int -> mpfr_t -> mpfr_rnd_t -> mpfr_t * int = "caml_mpfr_rec_sqrt"
external mpfr_cbrt : int -> mpfr_t -> mpfr_rnd_t -> mpfr_t * int = "caml_mpfr_cbrt"
external mpfr_root : int -> mpfr_t -> int -> mpfr_rnd_t -> mpfr_t * int = "caml_mpfr_root"
external mpfr_pow : int -> mpfr_t -> mpfr_t -> mpfr_rnd_t -> mpfr_t * int = "caml_mpfr_pow"
external mpfr_pow_int : int -> mpfr_t -> int -> mpfr_rnd_t -> mpfr_t * int = "caml_mpfr_pow_si"
external mpfr_neg : int -> mpfr_t -> mpfr_rnd_t -> mpfr_t * int = "caml_mpfr_neg"
external mpfr_abs : int -> mpfr_t -> mpfr_rnd_t -> mpfr_t * int = "caml_mpfr_abs"
external mpfr_dim : int -> mpfr_t -> mpfr_t -> mpfr_rnd_t -> mpfr_t * int = "caml_mpfr_dim"
external mpfr_mul_2int : int -> mpfr_t -> int -> mpfr_rnd_t -> mpfr_t * int = "caml_mpfr_mul_2si"
external mpfr_div_2int : int -> mpfr_t -> int -> mpfr_rnd_t -> mpfr_t * int = "caml_mpfr_div_2si"


(* 5.6 Comparison Functions *)
external mpfr_cmp : mpfr_t -> mpfr_t -> int = "caml_mpfr_cmp"
external mpfr_cmp_int : mpfr_t -> int -> int = "caml_mpfr_cmp_si"
external mpfr_cmp_float : mpfr_t -> float -> int = "caml_mpfr_cmp_d"
external mpfr_cmp_int_2exp : mpfr_t -> int -> int -> int = "caml_mpfr_cmp_si_2exp"
external mpfr_cmpabs : mpfr_t -> mpfr_t -> int = "caml_mpfr_cmpabs"
external mpfr_nan_p : mpfr_t -> int = "caml_mpfr_nan_p"
external mpfr_inf_p : mpfr_t -> int = "caml_mpfr_inf_p"
external mpfr_number_p : mpfr_t -> int = "caml_mpfr_number_p"
external mpfr_zero_p : mpfr_t -> int = "caml_mpfr_zero_p"
external mpfr_regular_p : mpfr_t -> int = "caml_mpfr_regular_p"
external mpfr_sgn : mpfr_t -> int = "caml_mpfr_sgn"
external mpfr_greater_p : mpfr_t -> mpfr_t -> int = "caml_mpfr_greater_p"
external mpfr_greaterequal_p : mpfr_t -> mpfr_t -> int = "caml_mpfr_greaterequal_p"
external mpfr_less_p : mpfr_t -> mpfr_t -> int = "caml_mpfr_less_p"
external mpfr_lessequal_p : mpfr_t -> mpfr_t -> int = "caml_mpfr_lessequal_p"
external mpfr_equal_p : mpfr_t -> mpfr_t -> int = "caml_mpfr_equal_p"
external mpfr_lessgreater_p : mpfr_t -> mpfr_t -> int = "caml_mpfr_lessgreater_p"
external mpfr_unordered_p : mpfr_t -> mpfr_t -> int = "caml_mpfr_unordered_p"


(* 5.8 Input and Output Functions *)
let mpfr_out_str chan base n op rnd =
  let significant, exponent = mpfr_get_str base n op rnd in
  if String.contains significant '@'
  then
    begin
      Printf.fprintf chan "%s" significant;
      String.length significant
    end
  else
    begin
      if significant.[0] == '-'
      then
        Printf.fprintf chan "-%c.%s%c%d"
                       significant.[1]
                       (String.sub significant 2 (String.length significant - 2))
                       (if base > 10 then '@' else 'e')
                       (exponent - 1)
      else
        Printf.fprintf chan "%c.%s%c%d"
                       significant.[0]
                       (String.sub significant 1 (String.length significant - 1))
                       (if base > 10 then '@' else 'e')
                       (exponent - 1);
      (String.length significant) + (String.length (string_of_int (exponent -1))) + 2
    end
