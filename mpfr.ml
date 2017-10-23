include Mlmpfr

type ternary = Correctly_Rounded | Greater | Lower
type mpfr_float = mpfr_t * ternary option


let default_precision = ref (mpfr_get_default_prec ())
let default_rounding = ref (mpfr_get_default_rounding_mode ())


let make_from_float ?prec:(prec = !default_precision) ?rnd:(rnd = !default_rounding) op =
  let res = mpfr_init_set_float prec op rnd in
  let ter = if res.tv >= 0 then if res.tv == 0 then Correctly_Rounded else Greater else Lower in
  (res.rop, Some ter)

let set_default_precision p =
  mpfr_set_default_prec p;
  default_precision := mpfr_get_default_prec ()

let get_precision x =
  match x with
    r, _ -> mpfr_get_prec r
