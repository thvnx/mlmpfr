type mpfr_rnd_t =
  MPFR_RNDN (* round to nearest (roundTiesToEven in IEEE 754-2008) *)
| MPFR_RNDZ (* round toward zero (roundTowardZero in IEEE 754-2008) *)
| MPFR_RNDU (* round toward plus infinity (roundTowardPositive in IEEE 754-2008) *)
| MPFR_RNDD (* round toward minus infinity (roundTowardNegative in IEEE 754-2008) *)
| MPFR_RNDA (* round away from zero *)

type mpfr_t

type mpfr_exception =
  Underflow | Overflow | DivideByZero | NaN | Inexact | RangeError

external get_mpfr_prec_min_macro : unit -> int = "mpfr_prec_min_ml"
external get_mpfr_prec_max_macro : unit -> int = "mpfr_prec_max_ml"
let mpfr_prec_min = get_mpfr_prec_min_macro ()
let mpfr_prec_max = get_mpfr_prec_max_macro ()


(* 5.1 Initialization Functions *)
external mpfr_init2 : int -> mpfr_t = "mpfr_init2_ml"
external mpfr_inits2 : int -> int -> mpfr_t list = "mpfr_inits2_ml"
external mpfr_clear : mpfr_t -> unit = "mpfr_clear_ml"
let mpfr_clears ops =
  List.iter (fun op -> mpfr_clear op) ops
external mpfr_init : unit -> mpfr_t = "mpfr_init_ml"
external mpfr_inits : int -> mpfr_t list = "mpfr_inits_ml"
external mpfr_set_default_prec : int -> unit = "mpfr_set_default_prec_ml"
external mpfr_get_default_prec : unit -> int = "mpfr_get_default_prec_ml"
external mpfr_set_prec : mpfr_t -> int -> unit = "mpfr_set_prec_ml"
external mpfr_get_prec : mpfr_t -> int = "mpfr_get_prec_ml"


(* 5.2 Assignment Functions *)
external mpfr_set : mpfr_t -> mpfr_t -> mpfr_rnd_t -> int = "mpfr_set_ml"
external mpfr_set_int : mpfr_t -> int -> mpfr_rnd_t -> int = "mpfr_set_si_ml"
external mpfr_set_float : mpfr_t -> float -> mpfr_rnd_t -> int = "mpfr_set_d_ml"
external mpfr_set_str : mpfr_t -> string -> int -> mpfr_rnd_t -> int = "mpfr_set_str_ml"
external mpfr_strtofr : mpfr_t -> string -> int -> mpfr_rnd_t -> int = "mpfr_strtofr_ml"
external mpfr_set_nan : mpfr_t -> unit = "mpfr_set_nan_ml"
external mpfr_set_inf : mpfr_t -> int -> unit = "mpfr_set_inf_ml"
external mpfr_set_zero : mpfr_t -> int -> unit = "mpfr_set_zero_ml"
external mpfr_swap : mpfr_t -> mpfr_t -> unit = "mpfr_swap_ml"


(* 5.3 Combined Initialization and Assignment Functions *)
external mpfr_init_set : mpfr_t -> mpfr_rnd_t -> mpfr_t * int = "mpfr_init_set_ml"
external mpfr_init_set_int : int -> mpfr_rnd_t -> mpfr_t * int = "mpfr_init_set_si_ml"
external mpfr_init_set_float : float -> mpfr_rnd_t -> mpfr_t * int = "mpfr_init_set_d_ml"
external mpfr_init_set_str : string -> int -> mpfr_rnd_t -> mpfr_t * int = "mpfr_init_set_str_ml"


(* 5.4 Conversion Functions *)
external mpfr_get_float : mpfr_t -> mpfr_rnd_t -> float = "mpfr_get_d_ml"
external mpfr_get_int : mpfr_t -> mpfr_rnd_t -> int = "mpfr_get_si_ml"
external mpfr_get_float_2exp : mpfr_t -> mpfr_rnd_t -> float * int = "mpfr_get_d_2exp_ml"
external mpfr_frexp : mpfr_t -> mpfr_t -> mpfr_rnd_t -> int * mpfr_t = "mpfr_frexp_ml"
external mpfr_get_str : int -> int -> mpfr_t -> mpfr_rnd_t -> string * int = "mpfr_get_str_ml"
external mpfr_fits_int_p : mpfr_t -> mpfr_rnd_t -> int = "mpfr_fits_sint_p_ml"


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
