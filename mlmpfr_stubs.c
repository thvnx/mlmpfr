#include <stdio.h>
#include <mpfr.h>
#include <caml/mlvalues.h>
#include <caml/memory.h>
#include <caml/alloc.h>
#include <caml/custom.h>
#include <caml/fail.h>


static struct custom_operations mpfr_ops = {
  "github.com/thvnx/mlmpfr.1",
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
    case 0: return MPFR_RNDN;
    case 1: return MPFR_RNDZ;
    case 2: return MPFR_RNDU;
    case 3: return MPFR_RNDD;
    case 4: return MPFR_RNDA;
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

CAMLprim value mpfr_clear_ml (value op)
{
  CAMLparam1 (op);
  mpfr_clear (Mpfr_val (op));
  CAMLreturn (Val_unit);
}

CAMLprim value mpfr_set_d_ml (value op, value d, value rnd)
{
  CAMLparam3 (op, d, rnd);
  CAMLreturn (Val_int (mpfr_set_d (Mpfr_val (op), Double_val (d),
				   rounding_mode2mpfr_rnd_t (Int_val (rnd)))));
}

CAMLprim value mpfr_out_str_ml (value fn, value base, value n, value op, value rnd)
{
  CAMLparam5 (fn, base, n, op, rnd);
  char *of = String_val (fn);
  FILE *fd = fopen (of, "a");
  int wc = mpfr_out_str (fd, Int_val (base), Int_val (n), Mpfr_val (op),
			 rounding_mode2mpfr_rnd_t (Int_val (rnd)));
  fclose(fd);
  CAMLreturn (Val_int (wc));
}
