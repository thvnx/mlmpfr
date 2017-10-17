#include <stdio.h>
#include <mpfr.h>
#include <caml/mlvalues.h>
#include <caml/memory.h>
#include <caml/alloc.h>
#include <caml/custom.h>
#include <caml/fail.h>

static int custom_compare (value v1, value v2);

static struct custom_operations mpfr_ops = {
  "github.com/thvnx/mlmpfr.1",
  custom_finalize_default,
  custom_compare,
  custom_hash_default,
  custom_serialize_default,
  custom_deserialize_default,
  custom_compare_ext_default
};

#define Mpfr_val(m) (*((mpfr_t *) Data_custom_val (m)))

int rnd_val (r)
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

CAMLprim value mpfr_set_ml (value rop, value op, value rnd)
{
  CAMLparam3 (rop, op, rnd);
  CAMLreturn (Val_int (mpfr_set (Mpfr_val (rop), Mpfr_val (op),
				 rnd_val (Int_val (rnd)))));
}

CAMLprim value mpfr_set_si_ml (value rop, value op, value rnd)
{
  CAMLparam3 (rop, op, rnd);
  CAMLreturn (Val_int (mpfr_set_si (Mpfr_val (rop), Int_val (op),
				   rnd_val (Int_val (rnd)))));
}

CAMLprim value mpfr_set_d_ml (value rop, value op, value rnd)
{
  CAMLparam3 (rop, op, rnd);
  CAMLreturn (Val_int (mpfr_set_d (Mpfr_val (rop), Double_val (op),
				   rnd_val (Int_val (rnd)))));
}

CAMLprim value mpfr_set_str_ml (value rop, value op, value base, value rnd)
{
  CAMLparam4 (rop, op, base, rnd);
  CAMLreturn (Val_int (mpfr_set_str (Mpfr_val (rop), String_val (op),
				     Int_val (base), rnd_val (Int_val (rnd)))));
}

CAMLprim value mpfr_strtofr_ml (value rop, value op, value base, value rnd)
{
  CAMLparam4 (rop, op, base, rnd);
  CAMLreturn (Val_int (mpfr_strtofr (Mpfr_val (rop), String_val (op), NULL,
				     Int_val (base), rnd_val (Int_val (rnd)))));
}

CAMLprim value mpfr_set_nan_ml (value rop)
{
  CAMLparam1 (rop);
  mpfr_set_nan (Mpfr_val (rop));
  CAMLreturn (Val_unit);
}

CAMLprim value mpfr_set_inf_ml (value rop, value sign)
{
  CAMLparam2 (rop, sign);
  mpfr_set_inf (Mpfr_val (rop), Int_val (sign));
  CAMLreturn (Val_unit);
}

CAMLprim value mpfr_set_zero_ml (value rop, value sign)
{
  CAMLparam2 (rop, sign);
  mpfr_set_zero (Mpfr_val (rop), Int_val (sign));
  CAMLreturn (Val_unit);
}

CAMLprim value mpfr_swap_ml (value op1, value op2)
{
  CAMLparam2 (op1, op2);
  mpfr_swap (Mpfr_val (op1), Mpfr_val (op2));
  CAMLreturn (Val_unit);
}

CAMLprim value mpfr_init_set_ml (value op, value rnd)
{
  CAMLparam2 (op, rnd);
  CAMLlocal2 (initialized_value, result);

  int tv;

  initialized_value = caml_alloc_custom (&mpfr_ops, sizeof (mpfr_t), 0, 1);

  tv = mpfr_init_set (Mpfr_val (initialized_value), Mpfr_val (op),
		      rnd_val (Int_val (rnd)));

  result = caml_alloc_tuple (2);

  Store_field (result, 0, initialized_value);
  Store_field (result, 1, Val_int (tv));
  CAMLreturn (result);
}

CAMLprim value mpfr_init_set_si_ml (value op, value rnd)
{
  CAMLparam2 (op, rnd);
  CAMLlocal2 (initialized_value, result);

  int tv;

  initialized_value = caml_alloc_custom (&mpfr_ops, sizeof (mpfr_t), 0, 1);

  tv = mpfr_init_set_si (Mpfr_val (initialized_value), Int_val (op),
		      rnd_val (Int_val (rnd)));

  result = caml_alloc_tuple (2);

  Store_field (result, 0, initialized_value);
  Store_field (result, 1, Val_int (tv));
  CAMLreturn (result);
}

CAMLprim value mpfr_init_set_d_ml (value op, value rnd)
{
  CAMLparam2 (op, rnd);
  CAMLlocal2 (initialized_value, result);

  int tv;

  initialized_value = caml_alloc_custom (&mpfr_ops, sizeof (mpfr_t), 0, 1);

  tv = mpfr_init_set_d (Mpfr_val (initialized_value), Double_val (op),
		      rnd_val (Int_val (rnd)));

  result = caml_alloc_tuple (2);

  Store_field (result, 0, initialized_value);
  Store_field (result, 1, Val_int (tv));
  CAMLreturn (result);
}

CAMLprim value mpfr_init_set_str_ml (value op, value base, value rnd)
{
  CAMLparam3 (op, base, rnd);
  CAMLlocal2 (initialized_value, result);

  int tv;

  initialized_value = caml_alloc_custom (&mpfr_ops, sizeof (mpfr_t), 0, 1);

  tv = mpfr_init_set_str (Mpfr_val (initialized_value), String_val (op), Int_val (base),
		      rnd_val (Int_val (rnd)));

  result = caml_alloc_tuple (2);

  Store_field (result, 0, initialized_value);
  Store_field (result, 1, Val_int (tv));
  CAMLreturn (result);
}

CAMLprim value mpfr_get_d_ml (value op, value rnd)
{
  CAMLparam2 (op, rnd);
  CAMLreturn (caml_copy_double (mpfr_get_d (Mpfr_val (op), rnd_val (rnd))));
}

CAMLprim value mpfr_get_si_ml (value op, value rnd)
{
  CAMLparam2 (op, rnd);
  CAMLreturn (Val_int (mpfr_get_si (Mpfr_val (op), rnd_val (rnd))));
}

CAMLprim value mpfr_get_d_2exp_ml (value op, value rnd)
{
  CAMLparam2 (op, rnd);
  CAMLlocal1 (result);

  long *exp;
  double dv = mpfr_get_d_2exp (exp, Mpfr_val (op), rnd_val (rnd));

  result = caml_alloc_tuple (2);

  Store_field (result, 0, caml_copy_double (dv));
  Store_field (result, 1, Val_int (&exp));
  CAMLreturn (result);
}

CAMLprim value mpfr_frexp_ml (value prec, value op, value rnd)
{
  CAMLparam3 (prec, op, rnd);
  CAMLlocal2 (result, rop);

  rop = caml_alloc_custom (&mpfr_ops, sizeof (mpfr_t), 0, 1);
  mpfr_init2 (Mpfr_val (rop), Int_val (prec));

  mpfr_exp_t *exp;
  mpfr_frexp (exp, Mpfr_val (rop), Mpfr_val (op), rnd_val (rnd));

  result = caml_alloc_tuple (2);

  Store_field (result, 0, Val_int (&exp));
  Store_field (result, 1, rop);
  CAMLreturn (result);
}

CAMLprim value mpfr_get_str_ml (value base, value n, value op, value rnd)
{
  CAMLparam4 (base, n, op, rnd);
  CAMLlocal1 (result);

  char *ret;
  mpfr_exp_t expptr;

  ret = mpfr_get_str (NULL, &expptr, Int_val (base), Int_val (n), Mpfr_val (op),
		      rnd_val (Int_val (rnd)));

  result = caml_alloc_tuple (2);

  Store_field (result, 0, caml_copy_string (ret));
  Store_field (result, 1, Val_int (expptr));
  mpfr_free_str (ret);

  CAMLreturn (result);
}

CAMLprim value mpfr_fits_sint_p_ml (value op, value rnd)
{
  CAMLparam2 (op, rnd);
  CAMLreturn (Val_int (mpfr_fits_sint_p (Mpfr_val (op), rnd_val (rnd))));
}

CAMLprim value mpfr_add_ml (value prec, value op1, value op2, value rnd)
{
  CAMLparam4 (prec, op1, op2, rnd);
  CAMLlocal2 (rop, result);
  int ret;

  rop = caml_alloc_custom (&mpfr_ops, sizeof (mpfr_t), 0, 1);
  mpfr_init2 (Mpfr_val (rop), Int_val (prec));
  ret = mpfr_add (Mpfr_val (rop), Mpfr_val (op1), Mpfr_val (op2), rnd_val (rnd));

  result = caml_alloc_tuple (2);
  Store_field (result, 0, rop);
  Store_field (result, 1, Val_int (ret));
  CAMLreturn (result);
}

CAMLprim value mpfr_add_si_ml (value prec, value op1, value op2, value rnd)
{
  CAMLparam4 (prec, op1, op2, rnd);
  CAMLlocal2 (rop, result);
  int ret;

  rop = caml_alloc_custom (&mpfr_ops, sizeof (mpfr_t), 0, 1);
  mpfr_init2 (Mpfr_val (rop), Int_val (prec));
  ret = mpfr_add_si (Mpfr_val (rop), Mpfr_val (op1), Int_val (op2), rnd_val (rnd));

  result = caml_alloc_tuple (2);
  Store_field (result, 0, rop);
  Store_field (result, 1, Val_int (ret));
  CAMLreturn (result);
}

CAMLprim value mpfr_add_d_ml (value prec, value op1, value op2, value rnd)
{
  CAMLparam4 (prec, op1, op2, rnd);
  CAMLlocal2 (rop, result);
  int ret;

  rop = caml_alloc_custom (&mpfr_ops, sizeof (mpfr_t), 0, 1);
  mpfr_init2 (Mpfr_val (rop), Int_val (prec));
  ret = mpfr_add_d (Mpfr_val (rop), Mpfr_val (op1), Double_val (op2), rnd_val (rnd));

  result = caml_alloc_tuple (2);
  Store_field (result, 0, rop);
  Store_field (result, 1, Val_int (ret));
  CAMLreturn (result);
}

CAMLprim value mpfr_sub_ml (value prec, value op1, value op2, value rnd)
{
  CAMLparam4 (prec, op1, op2, rnd);
  CAMLlocal2 (rop, result);
  int ret;

  rop = caml_alloc_custom (&mpfr_ops, sizeof (mpfr_t), 0, 1);
  mpfr_init2 (Mpfr_val (rop), Int_val (prec));
  ret = mpfr_sub (Mpfr_val (rop), Mpfr_val (op1), Mpfr_val (op2), rnd_val (rnd));

  result = caml_alloc_tuple (2);
  Store_field (result, 0, rop);
  Store_field (result, 1, Val_int (ret));
  CAMLreturn (result);
}

CAMLprim value mpfr_si_sub_ml (value prec, value op1, value op2, value rnd)
{
  CAMLparam4 (prec, op1, op2, rnd);
  CAMLlocal2 (rop, result);
  int ret;

  rop = caml_alloc_custom (&mpfr_ops, sizeof (mpfr_t), 0, 1);
  mpfr_init2 (Mpfr_val (rop), Int_val (prec));
  ret = mpfr_si_sub (Mpfr_val (rop), Int_val (op1), Mpfr_val (op2), rnd_val (rnd));

  result = caml_alloc_tuple (2);
  Store_field (result, 0, rop);
  Store_field (result, 1, Val_int (ret));
  CAMLreturn (result);
}

CAMLprim value mpfr_sub_si_ml (value prec, value op1, value op2, value rnd)
{
  CAMLparam4 (prec, op1, op2, rnd);
  CAMLlocal2 (rop, result);
  int ret;

  rop = caml_alloc_custom (&mpfr_ops, sizeof (mpfr_t), 0, 1);
  mpfr_init2 (Mpfr_val (rop), Int_val (prec));
  ret = mpfr_sub_si (Mpfr_val (rop), Mpfr_val (op1), Int_val (op2), rnd_val (rnd));

  result = caml_alloc_tuple (2);
  Store_field (result, 0, rop);
  Store_field (result, 1, Val_int (ret));
  CAMLreturn (result);
}

CAMLprim value mpfr_d_sub_ml (value prec, value op1, value op2, value rnd)
{
  CAMLparam4 (prec, op1, op2, rnd);
  CAMLlocal2 (rop, result);
  int ret;

  rop = caml_alloc_custom (&mpfr_ops, sizeof (mpfr_t), 0, 1);
  mpfr_init2 (Mpfr_val (rop), Int_val (prec));
  ret = mpfr_d_sub (Mpfr_val (rop), Double_val (op1), Mpfr_val (op2), rnd_val (rnd));

  result = caml_alloc_tuple (2);
  Store_field (result, 0, rop);
  Store_field (result, 1, Val_int (ret));
  CAMLreturn (result);
}

CAMLprim value mpfr_sub_d_ml (value prec, value op1, value op2, value rnd)
{
  CAMLparam4 (prec, op1, op2, rnd);
  CAMLlocal2 (rop, result);
  int ret;

  rop = caml_alloc_custom (&mpfr_ops, sizeof (mpfr_t), 0, 1);
  mpfr_init2 (Mpfr_val (rop), Int_val (prec));
  ret = mpfr_sub_d (Mpfr_val (rop), Mpfr_val (op1), Double_val (op2), rnd_val (rnd));

  result = caml_alloc_tuple (2);
  Store_field (result, 0, rop);
  Store_field (result, 1, Val_int (ret));
  CAMLreturn (result);
}

CAMLprim value mpfr_mul_ml (value prec, value op1, value op2, value rnd)
{
  CAMLparam4 (prec, op1, op2, rnd);
  CAMLlocal2 (rop, result);
  int ret;

  rop = caml_alloc_custom (&mpfr_ops, sizeof (mpfr_t), 0, 1);
  mpfr_init2 (Mpfr_val (rop), Int_val (prec));
  ret = mpfr_mul (Mpfr_val (rop), Mpfr_val (op1), Mpfr_val (op2), rnd_val (rnd));

  result = caml_alloc_tuple (2);
  Store_field (result, 0, rop);
  Store_field (result, 1, Val_int (ret));
  CAMLreturn (result);
}

CAMLprim value mpfr_mul_si_ml (value prec, value op1, value op2, value rnd)
{
  CAMLparam4 (prec, op1, op2, rnd);
  CAMLlocal2 (rop, result);
  int ret;

  rop = caml_alloc_custom (&mpfr_ops, sizeof (mpfr_t), 0, 1);
  mpfr_init2 (Mpfr_val (rop), Int_val (prec));
  ret = mpfr_mul_si (Mpfr_val (rop), Mpfr_val (op1), Int_val (op2), rnd_val (rnd));

  result = caml_alloc_tuple (2);
  Store_field (result, 0, rop);
  Store_field (result, 1, Val_int (ret));
  CAMLreturn (result);
}

CAMLprim value mpfr_mul_d_ml (value prec, value op1, value op2, value rnd)
{
  CAMLparam4 (prec, op1, op2, rnd);
  CAMLlocal2 (rop, result);
  int ret;

  rop = caml_alloc_custom (&mpfr_ops, sizeof (mpfr_t), 0, 1);
  mpfr_init2 (Mpfr_val (rop), Int_val (prec));
  ret = mpfr_mul_d (Mpfr_val (rop), Mpfr_val (op1), Double_val (op2), rnd_val (rnd));

  result = caml_alloc_tuple (2);
  Store_field (result, 0, rop);
  Store_field (result, 1, Val_int (ret));
  CAMLreturn (result);
}

CAMLprim value mpfr_sqr_ml (value prec, value op, value rnd)
{
  CAMLparam3 (prec, op, rnd);
  CAMLlocal2 (rop, result);
  int ret;

  rop = caml_alloc_custom (&mpfr_ops, sizeof (mpfr_t), 0, 1);
  mpfr_init2 (Mpfr_val (rop), Int_val (prec));
  ret = mpfr_sqr (Mpfr_val (rop), Mpfr_val (op), rnd_val (rnd));

  result = caml_alloc_tuple (2);
  Store_field (result, 0, rop);
  Store_field (result, 1, Val_int (ret));
  CAMLreturn (result);
}

CAMLprim value mpfr_div_ml (value prec, value op1, value op2, value rnd)
{
  CAMLparam4 (prec, op1, op2, rnd);
  CAMLlocal2 (rop, result);
  int ret;

  rop = caml_alloc_custom (&mpfr_ops, sizeof (mpfr_t), 0, 1);
  mpfr_init2 (Mpfr_val (rop), Int_val (prec));
  ret = mpfr_div (Mpfr_val (rop), Mpfr_val (op1), Mpfr_val (op2), rnd_val (rnd));

  result = caml_alloc_tuple (2);
  Store_field (result, 0, rop);
  Store_field (result, 1, Val_int (ret));
  CAMLreturn (result);
}

CAMLprim value mpfr_si_div_ml (value prec, value op1, value op2, value rnd)
{
  CAMLparam4 (prec, op1, op2, rnd);
  CAMLlocal2 (rop, result);
  int ret;

  rop = caml_alloc_custom (&mpfr_ops, sizeof (mpfr_t), 0, 1);
  mpfr_init2 (Mpfr_val (rop), Int_val (prec));
  ret = mpfr_si_div (Mpfr_val (rop), Int_val (op1), Mpfr_val (op2), rnd_val (rnd));

  result = caml_alloc_tuple (2);
  Store_field (result, 0, rop);
  Store_field (result, 1, Val_int (ret));
  CAMLreturn (result);
}

CAMLprim value mpfr_div_si_ml (value prec, value op1, value op2, value rnd)
{
  CAMLparam4 (prec, op1, op2, rnd);
  CAMLlocal2 (rop, result);
  int ret;

  rop = caml_alloc_custom (&mpfr_ops, sizeof (mpfr_t), 0, 1);
  mpfr_init2 (Mpfr_val (rop), Int_val (prec));
  ret = mpfr_div_si (Mpfr_val (rop), Mpfr_val (op1), Int_val (op2), rnd_val (rnd));

  result = caml_alloc_tuple (2);
  Store_field (result, 0, rop);
  Store_field (result, 1, Val_int (ret));
  CAMLreturn (result);
}

CAMLprim value mpfr_d_div_ml (value prec, value op1, value op2, value rnd)
{
  CAMLparam4 (prec, op1, op2, rnd);
  CAMLlocal2 (rop, result);
  int ret;

  rop = caml_alloc_custom (&mpfr_ops, sizeof (mpfr_t), 0, 1);
  mpfr_init2 (Mpfr_val (rop), Int_val (prec));
  ret = mpfr_d_div (Mpfr_val (rop), Double_val (op1), Mpfr_val (op2), rnd_val (rnd));

  result = caml_alloc_tuple (2);
  Store_field (result, 0, rop);
  Store_field (result, 1, Val_int (ret));
  CAMLreturn (result);
}

CAMLprim value mpfr_div_d_ml (value prec, value op1, value op2, value rnd)
{
  CAMLparam4 (prec, op1, op2, rnd);
  CAMLlocal2 (rop, result);
  int ret;

  rop = caml_alloc_custom (&mpfr_ops, sizeof (mpfr_t), 0, 1);
  mpfr_init2 (Mpfr_val (rop), Int_val (prec));
  ret = mpfr_div_d (Mpfr_val (rop), Mpfr_val (op1), Double_val (op2), rnd_val (rnd));

  result = caml_alloc_tuple (2);
  Store_field (result, 0, rop);
  Store_field (result, 1, Val_int (ret));
  CAMLreturn (result);
}

CAMLprim value mpfr_sqrt_ml (value prec, value op, value rnd)
{
  CAMLparam3 (prec, op, rnd);
  CAMLlocal2 (rop, result);
  int ret;

  rop = caml_alloc_custom (&mpfr_ops, sizeof (mpfr_t), 0, 1);
  mpfr_init2 (Mpfr_val (rop), Int_val (prec));
  ret = mpfr_sqrt (Mpfr_val (rop), Mpfr_val (op), rnd_val (rnd));

  result = caml_alloc_tuple (2);
  Store_field (result, 0, rop);
  Store_field (result, 1, Val_int (ret));
  CAMLreturn (result);
}

CAMLprim value mpfr_sqrt_ui_ml (value prec, value op, value rnd)
{
  CAMLparam3 (prec, op, rnd);
  CAMLlocal2 (rop, result);
  int ret;

  if (Int_val (op) < 0)
    caml_failwith(__FUNCTION__);

  rop = caml_alloc_custom (&mpfr_ops, sizeof (mpfr_t), 0, 1);
  mpfr_init2 (Mpfr_val (rop), Int_val (prec));
  ret = mpfr_sqrt_ui (Mpfr_val (rop), Int_val (op), rnd_val (rnd));

  result = caml_alloc_tuple (2);
  Store_field (result, 0, rop);
  Store_field (result, 1, Val_int (ret));
  CAMLreturn (result);
}

CAMLprim value mpfr_rec_sqrt_ml (value prec, value op, value rnd)
{
  CAMLparam3 (prec, op, rnd);
  CAMLlocal2 (rop, result);
  int ret;

  rop = caml_alloc_custom (&mpfr_ops, sizeof (mpfr_t), 0, 1);
  mpfr_init2 (Mpfr_val (rop), Int_val (prec));
  ret = mpfr_rec_sqrt (Mpfr_val (rop), Mpfr_val (op), rnd_val (rnd));

  result = caml_alloc_tuple (2);
  Store_field (result, 0, rop);
  Store_field (result, 1, Val_int (ret));
  CAMLreturn (result);
}

CAMLprim value mpfr_cbrt_ml (value prec, value op, value rnd)
{
  CAMLparam3 (prec, op, rnd);
  CAMLlocal2 (rop, result);
  int ret;

  rop = caml_alloc_custom (&mpfr_ops, sizeof (mpfr_t), 0, 1);
  mpfr_init2 (Mpfr_val (rop), Int_val (prec));
  ret = mpfr_cbrt (Mpfr_val (rop), Mpfr_val (op), rnd_val (rnd));

  result = caml_alloc_tuple (2);
  Store_field (result, 0, rop);
  Store_field (result, 1, Val_int (ret));
  CAMLreturn (result);
}

CAMLprim value mpfr_root_ml (value prec, value op, value k, value rnd)
{
  CAMLparam4 (prec, op, k, rnd);
  CAMLlocal2 (rop, result);
  int ret;

  if (Int_val (k) < 0)
    caml_failwith(__FUNCTION__);

  rop = caml_alloc_custom (&mpfr_ops, sizeof (mpfr_t), 0, 1);
  mpfr_init2 (Mpfr_val (rop), Int_val (prec));
  ret = mpfr_root (Mpfr_val (rop), Mpfr_val (op), Int_val (k), rnd_val (rnd));

  result = caml_alloc_tuple (2);
  Store_field (result, 0, rop);
  Store_field (result, 1, Val_int (ret));
  CAMLreturn (result);
}

CAMLprim value mpfr_pow_ml (value prec, value op1, value op2, value rnd)
{
  CAMLparam4 (prec, op1, op2, rnd);
  CAMLlocal2 (rop, result);
  int ret;

  rop = caml_alloc_custom (&mpfr_ops, sizeof (mpfr_t), 0, 1);
  mpfr_init2 (Mpfr_val (rop), Int_val (prec));
  ret = mpfr_pow (Mpfr_val (rop), Mpfr_val (op1), Mpfr_val (op2), rnd_val (rnd));

  result = caml_alloc_tuple (2);
  Store_field (result, 0, rop);
  Store_field (result, 1, Val_int (ret));
  CAMLreturn (result);
}

CAMLprim value mpfr_pow_si_ml (value prec, value op1, value op2, value rnd)
{
  CAMLparam4 (prec, op1, op2, rnd);
  CAMLlocal2 (rop, result);
  int ret;

  rop = caml_alloc_custom (&mpfr_ops, sizeof (mpfr_t), 0, 1);
  mpfr_init2 (Mpfr_val (rop), Int_val (prec));
  ret = mpfr_pow_si (Mpfr_val (rop), Mpfr_val (op1), Int_val (op2), rnd_val (rnd));

  result = caml_alloc_tuple (2);
  Store_field (result, 0, rop);
  Store_field (result, 1, Val_int (ret));
  CAMLreturn (result);
}

CAMLprim value mpfr_neg_ml (value prec, value op, value rnd)
{
  CAMLparam3 (prec, op, rnd);
  CAMLlocal2 (rop, result);
  int ret;

  rop = caml_alloc_custom (&mpfr_ops, sizeof (mpfr_t), 0, 1);
  mpfr_init2 (Mpfr_val (rop), Int_val (prec));
  ret = mpfr_neg (Mpfr_val (rop), Mpfr_val (op), rnd_val (rnd));

  result = caml_alloc_tuple (2);
  Store_field (result, 0, rop);
  Store_field (result, 1, Val_int (ret));
  CAMLreturn (result);
}

CAMLprim value mpfr_abs_ml (value prec, value op, value rnd)
{
  CAMLparam3 (prec, op, rnd);
  CAMLlocal2 (rop, result);
  int ret;

  rop = caml_alloc_custom (&mpfr_ops, sizeof (mpfr_t), 0, 1);
  mpfr_init2 (Mpfr_val (rop), Int_val (prec));
  ret = mpfr_abs (Mpfr_val (rop), Mpfr_val (op), rnd_val (rnd));

  result = caml_alloc_tuple (2);
  Store_field (result, 0, rop);
  Store_field (result, 1, Val_int (ret));
  CAMLreturn (result);
}

CAMLprim value mpfr_dim_ml (value prec, value op1, value op2, value rnd)
{
  CAMLparam4 (prec, op1, op2, rnd);
  CAMLlocal2 (rop, result);
  int ret;

  rop = caml_alloc_custom (&mpfr_ops, sizeof (mpfr_t), 0, 1);
  mpfr_init2 (Mpfr_val (rop), Int_val (prec));
  ret = mpfr_dim (Mpfr_val (rop), Mpfr_val (op1), Mpfr_val (op2), rnd_val (rnd));

  result = caml_alloc_tuple (2);
  Store_field (result, 0, rop);
  Store_field (result, 1, Val_int (ret));
  CAMLreturn (result);
}

CAMLprim value mpfr_mul_2si_ml (value prec, value op1, value op2, value rnd)
{
  CAMLparam4 (prec, op1, op2, rnd);
  CAMLlocal2 (rop, result);
  int ret;

  rop = caml_alloc_custom (&mpfr_ops, sizeof (mpfr_t), 0, 1);
  mpfr_init2 (Mpfr_val (rop), Int_val (prec));
  ret = mpfr_mul_2si (Mpfr_val (rop), Mpfr_val (op1), Int_val (op2), rnd_val (rnd));

  result = caml_alloc_tuple (2);
  Store_field (result, 0, rop);
  Store_field (result, 1, Val_int (ret));
  CAMLreturn (result);
}

CAMLprim value mpfr_div_2si_ml (value prec, value op1, value op2, value rnd)
{
  CAMLparam4 (prec, op1, op2, rnd);
  CAMLlocal2 (rop, result);
  int ret;

  rop = caml_alloc_custom (&mpfr_ops, sizeof (mpfr_t), 0, 1);
  mpfr_init2 (Mpfr_val (rop), Int_val (prec));
  ret = mpfr_div_2si (Mpfr_val (rop), Mpfr_val (op1), Int_val (op2), rnd_val (rnd));

  result = caml_alloc_tuple (2);
  Store_field (result, 0, rop);
  Store_field (result, 1, Val_int (ret));
  CAMLreturn (result);
}

CAMLprim value mpfr_cmp_ml (value op1, value op2)
{
  CAMLparam2 (op1, op2);
  CAMLreturn (Val_int (mpfr_cmp (Mpfr_val (op1), Mpfr_val (op2))));
}

CAMLprim value mpfr_cmp_int_ml (value op1, value op2)
{
  CAMLparam2 (op1, op2);
  CAMLreturn (Val_int (mpfr_cmp_si (Mpfr_val (op1), Int_val (op2))));
}

CAMLprim value mpfr_cmp_float_ml (value op1, value op2)
{
  CAMLparam2 (op1, op2);
  CAMLreturn (Val_int (mpfr_cmp_d (Mpfr_val (op1), Double_val (op2))));
}

CAMLprim value mpfr_cmp_si_2exp_ml (value op1, value op2, value exp)
{
  CAMLparam3 (op1, op2, exp);
  CAMLreturn (Val_int (mpfr_cmp_si_2exp (Mpfr_val (op1), Int_val (op2), Int_val (exp))));
}

CAMLprim value mpfr_cmpabs_ml (value op1, value op2)
{
  CAMLparam2 (op1, op2);
  CAMLreturn (Val_int (mpfr_cmp_abs (Mpfr_val (op1), Mpfr_val (op2))));
}

CAMLprim value mpfr_nan_p_ml (value op)
{
  CAMLparam1 (op);
  CAMLreturn (Val_int (mpfr_nan_p (Mpfr_val (op))));
}

CAMLprim value mpfr_inf_p_ml (value op)
{
  CAMLparam1 (op);
  CAMLreturn (Val_int (mpfr_inf_p (Mpfr_val (op))));
}

CAMLprim value mpfr_number_p_ml (value op)
{
  CAMLparam1 (op);
  CAMLreturn (Val_int (mpfr_number_p (Mpfr_val (op))));
}

CAMLprim value mpfr_zero_p_ml (value op)
{
  CAMLparam1 (op);
  CAMLreturn (Val_int (mpfr_zero_p (Mpfr_val (op))));
}

CAMLprim value mpfr_regular_p_ml (value op)
{
  CAMLparam1 (op);
  CAMLreturn (Val_int (mpfr_regular_p (Mpfr_val (op))));
}

CAMLprim value mpfr_sgn_ml (value op)
{
  CAMLparam1 (op);
  CAMLreturn (Val_int (mpfr_sgn (Mpfr_val (op))));
}

CAMLprim value mpfr_greater_p_ml (value op1, value op2)
{
  CAMLparam2 (op1, op2);
  CAMLreturn (Val_int (mpfr_greater_p (Mpfr_val (op1), Mpfr_val (op2))));
}

CAMLprim value mpfr_greaterequal_p_ml (value op1, value op2)
{
  CAMLparam2 (op1, op2);
  CAMLreturn (Val_int (mpfr_greaterequal_p (Mpfr_val (op1), Mpfr_val (op2))));
}

CAMLprim value mpfr_less_p_ml (value op1, value op2)
{
  CAMLparam2 (op1, op2);
  CAMLreturn (Val_int (mpfr_less_p (Mpfr_val (op1), Mpfr_val (op2))));
}

CAMLprim value mpfr_lessequal_p_ml (value op1, value op2)
{
  CAMLparam2 (op1, op2);
  CAMLreturn (Val_int (mpfr_lessequal_p (Mpfr_val (op1), Mpfr_val (op2))));
}

CAMLprim value mpfr_equal_p_ml (value op1, value op2)
{
  CAMLparam2 (op1, op2);
  CAMLreturn (Val_int (mpfr_equal_p (Mpfr_val (op1), Mpfr_val (op2))));
}

CAMLprim value mpfr_lessgreater_p_ml (value op1, value op2)
{
  CAMLparam2 (op1, op2);
  CAMLreturn (Val_int (mpfr_lessgreater_p (Mpfr_val (op1), Mpfr_val (op2))));
}

CAMLprim value mpfr_unordered_p_ml (value op1, value op2)
{
  CAMLparam2 (op1, op2);
  CAMLreturn (Val_int (mpfr_unordered_p (Mpfr_val (op1), Mpfr_val (op2))));
}

static int custom_compare (value v1, value v2)
{
  return mpfr_cmp (Mpfr_val (v1), Mpfr_val (v2));
}
