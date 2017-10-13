type rounding_mode =
  MPFR_RNDN (* round to nearest (roundTiesToEven in IEEE 754-2008) *)
| MPFR_RNDZ (* round toward zero (roundTowardZero in IEEE 754-2008) *)
| MPFR_RNDU (* round toward plus infinity (roundTowardPositive in IEEE 754-2008) *)
| MPFR_RNDD (* round toward minus infinity (roundTowardNegative in IEEE 754-2008) *)
| MPFR_RNDA (* round away from zero *)

type mpfr_t

type mpfr_exception =
  Underflow | Overflow | DivideByZero | NaN | Inexact | RangeError


(* 5.1 Initialization Functions *)
external mpfr_init2 : int -> mpfr_t = "mpfr_init2_ml"
external mpfr_inits2 : int -> int -> mpfr_t list = "mpfr_inits2_ml"
external mpfr_clear : mpfr_t -> unit = "mpfr_clear_ml"


(* 5.2 Assignment Functions *)
external mpfr_set_d : mpfr_t -> float -> rounding_mode -> int = "mpfr_set_d_ml"


(* 5.4 Conversion Functions *)
external mpfr_get_str : int -> int -> mpfr_t -> rounding_mode -> string * int = "mpfr_get_str_ml"


(* 5.8 Input and Output Functions *)
let mpfr_out_str chan base n op rnd =
  let significant, exponent = mpfr_get_str base n op rnd in (* do not forget to test special outputs *)
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
