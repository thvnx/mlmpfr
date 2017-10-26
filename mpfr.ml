include Mlmpfr

type sign = Positive | Negative
type ternary = Correctly_Rounded | Greater | Lower
type mpfr_float = mpfr_t * ternary option

let mpfr_prec_min = get_mpfr_prec_min_macro ()
let mpfr_prec_max = get_mpfr_prec_max_macro ()

let default_precision = ref (mpfr_get_default_prec ())
let default_rounding = ref (mpfr_get_default_rounding_mode ())

exception Precision_range of int
exception Base_range of int

let precision_in_range p =
  if (p >= mpfr_prec_min) && (p <= mpfr_prec_max)
  then ()
  else raise (Precision_range p)

let base_in_range b =
  if ((b >= 2) && (b <= 64)) || b == 0
  then ()
  else raise (Base_range b)

let ternary_int_to_type t =
  if t >= 0 then if t == 0 then Correctly_Rounded else Greater else Lower

let rounding_to_string x =
  match x with
    _, Some Correctly_Rounded -> "Correct"
  | _, Some Lower -> "Lower"
  | _, Some Greater -> "Greater"
  | _ -> "No_Rounding"

let make_from_mpfr ?prec:(prec = !default_precision) ?rnd:(rnd = !default_rounding) op =
  precision_in_range prec;
  let res = match op with op, _ -> mpfr_init_set_mpfr prec op rnd in
  let ter = ternary_int_to_type res.tv in
  (res.rop, Some ter)

let make_from_int ?prec:(prec = !default_precision) ?rnd:(rnd = !default_rounding) op =
  precision_in_range prec;
  let res = mpfr_init_set_int prec op rnd in
  let ter = ternary_int_to_type res.tv in
  (res.rop, Some ter)

let make_from_float ?prec:(prec = !default_precision) ?rnd:(rnd = !default_rounding) op =
  precision_in_range prec;
  let res = mpfr_init_set_float prec op rnd in
  let ter = ternary_int_to_type res.tv in
  (res.rop, Some ter)

let make_from_str ?prec:(prec = !default_precision) ?rnd:(rnd = !default_rounding) ?base:(base = 0) op =
  precision_in_range prec;
  base_in_range base;
  let res = mpfr_init_set_str prec op base rnd in
  let ter = ternary_int_to_type res.tv in
  (res.rop, Some ter)

let make_nan ?prec:(prec = !default_precision) _ =
  let res = mpfr_init_set_nan prec in
  (res, None)

let make_inf ?prec:(prec = !default_precision) sign =
  let res = mpfr_init_set_inf prec (match sign with Positive -> 1 | Negative -> -1) in
  (res, None)

let make_zero ?prec:(prec = !default_precision) sign =
  let res = mpfr_init_set_zero prec (match sign with Positive -> 1 | Negative -> -1) in
  (res, None)

let set_default_precision p =
  precision_in_range p;
  mpfr_set_default_prec p;
  default_precision := mpfr_get_default_prec ()

let get_default_precision _ =
  mpfr_get_default_prec ()

let get_precision x =
  match x with
    r, _ -> mpfr_get_prec r

let get_float ?rnd:(rnd = !default_rounding) x =
  match x with
    r, _ -> mpfr_get_float r rnd

let get_int ?rnd:(rnd = !default_rounding) x =
  match x with
    r, _ -> mpfr_get_int r rnd

let get_float_2exp ?rnd:(rnd = !default_rounding) x =
  match x with
    r, _ -> let fe = mpfr_get_float_2exp r rnd in
            (fe.n, fe.e)

let get_mpfr_2exp ?rnd:(rnd = !default_rounding) ?prec:(prec = !default_precision) x =
  precision_in_range prec;
  match x with
    r, _ -> let fe, t = mpfr_frexp prec r rnd in
            let ter = ternary_int_to_type t in
            ((fe.n, Some ter), fe.e)

let get_str ?rnd:(rnd = !default_rounding) ?base:(base = 10) ?size:(size = 0) x =
  base_in_range base;
  let s = if size < 0 then 0 else size in
  match x with
    r, _ -> let se = mpfr_get_str base s r rnd in
            (se.significand, string_of_int se.exponent)

let get_formatted_str ?rnd:(rnd = !default_rounding) ?base:(base = 10) ?size:(size = 0) x =
  let sign, exp = get_str ~rnd:rnd ~base:base ~size:size x in
  if String.contains sign '@' (* nan or inf *)
  then sign
  else
    if sign.[0] == '-'
    then "-" ^ (Char.escaped sign.[1]) ^ "." ^ (String.sub sign 2 (String.length sign - 2)) ^
           (if base > 10 then "@" else "e") ^ (string_of_int ((int_of_string exp) - 1))
    else (Char.escaped sign.[0]) ^ "." ^ (String.sub sign 1 (String.length sign - 1)) ^
           (if base > 10 then "@" else "e") ^ (string_of_int ((int_of_string exp) - 1))

let fits_int_p ?rnd:(rnd = !default_rounding) x =
  match x with
    r, _ -> mpfr_fits_int_p r rnd
