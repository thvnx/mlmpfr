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
exception Invalid_math of string

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
  let significand, exponent = get_str ~rnd:rnd ~base:base ~size:size x in
  let exponent = (int_of_string exponent) - 1 in
  if String.contains significand '@' (* nan or inf *)
  then significand
  else
    if significand.[0] == '-'
    then Printf.sprintf "-%c.%s%c%+03d" significand.[1] (String.sub significand 2 (String.length significand - 2))
                        (if base > 10 then '@' else 'e') exponent
    else Printf.sprintf "%c.%s%c%+03d" significand.[0] (String.sub significand 1 (String.length significand - 1))
                        (if base > 10 then '@' else 'e') exponent

let fits_int_p ?rnd:(rnd = !default_rounding) x =
  match x with
    r, _ -> mpfr_fits_int_p r rnd

let add ?rnd:(rnd = !default_rounding) ?prec:(prec = !default_precision) op1 op2 =
  precision_in_range prec;
  match (op1, op2) with
    (m1, _), (m2, _) -> let r = mpfr_add prec m1 m2 rnd in (r.rop, Some (ternary_int_to_type r.tv))

let add_int ?rnd:(rnd = !default_rounding) ?prec:(prec = !default_precision) op1 op2 =
  precision_in_range prec;
  match (op1, op2) with
    (m1, _), i2 -> let r = mpfr_add_int prec m1 i2 rnd in (r.rop, Some (ternary_int_to_type r.tv))

let add_float ?rnd:(rnd = !default_rounding) ?prec:(prec = !default_precision) op1 op2 =
  precision_in_range prec;
  match (op1, op2) with
    (m1, _), f2 -> let r = mpfr_add_float prec m1 f2 rnd in (r.rop, Some (ternary_int_to_type r.tv))

let sub ?rnd:(rnd = !default_rounding) ?prec:(prec = !default_precision) op1 op2 =
  precision_in_range prec;
  match (op1, op2) with
    (m1, _), (m2, _) -> let r = mpfr_sub prec m1 m2 rnd in (r.rop, Some (ternary_int_to_type r.tv))

let sub_int ?rnd:(rnd = !default_rounding) ?prec:(prec = !default_precision) op1 op2 =
  precision_in_range prec;
  match (op1, op2) with
    (m1, _), i2 -> let r = mpfr_sub_int prec m1 i2 rnd in (r.rop, Some (ternary_int_to_type r.tv))

let int_sub ?rnd:(rnd = !default_rounding) ?prec:(prec = !default_precision) op1 op2 =
  precision_in_range prec;
  match (op1, op2) with
    i1, (m2, _) -> let r = mpfr_int_sub prec i1 m2 rnd in (r.rop, Some (ternary_int_to_type r.tv))

let sub_float ?rnd:(rnd = !default_rounding) ?prec:(prec = !default_precision) op1 op2 =
  precision_in_range prec;
  match (op1, op2) with
    (m1, _), f2 -> let r = mpfr_sub_float prec m1 f2 rnd in (r.rop, Some (ternary_int_to_type r.tv))

let float_sub ?rnd:(rnd = !default_rounding) ?prec:(prec = !default_precision) op1 op2 =
  precision_in_range prec;
  match (op1, op2) with
    f1, (m2, _) -> let r = mpfr_float_sub prec f1 m2 rnd in (r.rop, Some (ternary_int_to_type r.tv))

let mul ?rnd:(rnd = !default_rounding) ?prec:(prec = !default_precision) op1 op2 =
  precision_in_range prec;
  match (op1, op2) with
    (m1, _), (m2, _) -> let r = mpfr_mul prec m1 m2 rnd in (r.rop, Some (ternary_int_to_type r.tv))

let mul_int ?rnd:(rnd = !default_rounding) ?prec:(prec = !default_precision) op1 op2 =
  precision_in_range prec;
  match (op1, op2) with
    (m1, _), i2 -> let r = mpfr_mul_int prec m1 i2 rnd in (r.rop, Some (ternary_int_to_type r.tv))

let mul_float ?rnd:(rnd = !default_rounding) ?prec:(prec = !default_precision) op1 op2 =
  precision_in_range prec;
  match (op1, op2) with
    (m1, _), f2 -> let r = mpfr_mul_float prec m1 f2 rnd in (r.rop, Some (ternary_int_to_type r.tv))

let div ?rnd:(rnd = !default_rounding) ?prec:(prec = !default_precision) op1 op2 =
  precision_in_range prec;
  match (op1, op2) with
    (m1, _), (m2, _) -> let r = mpfr_div prec m1 m2 rnd in (r.rop, Some (ternary_int_to_type r.tv))

let div_int ?rnd:(rnd = !default_rounding) ?prec:(prec = !default_precision) op1 op2 =
  precision_in_range prec;
  match (op1, op2) with
    (m1, _), i2 -> let r = mpfr_div_int prec m1 i2 rnd in (r.rop, Some (ternary_int_to_type r.tv))

let int_div ?rnd:(rnd = !default_rounding) ?prec:(prec = !default_precision) op1 op2 =
  precision_in_range prec;
  match (op1, op2) with
    i1, (m2, _) -> let r = mpfr_int_div prec i1 m2 rnd in (r.rop, Some (ternary_int_to_type r.tv))

let div_float ?rnd:(rnd = !default_rounding) ?prec:(prec = !default_precision) op1 op2 =
  precision_in_range prec;
  match (op1, op2) with
    (m1, _), f2 -> let r = mpfr_div_float prec m1 f2 rnd in (r.rop, Some (ternary_int_to_type r.tv))

let float_div ?rnd:(rnd = !default_rounding) ?prec:(prec = !default_precision) op1 op2 =
  precision_in_range prec;
  match (op1, op2) with
    f1, (m2, _) -> let r = mpfr_float_div prec f1 m2 rnd in (r.rop, Some (ternary_int_to_type r.tv))

let sqrt ?rnd:(rnd = !default_rounding) ?prec:(prec = !default_precision) op =
  precision_in_range prec;
  match op with
    m, _ -> let r = mpfr_sqrt prec m rnd in (r.rop, Some (ternary_int_to_type r.tv))

let sqrt_int ?rnd:(rnd = !default_rounding) ?prec:(prec = !default_precision) op =
  precision_in_range prec;
  let r = mpfr_sqrt_int prec op rnd in (r.rop, Some (ternary_int_to_type r.tv))

let cbrt ?rnd:(rnd = !default_rounding) ?prec:(prec = !default_precision) op =
  precision_in_range prec;
  match op with
    m, _ -> let r = mpfr_cbrt prec m rnd in (r.rop, Some (ternary_int_to_type r.tv))

let root ?rnd:(rnd = !default_rounding) ?prec:(prec = !default_precision) op k =
  precision_in_range prec;
  match op with
    m, _ -> let r = mpfr_root prec m k rnd in (r.rop, Some (ternary_int_to_type r.tv))

let rec_sqrt ?rnd:(rnd = !default_rounding) ?prec:(prec = !default_precision) op =
  precision_in_range prec;
  match op with
    m, _ -> let r = mpfr_rec_sqrt prec m rnd in (r.rop, Some (ternary_int_to_type r.tv))

let pow ?rnd:(rnd = !default_rounding) ?prec:(prec = !default_precision) x y =
  precision_in_range prec;
  match x, y with
    (mx, _), (my, _) -> let r = mpfr_pow prec mx my rnd in (r.rop, Some (ternary_int_to_type r.tv))

let pow_int ?rnd:(rnd = !default_rounding) ?prec:(prec = !default_precision) x y =
  precision_in_range prec;
  match x, y with
    (mx, _), iy -> let r = mpfr_pow_int prec mx iy rnd in (r.rop, Some (ternary_int_to_type r.tv))

let int_pow ?rnd:(rnd = !default_rounding) ?prec:(prec = !default_precision) x y =
  precision_in_range prec;
  match x, y with
    ix, (my, _) -> let r = mpfr_int_pow prec ix my rnd in (r.rop, Some (ternary_int_to_type r.tv))

let int_pow_int ?rnd:(rnd = !default_rounding) ?prec:(prec = !default_precision) x y =
  precision_in_range prec;
  let r = mpfr_int_pow_int prec x y rnd in (r.rop, Some (ternary_int_to_type r.tv))

let neg ?rnd:(rnd = !default_rounding) ?prec:(prec = !default_precision) op =
  precision_in_range prec;
  match op with
    m, _ -> let r = mpfr_neg prec m rnd in (r.rop, Some (ternary_int_to_type r.tv))

let abs ?rnd:(rnd = !default_rounding) ?prec:(prec = !default_precision) op =
  precision_in_range prec;
  match op with
    m, _ -> let r = mpfr_abs prec m rnd in (r.rop, Some (ternary_int_to_type r.tv))

let dim ?rnd:(rnd = !default_rounding) ?prec:(prec = !default_precision) op1 op2 =
  precision_in_range prec;
  match (op1, op2) with
    (m1, _), (m2, _) -> let r = mpfr_dim prec m1 m2 rnd in (r.rop, Some (ternary_int_to_type r.tv))

let mul_2int ?rnd:(rnd = !default_rounding) ?prec:(prec = !default_precision) x y =
  precision_in_range prec;
  match (x, y) with
    (mx, _), iy -> let r = mpfr_mul_2int prec mx iy rnd in (r.rop, Some (ternary_int_to_type r.tv))

let div_2int ?rnd:(rnd = !default_rounding) ?prec:(prec = !default_precision) x y =
  precision_in_range prec;
  match (x, y) with
    (mx, _), iy -> let r = mpfr_div_2int prec mx iy rnd in (r.rop, Some (ternary_int_to_type r.tv))
