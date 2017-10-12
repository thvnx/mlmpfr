#include <stdio.h>
#include <mpfr.h>
#include <caml/mlvalues.h>
#include <caml/memory.h>
#include <caml/alloc.h>
#include <caml/custom.h>
#include <caml/fail.h>


static struct custom_operations mpfr_ops = {
  "???",
  custom_finalize_default,
  custom_compare_default,
  custom_hash_default,
  custom_serialize_default,
  custom_deserialize_default,
  custom_compare_ext_default
};

#define Mpfr_val(m) (*((mpfr_t *) Data_custom_val (m)))

int rounding_mode2mpfr_rnd_t (r)
{
  switch (r)
    {
    case 1: return MPFR_RNDN;
    case 2: return MPFR_RNDZ;
    case 3: return MPFR_RNDU;
    case 4: return MPFR_RNDD;
    case 5: return MPFR_RNDA;
    default:
      caml_failwith(__FUNCTION__);
    }
}

CAMLprim value mpfr_init2_ml (value prec)
{
  CAMLparam1 (prec);
  CAMLlocal1 (initialized_value);
  initialized_value = caml_alloc_custom (&mpfr_ops, sizeof (mpfr_t), 0, 1);
  mpfr_init2 (Mpfr_val (initialized_value), (mpfr_prec_t) Int_val (prec));
  CAMLreturn (initialized_value);
}

CAMLprim value mpfr_out_str_ml (value base, value n, value op, value rnd)
{
  CAMLparam4 (base, n, op, rnd);
  CAMLreturn (Int_val (mpfr_out_str (stdout,
				     Int_val (base),
				     Int_val (n),
				     Mpfr_val (op),
				     rounding_mode2mpfr_rnd_t (Int_val (rnd)))));
}
