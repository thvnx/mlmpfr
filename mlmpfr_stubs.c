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

CAMLprim value mpfr_prec_min_ml ()
{
  CAMLparam0 ();
  CAMLreturn (Val_int (MPFR_PREC_MIN));
}

CAMLprim value mpfr_prec_max_ml ()
{
  CAMLparam0 ();
  CAMLreturn (Val_int (MPFR_PREC_MAX));
}

CAMLprim value mpfr_init2_ml (value prec)
{
  CAMLparam1 (prec);
  CAMLlocal1 (initialized_value);
  initialized_value = caml_alloc_custom (&mpfr_ops, sizeof (mpfr_t), 0, 1);
  mpfr_init2 (Mpfr_val (initialized_value), (mpfr_prec_t) Int_val (prec));
  CAMLreturn (initialized_value);
}

CAMLprim value mpfr_inits2_ml (value prec, value n)
{
  CAMLparam2 (prec, n);
  CAMLlocal2 (list, tmp);

  if (Int_val (n) <= 0) // if n is zero, return empty list
    CAMLreturn (Val_int (0));

  // build a list of size n
  list = caml_alloc (2, 0);
  Store_field (list, 0, mpfr_init2_ml (prec));
  Store_field (list, 1, Val_int(0));
  for (int i = 1; i < Int_val (n); i++)
    {
      tmp = caml_alloc (2, 0);
      Store_field (tmp, 0, mpfr_init2_ml (prec));
      Store_field (tmp, 1, list);
      list = tmp;
    }
  CAMLreturn (list);
}

CAMLprim value mpfr_clear_ml (value op)
{
  CAMLparam1 (op);
  mpfr_clear (Mpfr_val (op));
  CAMLreturn (Val_unit);
}

CAMLprim value mpfr_init_ml ()
{
  CAMLparam0 ();
  CAMLlocal1 (initialized_value);
  initialized_value = caml_alloc_custom (&mpfr_ops, sizeof (mpfr_t), 0, 1);
  mpfr_init (Mpfr_val (initialized_value));
  CAMLreturn (initialized_value);
}

CAMLprim value mpfr_inits_ml (value n)
{
  CAMLparam1 (n);
  CAMLlocal2 (list, tmp);

  if (Int_val (n) <= 0) // if n is zero, return empty list
    CAMLreturn (Val_int (0));

  // build a list of size n
  list = caml_alloc (2, 0);
  Store_field (list, 0, mpfr_init_ml ());
  Store_field (list, 1, Val_int(0));
  for (int i = 1; i < Int_val (n); i++)
    {
      tmp = caml_alloc (2, 0);
      Store_field (tmp, 0, mpfr_init_ml ());
      Store_field (tmp, 1, list);
      list = tmp;
    }
  CAMLreturn (list);
}

CAMLprim value mpfr_set_default_prec_ml (value prec)
{
  CAMLparam1 (prec);
  mpfr_set_default_prec (Int_val (prec));
  CAMLreturn (Val_unit);
}

CAMLprim value mpfr_get_default_prec_ml ()
{
  CAMLparam0 ();
  mpfr_prec_t prec = mpfr_get_default_prec ();
  CAMLreturn (Val_int (prec));
}

CAMLprim value mpfr_set_prec_ml (value op, value prec)
{
  CAMLparam2 (op, prec);
  mpfr_set_prec (Mpfr_val (op), Int_val (prec));
  CAMLreturn (Val_unit);
}

CAMLprim value mpfr_get_prec_ml (value op)
{
  CAMLparam1 (op);
  CAMLreturn (Val_int (mpfr_get_prec (Mpfr_val (op))));
}

CAMLprim value mpfr_set_d_ml (value op, value d, value rnd)
{
  CAMLparam3 (op, d, rnd);
  CAMLreturn (Val_int (mpfr_set_d (Mpfr_val (op), Double_val (d),
				   rounding_mode2mpfr_rnd_t (Int_val (rnd)))));
}

CAMLprim value mpfr_get_str_ml (value base, value n, value op, value rnd)
{
  CAMLparam4 (base, n, op, rnd);

  char *ret;
  mpfr_exp_t expptr;
  value result;

  ret = mpfr_get_str (NULL, &expptr, Int_val (base), Int_val (n), Mpfr_val (op),
		      rounding_mode2mpfr_rnd_t (Int_val (rnd)));

  result = caml_alloc_tuple (2);

  Store_field (result, 0, caml_copy_string (ret));
  Store_field (result, 1, Val_int (expptr));
  mpfr_free_str (ret);

  CAMLreturn (result);
}
