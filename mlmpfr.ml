type mpfr_rnd_t =
  MPFR_RNDN (* round to nearest (roundTiesToEven in IEEE 754-2008) *)
| MPFR_RNDZ (* round toward zero (roundTowardZero in IEEE 754-2008) *)
| MPFR_RNDU (* round toward plus infinity (roundTowardPositive in IEEE 754-2008) *)
| MPFR_RNDD (* round toward minus infinity (roundTowardNegative in IEEE 754-2008) *)
| MPFR_RNDA (* round away from zero *)

type mpfr_t
type ternary_value = int

type mpfr_with_ternary_value = { rop : mpfr_t; tv : ternary_value }
type mpfr_tv = mpfr_with_ternary_value

type mpfr_exp_t = int
type mpfr_prec_t = int
type base = int
type size = int

type float_2exp = { n : float; e : mpfr_exp_t }
type mpfr_2exp = { n : mpfr_t; e : mpfr_exp_t }
type sig_exp = { significand : string; exponent : mpfr_exp_t }

type mpfr_exception =
  Underflow | Overflow | DivideByZero | NaN | Inexact | RangeError

external get_mpfr_prec_min_macro : unit -> int = "caml_mpfr_prec_min"
external get_mpfr_prec_max_macro : unit -> int = "caml_mpfr_prec_max"
let mpfr_prec_min = get_mpfr_prec_min_macro ()
let mpfr_prec_max = get_mpfr_prec_max_macro ()


(* 5.1 Initialization Functions *)
external mpfr_init2 : mpfr_prec_t -> mpfr_t = "caml_mpfr_init2"
external mpfr_inits2 : int -> mpfr_prec_t -> mpfr_t list = "caml_mpfr_inits2"
external mpfr_clear : mpfr_t -> unit = "caml_mpfr_clear"
let mpfr_clears ops =
  List.iter (fun op -> mpfr_clear op) ops
external mpfr_init : unit -> mpfr_t = "caml_mpfr_init"
external mpfr_inits : int -> mpfr_t list = "caml_mpfr_inits"
external mpfr_set_default_prec : mpfr_prec_t -> unit = "caml_mpfr_set_default_prec"
external mpfr_get_default_prec : unit -> mpfr_prec_t = "caml_mpfr_get_default_prec"
external mpfr_set_prec : mpfr_t -> mpfr_prec_t -> unit = "caml_mpfr_set_prec"
external mpfr_get_prec : mpfr_t -> mpfr_prec_t = "caml_mpfr_get_prec"


(* 5.2 Assignment Functions *)
external mpfr_set : mpfr_t -> mpfr_t -> mpfr_rnd_t -> ternary_value = "caml_mpfr_set"
external mpfr_set_int : mpfr_t -> int -> mpfr_rnd_t -> ternary_value = "caml_mpfr_set_si"
external mpfr_set_float : mpfr_t -> float -> mpfr_rnd_t -> ternary_value = "caml_mpfr_set_d"
external mpfr_set_str : mpfr_t -> string -> int -> mpfr_rnd_t -> int = "caml_mpfr_set_str"
external mpfr_strtofr : mpfr_t -> string -> int -> mpfr_rnd_t -> ternary_value = "caml_mpfr_strtofr"
external mpfr_set_nan : mpfr_t -> unit = "caml_mpfr_set_nan"
external mpfr_set_inf : mpfr_t -> int -> unit = "caml_mpfr_set_inf"
external mpfr_set_zero : mpfr_t -> int -> unit = "caml_mpfr_set_zero"
external mpfr_swap : mpfr_t -> mpfr_t -> unit = "caml_mpfr_swap"


(* 5.3 Combined Initialization and Assignment Functions *)
external mpfr_init_set : mpfr_t -> mpfr_rnd_t -> mpfr_tv = "caml_mpfr_init_set"
external mpfr_init_set_int : int -> mpfr_rnd_t -> mpfr_tv = "caml_mpfr_init_set_si"
external mpfr_init_set_float : float -> mpfr_rnd_t -> mpfr_tv = "caml_mpfr_init_set_d"
external mpfr_init_set_str : string -> int -> mpfr_rnd_t -> mpfr_tv = "caml_mpfr_init_set_str"


(* 5.4 Conversion Functions *)
external mpfr_get_float : mpfr_t -> mpfr_rnd_t -> float = "caml_mpfr_get_d"
external mpfr_get_int : mpfr_t -> mpfr_rnd_t -> int = "caml_mpfr_get_si"
external mpfr_get_float_2exp : mpfr_t -> mpfr_rnd_t -> float_2exp = "caml_mpfr_get_d_2exp"
external mpfr_frexp : mpfr_prec_t -> mpfr_t -> mpfr_rnd_t -> mpfr_2exp = "caml_mpfr_frexp"
external mpfr_get_str : base -> size -> mpfr_t -> mpfr_rnd_t -> sig_exp = "caml_mpfr_get_str"
external mpfr_fits_int_p : mpfr_t -> mpfr_rnd_t -> bool = "caml_mpfr_fits_sint_p"


(* 5.5 Basic Arithmetic Functions *)
external mpfr_add : mpfr_prec_t -> mpfr_t -> mpfr_t -> mpfr_rnd_t -> mpfr_tv = "caml_mpfr_add"
external mpfr_add_int : mpfr_prec_t -> mpfr_t -> int -> mpfr_rnd_t -> mpfr_tv = "caml_mpfr_add_si"
external mpfr_add_float : mpfr_prec_t -> mpfr_t -> float -> mpfr_rnd_t -> mpfr_tv = "caml_mpfr_add_d"
external mpfr_sub : mpfr_prec_t -> mpfr_t -> mpfr_t -> mpfr_rnd_t -> mpfr_tv = "caml_mpfr_sub"
external mpfr_int_sub : mpfr_prec_t -> int -> mpfr_t -> mpfr_rnd_t -> mpfr_tv = "caml_mpfr_si_sub"
external mpfr_sub_int : mpfr_prec_t -> mpfr_t -> int -> mpfr_rnd_t -> mpfr_tv = "caml_mpfr_sub_si"
external mpfr_float_sub : mpfr_prec_t -> float -> mpfr_t -> mpfr_rnd_t -> mpfr_tv = "caml_mpfr_d_sub"
external mpfr_sub_float : mpfr_prec_t -> mpfr_t -> float -> mpfr_rnd_t -> mpfr_tv = "caml_mpfr_sub_d"
external mpfr_mul : mpfr_prec_t -> mpfr_t -> mpfr_t -> mpfr_rnd_t -> mpfr_tv = "caml_mpfr_mul"
external mpfr_mul_int : mpfr_prec_t -> mpfr_t -> int -> mpfr_rnd_t -> mpfr_tv = "caml_mpfr_mul_si"
external mpfr_mul_float : mpfr_prec_t -> mpfr_t -> float -> mpfr_rnd_t -> mpfr_tv = "caml_mpfr_mul_d"
external mpfr_sqr : mpfr_prec_t -> mpfr_t -> mpfr_rnd_t -> mpfr_tv = "caml_mpfr_sqr"
external mpfr_div : mpfr_prec_t -> mpfr_t -> mpfr_t -> mpfr_rnd_t -> mpfr_tv = "caml_mpfr_div"
external mpfr_int_div : mpfr_prec_t -> int -> mpfr_t -> mpfr_rnd_t -> mpfr_tv = "caml_mpfr_si_div"
external mpfr_div_int : mpfr_prec_t -> mpfr_t -> int -> mpfr_rnd_t -> mpfr_tv = "caml_mpfr_div_si"
external mpfr_float_div : mpfr_prec_t -> float -> mpfr_t -> mpfr_rnd_t -> mpfr_tv = "caml_mpfr_d_div"
external mpfr_div_float : mpfr_prec_t -> mpfr_t -> float -> mpfr_rnd_t -> mpfr_tv = "caml_mpfr_div_d"
external mpfr_sqrt : mpfr_prec_t -> mpfr_t -> mpfr_rnd_t -> mpfr_tv = "caml_mpfr_sqrt"
external mpfr_sqrt_int : mpfr_prec_t -> int -> mpfr_rnd_t -> mpfr_tv = "caml_mpfr_sqrt_ui"
external mpfr_rec_sqrt : mpfr_prec_t -> mpfr_t -> mpfr_rnd_t -> mpfr_tv = "caml_mpfr_rec_sqrt"
external mpfr_cbrt : mpfr_prec_t -> mpfr_t -> mpfr_rnd_t -> mpfr_tv = "caml_mpfr_cbrt"
external mpfr_root : mpfr_prec_t -> mpfr_t -> int -> mpfr_rnd_t -> mpfr_tv = "caml_mpfr_root"
external mpfr_pow : mpfr_prec_t -> mpfr_t -> mpfr_t -> mpfr_rnd_t -> mpfr_tv = "caml_mpfr_pow"
external mpfr_pow_int : mpfr_prec_t -> mpfr_t -> int -> mpfr_rnd_t -> mpfr_tv = "caml_mpfr_pow_si"
external mpfr_neg : mpfr_prec_t -> mpfr_t -> mpfr_rnd_t -> mpfr_tv = "caml_mpfr_neg"
external mpfr_abs : mpfr_prec_t -> mpfr_t -> mpfr_rnd_t -> mpfr_tv = "caml_mpfr_abs"
external mpfr_dim : mpfr_prec_t -> mpfr_t -> mpfr_t -> mpfr_rnd_t -> mpfr_tv = "caml_mpfr_dim"
external mpfr_mul_2int : mpfr_prec_t -> mpfr_t -> int -> mpfr_rnd_t -> mpfr_tv = "caml_mpfr_mul_2si"
external mpfr_div_2int : mpfr_prec_t -> mpfr_t -> int -> mpfr_rnd_t -> mpfr_tv = "caml_mpfr_div_2si"


(* 5.6 Comparison Functions *)
external mpfr_cmp : mpfr_t -> mpfr_t -> int = "caml_mpfr_cmp"
external mpfr_cmp_int : mpfr_t -> int -> int = "caml_mpfr_cmp_si"
external mpfr_cmp_float : mpfr_t -> float -> int = "caml_mpfr_cmp_d"
external mpfr_cmp_int_2exp : mpfr_t -> int -> int -> int = "caml_mpfr_cmp_si_2exp"
external mpfr_cmpabs : mpfr_t -> mpfr_t -> int = "caml_mpfr_cmpabs"
external mpfr_nan_p : mpfr_t -> bool = "caml_mpfr_nan_p"
external mpfr_inf_p : mpfr_t -> bool = "caml_mpfr_inf_p"
external mpfr_number_p : mpfr_t -> bool = "caml_mpfr_number_p"
external mpfr_zero_p : mpfr_t -> bool = "caml_mpfr_zero_p"
external mpfr_regular_p : mpfr_t -> bool = "caml_mpfr_regular_p"
external mpfr_sgn : mpfr_t -> int = "caml_mpfr_sgn"
external mpfr_greater_p : mpfr_t -> mpfr_t -> bool = "caml_mpfr_greater_p"
external mpfr_greaterequal_p : mpfr_t -> mpfr_t -> bool = "caml_mpfr_greaterequal_p"
external mpfr_less_p : mpfr_t -> mpfr_t -> bool = "caml_mpfr_less_p"
external mpfr_lessequal_p : mpfr_t -> mpfr_t -> bool = "caml_mpfr_lessequal_p"
external mpfr_equal_p : mpfr_t -> mpfr_t -> bool = "caml_mpfr_equal_p"
external mpfr_lessgreater_p : mpfr_t -> mpfr_t -> bool = "caml_mpfr_lessgreater_p"
external mpfr_unordered_p : mpfr_t -> mpfr_t -> bool = "caml_mpfr_unordered_p"


(* 5.7 Special Functions *)
external mpfr_log : mpfr_prec_t -> mpfr_t -> mpfr_rnd_t -> mpfr_tv = "caml_mpfr_log"
external mpfr_log2 : mpfr_prec_t -> mpfr_t -> mpfr_rnd_t -> mpfr_tv = "caml_mpfr_log2"
external mpfr_log10 : mpfr_prec_t -> mpfr_t -> mpfr_rnd_t -> mpfr_tv = "caml_mpfr_log10"
external mpfr_exp : mpfr_prec_t -> mpfr_t -> mpfr_rnd_t -> mpfr_tv = "caml_mpfr_exp"
external mpfr_exp2 : mpfr_prec_t -> mpfr_t -> mpfr_rnd_t -> mpfr_tv = "caml_mpfr_exp2"
external mpfr_exp10 : mpfr_prec_t -> mpfr_t -> mpfr_rnd_t -> mpfr_tv = "caml_mpfr_exp10"
external mpfr_cos : mpfr_prec_t -> mpfr_t -> mpfr_rnd_t -> mpfr_tv = "caml_mpfr_cos"
external mpfr_sin : mpfr_prec_t -> mpfr_t -> mpfr_rnd_t -> mpfr_tv = "caml_mpfr_sin"
external mpfr_tan : mpfr_prec_t -> mpfr_t -> mpfr_rnd_t -> mpfr_tv = "caml_mpfr_tan"
external mpfr_sin_cos : mpfr_prec_t -> mpfr_prec_t -> mpfr_t -> mpfr_rnd_t -> mpfr_t * mpfr_t * int = "caml_mpfr_sin_cos"
external mpfr_sec : mpfr_prec_t -> mpfr_t -> mpfr_rnd_t -> mpfr_tv = "caml_mpfr_sec"
external mpfr_csc : mpfr_prec_t -> mpfr_t -> mpfr_rnd_t -> mpfr_tv = "caml_mpfr_csc"
external mpfr_cot : mpfr_prec_t -> mpfr_t -> mpfr_rnd_t -> mpfr_tv = "caml_mpfr_cot"
external mpfr_acos : mpfr_prec_t -> mpfr_t -> mpfr_rnd_t -> mpfr_tv = "caml_mpfr_acos"
external mpfr_asin : mpfr_prec_t -> mpfr_t -> mpfr_rnd_t -> mpfr_tv = "caml_mpfr_asin"
external mpfr_atan : mpfr_prec_t -> mpfr_t -> mpfr_rnd_t -> mpfr_tv = "caml_mpfr_atan"
external mpfr_atan2 : mpfr_prec_t -> mpfr_t -> mpfr_t -> mpfr_rnd_t -> mpfr_tv = "caml_mpfr_atan2"
external mpfr_cosh : mpfr_prec_t -> mpfr_t -> mpfr_rnd_t -> mpfr_tv = "caml_mpfr_cosh"
external mpfr_sinh : mpfr_prec_t -> mpfr_t -> mpfr_rnd_t -> mpfr_tv = "caml_mpfr_sinh"
external mpfr_tanh : mpfr_prec_t -> mpfr_t -> mpfr_rnd_t -> mpfr_tv = "caml_mpfr_tanh"
external mpfr_sinh_cosh : mpfr_prec_t -> mpfr_prec_t -> mpfr_t -> mpfr_rnd_t -> mpfr_t * mpfr_t * int = "caml_mpfr_sinh_cosh"
external mpfr_sech : mpfr_prec_t -> mpfr_t -> mpfr_rnd_t -> mpfr_tv = "caml_mpfr_sech"
external mpfr_csch : mpfr_prec_t -> mpfr_t -> mpfr_rnd_t -> mpfr_tv = "caml_mpfr_csch"
external mpfr_coth : mpfr_prec_t -> mpfr_t -> mpfr_rnd_t -> mpfr_tv = "caml_mpfr_coth"
external mpfr_acosh : mpfr_prec_t -> mpfr_t -> mpfr_rnd_t -> mpfr_tv = "caml_mpfr_acosh"
external mpfr_asinh : mpfr_prec_t -> mpfr_t -> mpfr_rnd_t -> mpfr_tv = "caml_mpfr_asinh"
external mpfr_atanh : mpfr_prec_t -> mpfr_t -> mpfr_rnd_t -> mpfr_tv = "caml_mpfr_atanh"
external mpfr_fac_int : mpfr_prec_t -> int -> mpfr_rnd_t -> mpfr_tv = "caml_mpfr_fac_ui"
external mpfr_log1p : mpfr_prec_t -> mpfr_t -> mpfr_rnd_t -> mpfr_tv = "caml_mpfr_log1p"
external mpfr_expm1 : mpfr_prec_t -> mpfr_t -> mpfr_rnd_t -> mpfr_tv = "caml_mpfr_expm1"
external mpfr_eint : mpfr_prec_t -> mpfr_t -> mpfr_rnd_t -> mpfr_tv = "caml_mpfr_eint"
external mpfr_li2 : mpfr_prec_t -> mpfr_t -> mpfr_rnd_t -> mpfr_tv = "caml_mpfr_li2"
external mpfr_gamma : mpfr_prec_t -> mpfr_t -> mpfr_rnd_t -> mpfr_tv = "caml_mpfr_gamma"
external mpfr_lngamma : mpfr_prec_t -> mpfr_t -> mpfr_rnd_t -> mpfr_tv = "caml_mpfr_lngamma"
external mpfr_lgamma : mpfr_prec_t -> mpfr_t -> mpfr_rnd_t -> mpfr_tv * int = "caml_mpfr_lgamma"
external mpfr_digamma : mpfr_prec_t -> mpfr_t -> mpfr_rnd_t -> mpfr_tv = "caml_mpfr_digamma"
external mpfr_zeta : mpfr_prec_t -> mpfr_t -> mpfr_rnd_t -> mpfr_tv = "caml_mpfr_zeta"
external mpfr_zeta_int : mpfr_prec_t -> int -> mpfr_rnd_t -> mpfr_tv = "caml_mpfr_zeta_ui"
external mpfr_erf : mpfr_prec_t -> mpfr_t -> mpfr_rnd_t -> mpfr_tv = "caml_mpfr_erf"
external mpfr_erfc : mpfr_prec_t -> mpfr_t -> mpfr_rnd_t -> mpfr_tv = "caml_mpfr_erfc"
external mpfr_j0 : mpfr_prec_t -> mpfr_t -> mpfr_rnd_t -> mpfr_tv = "caml_mpfr_j0"
external mpfr_j1 : mpfr_prec_t -> mpfr_t -> mpfr_rnd_t -> mpfr_tv = "caml_mpfr_j1"
external mpfr_jn : mpfr_prec_t -> int -> mpfr_t -> mpfr_rnd_t -> mpfr_tv = "caml_mpfr_jn"
external mpfr_y0 : mpfr_prec_t -> mpfr_t -> mpfr_rnd_t -> mpfr_tv = "caml_mpfr_y0"
external mpfr_y1 : mpfr_prec_t -> mpfr_t -> mpfr_rnd_t -> mpfr_tv = "caml_mpfr_y1"
external mpfr_yn : mpfr_prec_t -> int -> mpfr_t -> mpfr_rnd_t -> mpfr_tv = "caml_mpfr_yn"
external mpfr_fma : mpfr_prec_t -> mpfr_t -> mpfr_t -> mpfr_t -> mpfr_rnd_t -> mpfr_tv = "caml_mpfr_fma"
external mpfr_fms : mpfr_prec_t -> mpfr_t -> mpfr_t -> mpfr_t -> mpfr_rnd_t -> mpfr_tv = "caml_mpfr_fms"
external mpfr_agm : mpfr_prec_t -> mpfr_t -> mpfr_t -> mpfr_rnd_t -> mpfr_tv = "caml_mpfr_agm"
external mpfr_hypot : mpfr_prec_t -> mpfr_t -> mpfr_t -> mpfr_rnd_t -> mpfr_tv = "caml_mpfr_hypot"
external mpfr_ai : mpfr_prec_t -> mpfr_t -> mpfr_rnd_t -> mpfr_tv = "caml_mpfr_ai"
external mpfr_const_log2 : mpfr_prec_t -> mpfr_prec_t -> mpfr_rnd_t -> mpfr_tv = "caml_mpfr_const_log2"
external mpfr_const_pi : mpfr_prec_t -> mpfr_prec_t -> mpfr_rnd_t -> mpfr_tv = "caml_mpfr_const_pi"
external mpfr_const_euler : mpfr_prec_t -> mpfr_prec_t -> mpfr_rnd_t -> mpfr_tv = "caml_mpfr_const_euler"
external mpfr_const_catalan : mpfr_prec_t -> mpfr_prec_t -> mpfr_rnd_t -> mpfr_tv = "caml_mpfr_const_catalan"
external mpfr_free_cache : unit -> unit = "caml_mpfr_free_cache"
external mpfr_sum : mpfr_prec_t -> mpfr_t list -> mpfr_rnd_t -> mpfr_tv = "caml_mpfr_sum"


(* 5.8 Input and Output Functions *)
let mpfr_out_str chan base n op rnd =
  let se = mpfr_get_str base n op rnd in
  let significand = se.significand in
  let exponent = se.exponent in
  if String.contains significand '@'
  then
    begin
      Printf.fprintf chan "%s" significand;
      String.length significand
    end
  else
    begin
      if significand.[0] == '-'
      then
        Printf.fprintf chan "-%c.%s%c%d"
                       significand.[1]
                       (String.sub significand 2 (String.length significand - 2))
                       (if base > 10 then '@' else 'e')
                       (exponent - 1)
      else
        Printf.fprintf chan "%c.%s%c%d"
                       significand.[0]
                       (String.sub significand 1 (String.length significand - 1))
                       (if base > 10 then '@' else 'e')
                       (exponent - 1);
      (String.length significand) + (String.length (string_of_int (exponent -1))) + 2
    end

let mpfr_inp_str prec chan base rnd =
  let rop = mpfr_init2 prec in
  let str = read_line chan in
  let n = mpfr_set_str rop str base rnd in
  (rop, n)
