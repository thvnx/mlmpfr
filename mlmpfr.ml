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


(* 5.8 Input and Output Functions *)
external mpfr_out_str : int -> int -> mpfr_t -> rounding_mode -> int = "mpfr_out_str_ml"
