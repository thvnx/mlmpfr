#include "mlmpfr_stubs.h"

CAMLprim value caml_mpfr_prec_min ()
{
  CAMLparam0 ();
  CAMLreturn (Val_int (MPFR_PREC_MIN));
}

CAMLprim value caml_mpfr_prec_max ()
{
  CAMLparam0 ();
  CAMLreturn (Val_int (MPFR_PREC_MAX));
}

/****************************/
/* Initialization Functions */
/****************************/

CAMLprim value caml_mpfr_init2 (value prec)
{
  CAMLparam1 (prec);
  CAMLlocal1 (rop);

  rop = caml_alloc_custom (&mpfr_ops, sizeof (mpfr_t), 0, 1);
  mpfr_init2 (MPFR_val (rop), (mpfr_prec_t) Int_val (prec));

  CAMLreturn (rop);
}

CAMLprim value caml_mpfr_inits2 (value prec, value n)
{
  CAMLparam2 (prec, n);
  CAMLlocal2 (list, tmp);

  if (Int_val (n) <= 0) // if n is zero, return empty list
    CAMLreturn (Val_int (0));

  // build a list of size n
  list = caml_alloc (2, 0);
  Store_field (list, 0, caml_mpfr_init2 (prec));
  Store_field (list, 1, Val_int(0));
  for (int i = 1; i < Int_val (n); i++)
    {
      tmp = caml_alloc (2, 0);
      Store_field (tmp, 0, caml_mpfr_init2 (prec));
      Store_field (tmp, 1, list);
      list = tmp;
    }

  CAMLreturn (list);
}

CAMLprim value caml_mpfr_clear (value op)
{
  CAMLparam1 (op);
  mpfr_clear (MPFR_val (op));
  CAMLreturn (Val_unit);
}

void custom_finalize (value op)
{
  mpfr_clear (MPFR_val (op));
}

CAMLprim value caml_mpfr_set_default_prec (value prec)
{
  CAMLparam1 (prec);
  mpfr_set_default_prec (Int_val (prec));
  CAMLreturn (Val_unit);
}

CAMLprim value caml_mpfr_get_default_prec ()
{
  CAMLparam0 ();
  mpfr_prec_t prec = mpfr_get_default_prec ();
  CAMLreturn (Val_int (prec));
}

CAMLprim value caml_mpfr_set_prec (value op, value prec)
{
  CAMLparam2 (op, prec);
  mpfr_set_prec (MPFR_val (op), Int_val (prec));
  CAMLreturn (Val_unit);
}

CAMLprim value caml_mpfr_get_prec (value op)
{
  CAMLparam1 (op);
  CAMLreturn (Val_int (mpfr_get_prec (MPFR_val (op))));
}

/************************/
/* Assignment Functions */
/************************/

CAMLprim value caml_mpfr_set (value rop, value op, value rnd)
{
  CAMLparam3 (rop, op, rnd);
  CAMLreturn (Val_int (mpfr_set (MPFR_val (rop), MPFR_val (op),
				 rnd_val (rnd))));
}

CAMLprim value caml_mpfr_set_si (value rop, value op, value rnd)
{
  CAMLparam3 (rop, op, rnd);
  CAMLreturn (Val_int (mpfr_set_si (MPFR_val (rop), SI_val (op),
				    rnd_val (rnd))));
}

CAMLprim value caml_mpfr_set_d (value rop, value op, value rnd)
{
  CAMLparam3 (rop, op, rnd);
  CAMLreturn (Val_int (mpfr_set_d (MPFR_val (rop), DBL_val (op),
				   rnd_val (rnd))));
}

CAMLprim value caml_mpfr_set_str (value rop, value op, value base, value rnd)
{
  CAMLparam4 (rop, op, base, rnd);
  CAMLreturn (Val_int (mpfr_set_str (MPFR_val (rop), String_val (op),
				     Int_val (base), rnd_val (rnd))));
}

CAMLprim value caml_mpfr_strtofr (value rop, value op, value base, value rnd)
{
  CAMLparam4 (rop, op, base, rnd);
  CAMLreturn (Val_int (mpfr_strtofr (MPFR_val (rop), String_val (op), NULL,
				     Int_val (base), rnd_val (rnd))));
}

CAMLprim value caml_mpfr_set_nan (value rop)
{
  CAMLparam1 (rop);
  mpfr_set_nan (MPFR_val (rop));
  CAMLreturn (Val_unit);
}

CAMLprim value caml_mpfr_set_inf (value rop, value sign)
{
  CAMLparam2 (rop, sign);
  mpfr_set_inf (MPFR_val (rop), Int_val (sign));
  CAMLreturn (Val_unit);
}

CAMLprim value caml_mpfr_set_zero (value rop, value sign)
{
  CAMLparam2 (rop, sign);
  mpfr_set_zero (MPFR_val (rop), Int_val (sign));
  CAMLreturn (Val_unit);
}

CAMLprim value caml_mpfr_swap (value op1, value op2)
{
  CAMLparam2 (op1, op2);
  mpfr_swap (MPFR_val (op1), MPFR_val (op2));
  CAMLreturn (Val_unit);
}

/***********************************************************************/
/* Combined Initialization and Assignment Functions (a functional way) */
/***********************************************************************/

CAMLprim value caml_mpfr_init_set_mpfr (value prec, value op, value rnd)
{
  CAMLparam0 ();
  CAMLlocal2 (rop, ter);

  rop = caml_mpfr_init2 (prec);
  ter = caml_mpfr_set (rop, op, rnd);

  CAMLreturn (caml_tuple2 (rop, ter));
}

CAMLprim value caml_mpfr_init_set_si (value prec, value op, value rnd)
{
  CAMLparam0 ();
  CAMLlocal2 (rop, ter);

  rop = caml_mpfr_init2 (prec);
  ter = caml_mpfr_set_si (rop, op, rnd);

  CAMLreturn (caml_tuple2 (rop, ter));
}

CAMLprim value caml_mpfr_init_set_d (value prec, value op, value rnd)
{
  CAMLparam0 ();
  CAMLlocal2 (rop, ter);

  rop = caml_mpfr_init2 (prec);
  ter = caml_mpfr_set_d (rop, op, rnd);

  CAMLreturn (caml_tuple2 (rop, ter));
}

CAMLprim value caml_mpfr_init_set_str (value prec, value str, value base, value rnd)
{
  CAMLparam0 ();
  CAMLlocal2 (rop, ter);

  rop = caml_mpfr_init2 (prec);
  ter = caml_mpfr_strtofr (rop, str, base, rnd);

  CAMLreturn (caml_tuple2 (rop, ter));
}

CAMLprim value caml_mpfr_init_set_nan (value prec)
{
  CAMLparam0 ();
  CAMLlocal1 (rop);

  rop = caml_mpfr_init2 (prec);
  caml_mpfr_set_nan (rop);

  CAMLreturn (rop);
}

CAMLprim value caml_mpfr_init_set_inf (value prec, value sign)
{
  CAMLparam0 ();
  CAMLlocal1 (rop);

  rop = caml_mpfr_init2 (prec);
  caml_mpfr_set_inf (rop, sign);

  CAMLreturn (rop);
}

CAMLprim value caml_mpfr_init_set_zero (value prec, value sign)
{
  CAMLparam0 ();
  CAMLlocal1 (rop);

  rop = caml_mpfr_init2 (prec);
  caml_mpfr_set_zero (rop, sign);

  CAMLreturn (rop);
}

/************************/
/* Conversion Functions */
/************************/

CAMLprim value caml_mpfr_get_d (value op, value rnd)
{
  CAMLparam2 (op, rnd);
  CAMLreturn (caml_copy_double (mpfr_get_d (MPFR_val (op), rnd_val (rnd))));
}

CAMLprim value caml_mpfr_get_si (value op, value rnd)
{
  CAMLparam2 (op, rnd);
  CAMLreturn (Val_int (mpfr_get_si (MPFR_val (op), rnd_val (rnd))));
}

CAMLprim value mpfr_get_d_2exp_ml (value op, value rnd)
{
  CAMLparam2 (op, rnd);
  long *exp;

  double dv = mpfr_get_d_2exp (exp, MPFR_val (op), rnd_val (rnd));

  CAMLreturn (caml_tuple2 (caml_copy_double (dv), Val_int (&exp)));
}

CAMLprim value caml_mpfr_frexp (value prec, value op, value rnd)
{
  CAMLparam2 (op, rnd);
  CAMLlocal1 (rop);
  mpfr_exp_t *exp;

  rop = caml_mpfr_init2 (prec);
  mpfr_frexp (exp, MPFR_val (rop), MPFR_val (op), rnd_val (rnd));

  CAMLreturn (caml_tuple2 (rop, Val_int (&exp)));
}

CAMLprim value caml_mpfr_get_str (value base, value n, value op, value rnd)
{
  CAMLparam4 (base, n, op, rnd);
  CAMLlocal1 (result);
  char *ret;
  mpfr_exp_t expptr;

  ret = mpfr_get_str (NULL, &expptr, Int_val (base), Int_val (n), MPFR_val (op),
		      rnd_val (rnd));

  CAMLreturn (caml_tuple2 ( caml_copy_string (ret), Val_int (expptr)));
}

CAMLprim value caml_mpfr_fits_si_p (value op, value rnd)
{
  CAMLparam2 (op, rnd);
  CAMLreturn (Val_bool (mpfr_fits_sint_p (MPFR_val (op), rnd_val (rnd))));
}

/******************************/
/* Basic Arithmetic Functions */
/******************************/

CAMLprim value caml_mpfr_add (value prec, value op1, value op2, value rnd)
{
  CAMLparam3 (op1, op2, rnd);
  CAMLlocal1 (rop);
  int ter;

  rop = caml_mpfr_init2 (prec);
  ter = mpfr_add (MPFR_val (rop), MPFR_val (op1), MPFR_val (op2), rnd_val (rnd));

  CAMLreturn (caml_tuple2 (rop, Val_int (ter)));
}

CAMLprim value caml_mpfr_add_si (value prec, value op1, value op2, value rnd)
{
  CAMLparam3 (op1, op2, rnd);
  CAMLlocal1 (rop);
  int ter;

  rop = caml_mpfr_init2 (prec);
  ter = mpfr_add_si (MPFR_val (rop), MPFR_val (op1), SI_val (op2), rnd_val (rnd));

  CAMLreturn (caml_tuple2 (rop, Val_int (ter)));
}

CAMLprim value caml_mpfr_add_d (value prec, value op1, value op2, value rnd)
{
  CAMLparam3 (op1, op2, rnd);
  CAMLlocal1 (rop);
  int ter;

  rop = caml_mpfr_init2 (prec);
  ter = mpfr_add_d (MPFR_val (rop), MPFR_val (op1), DBL_val (op2), rnd_val (rnd));

  CAMLreturn (caml_tuple2 (rop, Val_int (ter)));
}

CAMLprim value caml_mpfr_sub (value prec, value op1, value op2, value rnd)
{
  CAMLparam3 (op1, op2, rnd);
  CAMLlocal1 (rop);
  int ter;

  rop = caml_mpfr_init2 (prec);
  ter = mpfr_sub (MPFR_val (rop), MPFR_val (op1), MPFR_val (op2), rnd_val (rnd));

  CAMLreturn (caml_tuple2 (rop, Val_int (ter)));
}

CAMLprim value caml_mpfr_si_sub (value prec, value op1, value op2, value rnd)
{
  CAMLparam3 (op1, op2, rnd);
  CAMLlocal1 (rop);
  int ter;

  rop = caml_mpfr_init2 (prec);
  ter = mpfr_si_sub (MPFR_val (rop), SI_val (op1), MPFR_val (op2), rnd_val (rnd));

  CAMLreturn (caml_tuple2 (rop, Val_int (ter)));
}

CAMLprim value caml_mpfr_sub_si (value prec, value op1, value op2, value rnd)
{
  CAMLparam3 (op1, op2, rnd);
  CAMLlocal1 (rop);
  int ter;

  rop = caml_mpfr_init2 (prec);
  ter = mpfr_sub_si (MPFR_val (rop), MPFR_val (op1), SI_val (op2), rnd_val (rnd));

  CAMLreturn (caml_tuple2 (rop, Val_int (ter)));
}

CAMLprim value caml_mpfr_d_sub (value prec, value op1, value op2, value rnd)
{
  CAMLparam3 (op1, op2, rnd);
  CAMLlocal1 (rop);
  int ter;

  rop = caml_mpfr_init2 (prec);
  ter = mpfr_d_sub (MPFR_val (rop), DBL_val (op1), MPFR_val (op2), rnd_val (rnd));

  CAMLreturn (caml_tuple2 (rop, Val_int (ter)));
}

CAMLprim value caml_mpfr_sub_d (value prec, value op1, value op2, value rnd)
{
  CAMLparam3 (op1, op2, rnd);
  CAMLlocal1 (rop);
  int ter;

  rop = caml_mpfr_init2 (prec);
  ter = mpfr_sub_d (MPFR_val (rop), MPFR_val (op1), DBL_val (op2), rnd_val (rnd));

  CAMLreturn (caml_tuple2 (rop, Val_int (ter)));
}

CAMLprim value caml_mpfr_mul (value prec, value op1, value op2, value rnd)
{
  CAMLparam3 (op1, op2, rnd);
  CAMLlocal1 (rop);
  int ter;

  rop = caml_mpfr_init2 (prec);
  ter = mpfr_mul (MPFR_val (rop), MPFR_val (op1), MPFR_val (op2), rnd_val (rnd));

  CAMLreturn (caml_tuple2 (rop, Val_int (ter)));
}

CAMLprim value caml_mpfr_mul_si (value prec, value op1, value op2, value rnd)
{
  CAMLparam3 (op1, op2, rnd);
  CAMLlocal1 (rop);
  int ter;

  rop = caml_mpfr_init2 (prec);
  ter = mpfr_mul_si (MPFR_val (rop), MPFR_val (op1), SI_val (op2), rnd_val (rnd));

  CAMLreturn (caml_tuple2 (rop, Val_int (ter)));
}

CAMLprim value caml_mpfr_mul_d (value prec, value op1, value op2, value rnd)
{
  CAMLparam3 (op1, op2, rnd);
  CAMLlocal1 (rop);
  int ter;

  rop = caml_mpfr_init2 (prec);
  ter = mpfr_mul_d (MPFR_val (rop), MPFR_val (op1), DBL_val (op2), rnd_val (rnd));

  CAMLreturn (caml_tuple2 (rop, Val_int (ter)));
}

CAMLprim value caml_mpfr_sqr (value prec, value op, value rnd)
{
  CAMLparam2 (op, rnd);
  CAMLlocal1 (rop);
  int ter;

  rop = caml_mpfr_init2 (prec);
  ter = mpfr_sqr (MPFR_val (rop), MPFR_val (op), rnd_val (rnd));

  CAMLreturn (caml_tuple2 (rop, Val_int (ter)));
}

CAMLprim value caml_mpfr_div (value prec, value op1, value op2, value rnd)
{
  CAMLparam3 (op1, op2, rnd);
  CAMLlocal1 (rop);
  int ter;

  rop = caml_mpfr_init2 (prec);
  ter = mpfr_div (MPFR_val (rop), MPFR_val (op1), MPFR_val (op2), rnd_val (rnd));

  CAMLreturn (caml_tuple2 (rop, Val_int (ter)));
}

CAMLprim value caml_mpfr_si_div (value prec, value op1, value op2, value rnd)
{
  CAMLparam3 (op1, op2, rnd);
  CAMLlocal1 (rop);
  int ter;

  rop = caml_mpfr_init2 (prec);
  ter = mpfr_si_div (MPFR_val (rop), SI_val (op1), MPFR_val (op2), rnd_val (rnd));

  CAMLreturn (caml_tuple2 (rop, Val_int (ter)));
}

CAMLprim value caml_mpfr_div_si (value prec, value op1, value op2, value rnd)
{
  CAMLparam3 (op1, op2, rnd);
  CAMLlocal1 (rop);
  int ter;

  rop = caml_mpfr_init2 (prec);
  ter = mpfr_div_si (MPFR_val (rop), MPFR_val (op1), SI_val (op2), rnd_val (rnd));

  CAMLreturn (caml_tuple2 (rop, Val_int (ter)));
}

CAMLprim value caml_mpfr_d_div (value prec, value op1, value op2, value rnd)
{
  CAMLparam3 (op1, op2, rnd);
  CAMLlocal1 (rop);
  int ter;

  rop = caml_mpfr_init2 (prec);
  ter = mpfr_d_div (MPFR_val (rop), DBL_val (op1), MPFR_val (op2), rnd_val (rnd));

  CAMLreturn (caml_tuple2 (rop, Val_int (ter)));
}

CAMLprim value caml_mpfr_div_d (value prec, value op1, value op2, value rnd)
{
  CAMLparam3 (op1, op2, rnd);
  CAMLlocal1 (rop);
  int ter;

  rop = caml_mpfr_init2 (prec);
  ter = mpfr_div_d (MPFR_val (rop), MPFR_val (op1), DBL_val (op2), rnd_val (rnd));

  CAMLreturn (caml_tuple2 (rop, Val_int (ter)));
}

CAMLprim value caml_mpfr_sqrt (value prec, value op, value rnd)
{
  CAMLparam2 (op, rnd);
  CAMLlocal1 (rop);
  int ter;

  rop = caml_mpfr_init2 (prec);
  ter = mpfr_sqrt (MPFR_val (rop), MPFR_val (op), rnd_val (rnd));

  CAMLreturn (caml_tuple2 (rop, Val_int (ter)));
}

CAMLprim value caml_mpfr_sqrt_ui (value prec, value op, value rnd)
{
  CAMLparam2 (op, rnd);
  CAMLlocal1 (rop);
  int ter;

  if (SI_val (op) < 0)
    caml_failwith(__FUNCTION__);

  rop = caml_mpfr_init2 (prec);
  ter = mpfr_sqrt_ui (MPFR_val (rop), UI_val (op), rnd_val (rnd));

  CAMLreturn (caml_tuple2 (rop, Val_int (ter)));
}

CAMLprim value caml_mpfr_rec_sqrt (value prec, value op, value rnd)
{
  CAMLparam2 (op, rnd);
  CAMLlocal1 (rop);
  int ter;

  rop = caml_mpfr_init2 (prec);
  ter = mpfr_rec_sqrt (MPFR_val (rop), MPFR_val (op), rnd_val (rnd));

  CAMLreturn (caml_tuple2 (rop, Val_int (ter)));
}

CAMLprim value caml_mpfr_cbrt (value prec, value op, value rnd)
{
  CAMLparam2 (op, rnd);
  CAMLlocal1 (rop);
  int ter;

  rop = caml_mpfr_init2 (prec);
  ter = mpfr_cbrt (MPFR_val (rop), MPFR_val (op), rnd_val (rnd));

  CAMLreturn (caml_tuple2 (rop, Val_int (ter)));
}

CAMLprim value caml_mpfr_root (value prec, value op, value k, value rnd)
{
  CAMLparam3 (op, k, rnd);
  CAMLlocal1 (rop);
  int ter;

  if (SI_val (k) < 0)
    caml_failwith(__FUNCTION__);

  rop = caml_mpfr_init2 (prec);
  ter = mpfr_root (MPFR_val (rop), MPFR_val (op), UI_val (k), rnd_val (rnd));

  CAMLreturn (caml_tuple2 (rop, Val_int (ter)));
}

CAMLprim value caml_mpfr_pow (value prec, value op1, value op2, value rnd)
{
  CAMLparam3 (op1, op2, rnd);
  CAMLlocal1 (rop);
  int ter;

  rop = caml_mpfr_init2 (prec);
  ter = mpfr_pow (MPFR_val (rop), MPFR_val (op1), MPFR_val (op2), rnd_val (rnd));

  CAMLreturn (caml_tuple2 (rop, Val_int (ter)));
}

CAMLprim value caml_mpfr_pow_si (value prec, value op1, value op2, value rnd)
{
  CAMLparam3 (op1, op2, rnd);
  CAMLlocal1 (rop);
  int ter;

  rop = caml_mpfr_init2 (prec);
  ter = mpfr_pow_si (MPFR_val (rop), MPFR_val (op1), SI_val (op2), rnd_val (rnd));

  CAMLreturn (caml_tuple2 (rop, Val_int (ter)));
}

CAMLprim value caml_mpfr_neg (value prec, value op, value rnd)
{
  CAMLparam2 (op, rnd);
  CAMLlocal1 (rop);
  int ter;

  rop = caml_mpfr_init2 (prec);
  ter = mpfr_neg (MPFR_val (rop), MPFR_val (op), rnd_val (rnd));

  CAMLreturn (caml_tuple2 (rop, Val_int (ter)));
}

CAMLprim value caml_mpfr_abs (value prec, value op, value rnd)
{
  CAMLparam2 (op, rnd);
  CAMLlocal1 (rop);
  int ter;

  rop = caml_mpfr_init2 (prec);
  ter = mpfr_abs (MPFR_val (rop), MPFR_val (op), rnd_val (rnd));

  CAMLreturn (caml_tuple2 (rop, Val_int (ter)));
}

CAMLprim value caml_mpfr_dim (value prec, value op1, value op2, value rnd)
{
  CAMLparam3 (op1, op2, rnd);
  CAMLlocal1 (rop);
  int ter;

  rop = caml_mpfr_init2 (prec);
  ter = mpfr_dim (MPFR_val (rop), MPFR_val (op1), MPFR_val (op2), rnd_val (rnd));

  CAMLreturn (caml_tuple2 (rop, Val_int (ter)));
}

CAMLprim value mpfr_mul_2si_ml (value prec, value op1, value op2, value rnd)
{
  CAMLparam3 (op1, op2, rnd);
  CAMLlocal1 (rop);
  int ter;

  rop = caml_mpfr_init2 (prec);
  ter = mpfr_mul_2si (MPFR_val (rop), MPFR_val (op1), SI_val (op2), rnd_val (rnd));

  CAMLreturn (caml_tuple2 (rop, Val_int (ter)));
}

CAMLprim value mpfr_div_2si_ml (value prec, value op1, value op2, value rnd)
{
  CAMLparam3 (op1, op2, rnd);
  CAMLlocal1 (rop);
  int ter;

  rop = caml_mpfr_init2 (prec);
  ter = mpfr_div_2si (MPFR_val (rop), MPFR_val (op1), SI_val (op2), rnd_val (rnd));

  CAMLreturn (caml_tuple2 (rop, Val_int (ter)));
}

/************************/
/* Comparison Functions */
/************************/

CAMLprim value caml_mpfr_cmp (value op1, value op2)
{
  CAMLparam2 (op1, op2);
  CAMLreturn (Val_int (mpfr_cmp (MPFR_val (op1), MPFR_val (op2))));
}

CAMLprim value caml_mpfr_cmp_int (value op1, value op2)
{
  CAMLparam2 (op1, op2);
  CAMLreturn (Val_int (mpfr_cmp_si (MPFR_val (op1), SI_val (op2))));
}

CAMLprim value caml_mpfr_cmp_float (value op1, value op2)
{
  CAMLparam2 (op1, op2);
  CAMLreturn (Val_int (mpfr_cmp_d (MPFR_val (op1), Double_val (op2))));
}

CAMLprim value mpfr_cmp_si_2exp_ml (value op1, value op2, value exp)
{
  CAMLparam3 (op1, op2, exp);
  CAMLreturn (Val_int (mpfr_cmp_si_2exp (MPFR_val (op1), SI_val (op2), EXP_val (exp))));
}

CAMLprim value caml_mpfr_cmpabs (value op1, value op2)
{
  CAMLparam2 (op1, op2);
  CAMLreturn (Val_int (mpfr_cmp_abs (MPFR_val (op1), MPFR_val (op2))));
}

CAMLprim value caml_mpfr_nan_p (value op)
{
  CAMLparam1 (op);
  CAMLreturn (Val_bool (mpfr_nan_p (MPFR_val (op))));
}

CAMLprim value caml_mpfr_inf_p (value op)
{
  CAMLparam1 (op);
  CAMLreturn (Val_bool (mpfr_inf_p (MPFR_val (op))));
}

CAMLprim value caml_mpfr_number_p (value op)
{
  CAMLparam1 (op);
  CAMLreturn (Val_bool (mpfr_number_p (MPFR_val (op))));
}

CAMLprim value caml_mpfr_zero_p (value op)
{
  CAMLparam1 (op);
  CAMLreturn (Val_bool (mpfr_zero_p (MPFR_val (op))));
}

CAMLprim value caml_mpfr_regular_p (value op)
{
  CAMLparam1 (op);
  CAMLreturn (Val_bool (mpfr_regular_p (MPFR_val (op))));
}

CAMLprim value caml_mpfr_sgn (value op)
{
  CAMLparam1 (op);
  CAMLreturn (Val_int (mpfr_sgn (MPFR_val (op))));
}

CAMLprim value caml_mpfr_greater_p (value op1, value op2)
{
  CAMLparam2 (op1, op2);
  CAMLreturn (Val_bool (mpfr_greater_p (MPFR_val (op1), MPFR_val (op2))));
}

CAMLprim value caml_mpfr_greaterequal_p (value op1, value op2)
{
  CAMLparam2 (op1, op2);
  CAMLreturn (Val_bool (mpfr_greaterequal_p (MPFR_val (op1), MPFR_val (op2))));
}

CAMLprim value caml_mpfr_less_p (value op1, value op2)
{
  CAMLparam2 (op1, op2);
  CAMLreturn (Val_bool (mpfr_less_p (MPFR_val (op1), MPFR_val (op2))));
}

CAMLprim value caml_mpfr_lessequal_p (value op1, value op2)
{
  CAMLparam2 (op1, op2);
  CAMLreturn (Val_bool (mpfr_lessequal_p (MPFR_val (op1), MPFR_val (op2))));
}

CAMLprim value caml_mpfr_equal_p (value op1, value op2)
{
  CAMLparam2 (op1, op2);
  CAMLreturn (Val_bool (mpfr_equal_p (MPFR_val (op1), MPFR_val (op2))));
}

CAMLprim value caml_mpfr_lessgreater_p (value op1, value op2)
{
  CAMLparam2 (op1, op2);
  CAMLreturn (Val_bool (mpfr_lessgreater_p (MPFR_val (op1), MPFR_val (op2))));
}

CAMLprim value caml_mpfr_unordered_p (value op1, value op2)
{
  CAMLparam2 (op1, op2);
  CAMLreturn (Val_bool (mpfr_unordered_p (MPFR_val (op1), MPFR_val (op2))));
}

static int custom_compare (value v1, value v2)
{
  return caml_mpfr_cmp (v1, v2);
}

/*********************/
/* Special Functions */
/*********************/

CAMLprim value caml_mpfr_log (value prec, value op, value rnd)
  MPFR_REGULAR_FUNCTION1 (mpfr_log);

CAMLprim value caml_mpfr_log2 (value prec, value op, value rnd)
  MPFR_REGULAR_FUNCTION1 (mpfr_log2);

CAMLprim value caml_mpfr_log10 (value prec, value op, value rnd)
  MPFR_REGULAR_FUNCTION1 (mpfr_log10);

CAMLprim value caml_mpfr_exp (value prec, value op, value rnd)
  MPFR_REGULAR_FUNCTION1 (mpfr_exp);

CAMLprim value caml_mpfr_exp2 (value prec, value op, value rnd)
  MPFR_REGULAR_FUNCTION1 (mpfr_exp2);

CAMLprim value caml_mpfr_exp10 (value prec, value op, value rnd)
  MPFR_REGULAR_FUNCTION1 (mpfr_exp10);

CAMLprim value caml_mpfr_sin (value prec, value op, value rnd)
  MPFR_REGULAR_FUNCTION1 (mpfr_sin);

CAMLprim value caml_mpfr_cos (value prec, value op, value rnd)
  MPFR_REGULAR_FUNCTION1 (mpfr_cos);

CAMLprim value caml_mpfr_tan (value prec, value op, value rnd)
  MPFR_REGULAR_FUNCTION1 (mpfr_tan);

CAMLprim value caml_mpfr_sin_cos (value sprec, value cprec, value op, value rnd)
{
  CAMLparam2 (op, rnd);
  CAMLlocal2 (sop, cop);
  int ret;

  sop = caml_mpfr_init2 (sprec);
  cop = caml_mpfr_init2 (cprec);
  ret = mpfr_sin_cos (MPFR_val (sop), MPFR_val (cop), MPFR_val (op), rnd_val (rnd));

  CAMLreturn (caml_tuple3 (sop, cop, Val_int (ret)));
}

CAMLprim value caml_mpfr_sec (value prec, value op, value rnd)
  MPFR_REGULAR_FUNCTION1 (mpfr_sec);

CAMLprim value caml_mpfr_csc (value prec, value op, value rnd)
  MPFR_REGULAR_FUNCTION1 (mpfr_csc);

CAMLprim value caml_mpfr_cot (value prec, value op, value rnd)
  MPFR_REGULAR_FUNCTION1 (mpfr_cot);

CAMLprim value caml_mpfr_acos (value prec, value op, value rnd)
  MPFR_REGULAR_FUNCTION1 (mpfr_acos);

CAMLprim value caml_mpfr_asin (value prec, value op, value rnd)
  MPFR_REGULAR_FUNCTION1 (mpfr_asin);

CAMLprim value caml_mpfr_atan (value prec, value op, value rnd)
  MPFR_REGULAR_FUNCTION1 (mpfr_atan);

CAMLprim value caml_mpfr_atan2 (value prec, value x, value y, value rnd)
{
  CAMLparam3 (x, y, rnd);
  CAMLlocal1 (rop);
  int ter;

  rop = caml_mpfr_init2 (prec);
  ter = mpfr_atan2 (MPFR_val (rop), MPFR_val (x), MPFR_val (y), rnd_val (rnd));

  CAMLreturn (caml_tuple2 (rop, Int_val (ter)));
}

CAMLprim value caml_mpfr_sinh (value prec, value op, value rnd)
  MPFR_REGULAR_FUNCTION1 (mpfr_sinh);

CAMLprim value caml_mpfr_cosh (value prec, value op, value rnd)
  MPFR_REGULAR_FUNCTION1 (mpfr_cosh);

CAMLprim value caml_mpfr_tanh (value prec, value op, value rnd)
  MPFR_REGULAR_FUNCTION1 (mpfr_tanh);

CAMLprim value caml_mpfr_sinh_cosh (value sprec, value cprec, value op, value rnd)
{
  CAMLparam2 (op, rnd);
  CAMLlocal2 (sop, cop);
  int ret;

  sop = caml_mpfr_init2 (sprec);
  cop = caml_mpfr_init2 (cprec);
  ret = mpfr_sinh_cosh (MPFR_val (sop), MPFR_val (cop), MPFR_val (op), rnd_val (rnd));

  CAMLreturn (caml_tuple3 (sop, cop, Val_int (ret)));
}

CAMLprim value caml_mpfr_sech (value prec, value op, value rnd)
  MPFR_REGULAR_FUNCTION1 (mpfr_sech);

CAMLprim value caml_mpfr_csch (value prec, value op, value rnd)
  MPFR_REGULAR_FUNCTION1 (mpfr_csch);

CAMLprim value caml_mpfr_coth (value prec, value op, value rnd)
  MPFR_REGULAR_FUNCTION1 (mpfr_coth);

CAMLprim value caml_mpfr_acohs (value prec, value op, value rnd)
  MPFR_REGULAR_FUNCTION1 (mpfr_acosh);

CAMLprim value caml_mpfr_asinh (value prec, value op, value rnd)
  MPFR_REGULAR_FUNCTION1 (mpfr_asinh);

CAMLprim value caml_mpfr_atanh (value prec, value op, value rnd)
  MPFR_REGULAR_FUNCTION1 (mpfr_atanh);

CAMLprim value caml_mpfr_fac_ui (value prec, value op, value rnd)
{
  CAMLparam2 (op, rnd);
  CAMLlocal1 (rop);
  int ter;

  if (SI_val (op) < 0)
    caml_failwith(__FUNCTION__);

  rop = caml_mpfr_init2 (prec);
  ter = mpfr_fac_ui (MPFR_val (rop), SI_val (op), rnd_val (rnd));

  CAMLreturn (caml_tuple2 (rop, Val_int (ter)));
}

CAMLprim value caml_mpfr_log1p (value prec, value op, value rnd)
  MPFR_REGULAR_FUNCTION1 (mpfr_log1p);

CAMLprim value caml_mpfr_expm1 (value prec, value op, value rnd)
  MPFR_REGULAR_FUNCTION1 (mpfr_expm1);

CAMLprim value caml_mpfr_eint (value prec, value op, value rnd)
  MPFR_REGULAR_FUNCTION1 (mpfr_eint);

CAMLprim value caml_mpfr_li2 (value prec, value op, value rnd)
  MPFR_REGULAR_FUNCTION1 (mpfr_li2);

CAMLprim value caml_mpfr_gamma (value prec, value op, value rnd)
  MPFR_REGULAR_FUNCTION1 (mpfr_gamma);

CAMLprim value caml_mpfr_lngamma (value prec, value op, value rnd)
  MPFR_REGULAR_FUNCTION1 (mpfr_lngamma);

CAMLprim value caml_mpfr_lgamma (value prec, value op, value rnd)
{
  CAMLparam2 (op, rnd);
  CAMLlocal1 (rop);
  int ter;
  int *signp;

  rop = caml_mpfr_init2 (prec);
  ter = mpfr_lgamma (MPFR_val (rop), signp, MPFR_val (op), rnd_val (rnd));

  CAMLreturn (caml_tuple2 (caml_tuple2 (rop, Val_int (ter)), Val_int (&signp)));
}

CAMLprim value caml_mpfr_digamma (value prec, value op, value rnd)
  MPFR_REGULAR_FUNCTION1 (mpfr_digamma);

CAMLprim value caml_mpfr_zeta (value prec, value op, value rnd)
  MPFR_REGULAR_FUNCTION1 (mpfr_zeta);

CAMLprim value caml_mpfr_zeta_ui (value prec, value op, value rnd)
{
  CAMLparam2 (op, rnd);
  CAMLlocal1 (rop);
  int ter;

  if (SI_val (op) < 0)
    caml_failwith(__FUNCTION__);

  rop = caml_mpfr_init2 (prec);
  ter = mpfr_zeta_ui (MPFR_val (rop), SI_val (op), rnd_val (rnd));

  CAMLreturn (caml_tuple2 (rop, Val_int (ter)));
}

CAMLprim value caml_mpfr_erf (value prec, value op, value rnd)
  MPFR_REGULAR_FUNCTION1 (mpfr_erf);

CAMLprim value caml_mpfr_erfc (value prec, value op, value rnd)
  MPFR_REGULAR_FUNCTION1 (mpfr_erfc);

CAMLprim value caml_mpfr_j0 (value prec, value op, value rnd)
  MPFR_REGULAR_FUNCTION1 (mpfr_j0);

CAMLprim value caml_mpfr_j1 (value prec, value op, value rnd)
  MPFR_REGULAR_FUNCTION1 (mpfr_j1);

CAMLprim value caml_mpfr_jn (value prec, value n, value op, value rnd)
{
  CAMLparam3 (n, op, rnd);
  CAMLlocal1 (rop);
  int ter;

  rop = caml_mpfr_init2 (prec);
  ter = mpfr_jn (MPFR_val (rop), SI_val (n), MPFR_val (op), rnd_val (rnd));

  CAMLreturn (caml_tuple2 (rop, Val_int (ter)));
}

CAMLprim value caml_mpfr_y0 (value prec, value op, value rnd)
  MPFR_REGULAR_FUNCTION1 (mpfr_y0);

CAMLprim value caml_mpfr_y1 (value prec, value op, value rnd)
  MPFR_REGULAR_FUNCTION1 (mpfr_y1);

CAMLprim value caml_mpfr_yn (value prec, value n, value op, value rnd)
{
  CAMLparam3 (n, op, rnd);
  CAMLlocal1 (rop);
  int ter;

  rop = caml_mpfr_init2 (prec);
  ter = mpfr_yn (MPFR_val (rop), SI_val (n), MPFR_val (op), rnd_val (rnd));

  CAMLreturn (caml_tuple2 (rop, Val_int (ter)));
}

CAMLprim value caml_mpfr_fma (value prec, value op1, value op2, value op3, value rnd)
{
  CAMLparam4 (op1, op2, op3, rnd);
  CAMLlocal1 (rop);
  int ter;

  rop = caml_mpfr_init2 (prec);
  ter = mpfr_fma (MPFR_val (rop), MPFR_val (op1), MPFR_val (op2), MPFR_val (op3), rnd_val (rnd));

  CAMLreturn (caml_tuple2 (rop, Val_int (ter)));
}

CAMLprim value caml_mpfr_fms (value prec, value op1, value op2, value op3, value rnd)
{
  CAMLparam4 (op1, op2, op3, rnd);
  CAMLlocal1 (rop);
  int ter;

  rop = caml_mpfr_init2 (prec);
  ter = mpfr_fms (MPFR_val (rop), MPFR_val (op1), MPFR_val (op2), MPFR_val (op3), rnd_val (rnd));

  CAMLreturn (caml_tuple2 (rop, Val_int (ter)));
}

CAMLprim value caml_mpfr_agm (value prec, value op1, value op2, value rnd)
{
  CAMLparam3 (op1, op2, rnd);
  CAMLlocal1 (rop);
  int ter;

  rop = caml_mpfr_init2 (prec);
  ter = mpfr_agm (MPFR_val (rop), MPFR_val (op1), MPFR_val (op2), rnd_val (rnd));

  CAMLreturn (caml_tuple2 (rop, Val_int (ter)));
}

CAMLprim value caml_mpfr_hypot (value prec, value x, value y, value rnd)
{
  CAMLparam3 (x, y, rnd);
  CAMLlocal1 (rop);
  int ter;

  rop = caml_mpfr_init2 (prec);
  ter = mpfr_hypot (MPFR_val (rop), MPFR_val (x), MPFR_val (y), rnd_val (rnd));

  CAMLreturn (caml_tuple2 (rop, Val_int (ter)));
}

CAMLprim value caml_mpfr_ai (value prec, value op, value rnd)
  MPFR_REGULAR_FUNCTION1 (mpfr_ai);

CAMLprim value caml_mpfr_const_log2 (value prec, value rnd)
{
  CAMLparam1 (rnd);
  CAMLlocal1 (rop);
  int ter;

  rop = caml_mpfr_init2 (prec);
  ter = mpfr_const_log2 (MPFR_val (rop), rnd_val (rnd));

  CAMLreturn (caml_tuple2 (rop, Val_int (ter)));
}

CAMLprim value caml_mpfr_const_pi (value prec, value rnd)
{
  CAMLparam1 (rnd);
  CAMLlocal1 (rop);
  int ter;

  rop = caml_mpfr_init2 (prec);
  ter = mpfr_const_pi (MPFR_val (rop), rnd_val (rnd));

  CAMLreturn (caml_tuple2 (rop, Val_int (ter)));
}

CAMLprim value caml_mpfr_const_euler (value prec, value rnd)
{
  CAMLparam1 (rnd);
  CAMLlocal1 (rop);
  int ter;

  rop = caml_mpfr_init2 (prec);
  ter = mpfr_const_euler (MPFR_val (rop), rnd_val (rnd));

  CAMLreturn (caml_tuple2 (rop, Val_int (ter)));
}

CAMLprim value caml_mpfr_const_catalan (value prec, value rnd)
{
  CAMLparam1 (rnd);
  CAMLlocal1 (rop);
  int ter;

  rop = caml_mpfr_init2 (prec);
  ter = mpfr_const_catalan (MPFR_val (rop), rnd_val (rnd));

  CAMLreturn (caml_tuple2 (rop, Val_int (ter)));
}

CAMLprim value caml_mpfr_free_cache (value unit)
{
  CAMLparam1 (unit);
  mpfr_free_cache ();
  CAMLreturn (Val_unit);
}

CAMLprim value caml_mpfr_sum (value prec, value tab, value rnd)
{
  CAMLparam2 (tab, rnd);
  CAMLlocal1 (rop);
  int i, ter;

  rop = caml_mpfr_init2 (prec);
  // compute the size of tab
  int size = 0;
  value tmp = tab;
  while ( Is_block (tab) )
    {
      tab = Field (tab, 1);
      size++;
    }
  tab = tmp;

  mpfr_ptr ptab [size];
  for (i = 0; i < size; i++)
    {
      printf ("%d %d\n", i, Tag_val (tab));

      ptab[i] = MPFR_val (Field (tab, 0));
      tab = Field (tab, 1);
    }

  ter = mpfr_sum (MPFR_val (rop), ptab, size, rnd_val (rnd));

  CAMLreturn (caml_tuple2 (rop, Val_int (ter)));
}

/*******************************************/
/* Integer and Remainder Related Functions */
/*******************************************/

CAMLprim value caml_mpfr_rint (value prec, value op, value rnd)
  MPFR_REGULAR_FUNCTION1 (mpfr_rint);

CAMLprim value caml_mpfr_ceil (value prec, value op)
{
  CAMLparam1 (op);
  CAMLlocal1 (rop);
  int ter;

  rop = caml_mpfr_init2 (prec);
  ter = mpfr_ceil (MPFR_val (rop), MPFR_val (op));

  CAMLreturn (caml_tuple2 (rop, Val_int (ter)));
}

CAMLprim value caml_mpfr_floor (value prec, value op)
{
  CAMLparam1 (op);
  CAMLlocal1 (rop);
  int ter;

  rop = caml_mpfr_init2 (prec);
  ter = mpfr_floor (MPFR_val (rop), MPFR_val (op));

  CAMLreturn (caml_tuple2 (rop, Val_int (ter)));
}

CAMLprim value caml_mpfr_round (value prec, value op)
{
  CAMLparam1 (op);
  CAMLlocal1 (rop);
  int ter;

  rop = caml_mpfr_init2 (prec);
  ter = mpfr_round (MPFR_val (rop), MPFR_val (op));

  CAMLreturn (caml_tuple2 (rop, Val_int (ter)));
}

CAMLprim value caml_mpfr_trunc (value prec, value op)
{
  CAMLparam1 (op);
  CAMLlocal1 (rop);
  int ter;

  rop = caml_mpfr_init2 (prec);
  ter = mpfr_trunc (MPFR_val (rop), MPFR_val (op));

  CAMLreturn (caml_tuple2 (rop, Val_int (ter)));
}

CAMLprim value caml_mpfr_rint_ceil (value prec, value op, value rnd)
  MPFR_REGULAR_FUNCTION1 (mpfr_rint_ceil);

CAMLprim value caml_mpfr_rint_floor (value prec, value op, value rnd)
  MPFR_REGULAR_FUNCTION1 (mpfr_rint_floor);

CAMLprim value caml_mpfr_rint_round (value prec, value op, value rnd)
  MPFR_REGULAR_FUNCTION1 (mpfr_rint_round);

CAMLprim value caml_mpfr_rint_trunc (value prec, value op, value rnd)
  MPFR_REGULAR_FUNCTION1 (mpfr_rint_trunc);

CAMLprim value caml_mpfr_frac (value prec, value op, value rnd)
  MPFR_REGULAR_FUNCTION1 (mpfr_frac);

CAMLprim value caml_mpfr_modf (value iprec, value fprec, value op, value rnd)
{
  CAMLparam2 (op, rnd);
  CAMLlocal2 (iop, fop);
  int ret;

  iop = caml_mpfr_init2 (iprec);
  fop = caml_mpfr_init2 (fprec);
  ret = mpfr_modf (MPFR_val (iop), MPFR_val (fop), MPFR_val (op), rnd_val (rnd));

  CAMLreturn (caml_tuple3 (iop, fop, Val_int (ret)));
}

CAMLprim value caml_mpfr_fmod (value prec, value x, value y, value rnd)
{
  CAMLparam3 (x, y, rnd);
  CAMLlocal1 (rop);
  int ter;

  rop = caml_mpfr_init2 (prec);
  ter = mpfr_fmod (MPFR_val (rop), MPFR_val (x), MPFR_val (y), rnd_val (rnd));

  CAMLreturn (caml_tuple2 (rop, Val_int (ter)));
}

CAMLprim value caml_mpfr_remainder (value prec, value x, value y, value rnd)
{
  CAMLparam3 (x, y, rnd);
  CAMLlocal1 (rop);
  int ter;

  rop = caml_mpfr_init2 (prec);
  ter = mpfr_remainder (MPFR_val (rop), MPFR_val (x), MPFR_val (y), rnd_val (rnd));

  CAMLreturn (caml_tuple2 (rop, Val_int (ter)));
}

CAMLprim value caml_mpfr_remquo (value prec, value x, value y, value rnd)
{
  CAMLparam3 (x, y, rnd);
  CAMLlocal1 (rop);
  int ter;
  long* q;

  rop = caml_mpfr_init2 (prec);
  ter = mpfr_remquo (MPFR_val (rop), q, MPFR_val (x), MPFR_val (y), rnd_val (rnd));

  CAMLreturn (caml_tuple2 (caml_tuple2 (rop, Val_int (ter)), Val_int (q)));
}

CAMLprim value caml_integer_p (value op)
{
  CAMLparam1 (op);
  CAMLreturn (Val_bool (mpfr_integer_p (MPFR_val (op))));
}

/******************************/
/* Rounding Related Functions */
/******************************/

CAMLprim value caml_mpfr_set_default_rounding_mode (value rnd)
{
  CAMLparam1 (rnd);
  mpfr_set_default_rounding_mode (rnd_val (rnd));
  CAMLreturn (Val_unit);
}

CAMLprim value caml_mpfr_get_default_rounding_mode ()
{
  CAMLparam0 ();
  int rnd = mpfr_get_default_rounding_mode ();
  CAMLreturn (Val_int (rnd));
}

CAMLprim value caml_mpfr_can_round (value b, value err, value rnd1, value rnd2, value prec)
{
  CAMLparam5 (b, err, rnd1, rnd2, prec);
  int ret;

  ret = mpfr_can_round (MPFR_val (b), EXP_val (err), rnd_val (rnd1), rnd_val (rnd2), PREC_val (prec));

  CAMLreturn (Val_int (ret));
}

CAMLprim value caml_mpfr_min_prec (value x)
{
  CAMLparam1 (x);
  CAMLreturn (Int_val (mpfr_min_prec (MPFR_val (x))));
}

/***************************/
/* Miscellaneous Functions */
/***************************/

CAMLprim value caml_mpfr_nexttoward (value x, value y)
{
  CAMLparam2 (x, y);
  CAMLlocal1 (rop);

  rop = caml_mpfr_init2 (caml_mpfr_get_prec (x));
  if (!mpfr_set (MPFR_val (rop), MPFR_val (x), MPFR_RNDN))
    mpfr_nexttoward (MPFR_val (rop), MPFR_val (y));
  else
    caml_failwith(__FUNCTION__);

  CAMLreturn (rop);
}

CAMLprim value caml_mpfr_nextabove (value x, value y)
{
  CAMLparam1 (x);
  CAMLlocal1 (rop);

  rop = caml_mpfr_init2 (caml_mpfr_get_prec (x));
  if (!mpfr_set (MPFR_val (rop), MPFR_val (x), MPFR_RNDN))
    mpfr_nextabove (MPFR_val (rop));
  else
    caml_failwith(__FUNCTION__);

  CAMLreturn (rop);
}

CAMLprim value caml_mpfr_nextbelow (value x, value y)
{
  CAMLparam1 (x);
  CAMLlocal1 (rop);

  rop = caml_mpfr_init2 (caml_mpfr_get_prec (x));
  if (!mpfr_set (MPFR_val (rop), MPFR_val (x), MPFR_RNDN))
    mpfr_nextbelow (MPFR_val (rop));
  else
    caml_failwith(__FUNCTION__);

  CAMLreturn (rop);
}

CAMLprim value caml_mpfr_min (value prec, value op1, value op2, value rnd)
{
  CAMLparam3 (op1, op2, rnd);
  CAMLlocal1 (rop);
  int ter;

  rop = caml_mpfr_init2 (prec);
  ter = mpfr_min (MPFR_val (rop), MPFR_val (op1), MPFR_val (op2), rnd_val (rnd));

  CAMLreturn (caml_tuple2 (rop, Val_int (ter)));
}

CAMLprim value caml_mpfr_max (value prec, value op1, value op2, value rnd)
{
  CAMLparam3 (op1, op2, rnd);
  CAMLlocal1 (rop);
  int ter;

  rop = caml_mpfr_init2 (prec);
  ter = mpfr_max (MPFR_val (rop), MPFR_val (op1), MPFR_val (op2), rnd_val (rnd));

  CAMLreturn (caml_tuple2 (rop, Val_int (ter)));
}

CAMLprim value caml_mpfr_get_exp (value x)
{
  CAMLparam1 (x);
  CAMLreturn (Val_int (mpfr_get_exp (MPFR_val (x))));
}

CAMLprim value caml_mpfr_set_exp (value x, value e)
{
  CAMLparam2 (x, e);
  CAMLlocal1 (rop);
  int ret;

  rop = caml_mpfr_init2 (caml_mpfr_get_prec (x));
  if (!mpfr_set (MPFR_val (rop), MPFR_val (x), MPFR_RNDN))
    ret = mpfr_set_exp (MPFR_val (rop), EXP_val (e));
  else
    caml_failwith(__FUNCTION__);

  CAMLreturn (caml_tuple2 (rop, Val_int (ret)));
}

CAMLprim value caml_mpfr_signbit (value op)
{
  CAMLparam1 (op);
  CAMLreturn (Val_int (mpfr_signbit (MPFR_val (op))));
}

CAMLprim value caml_mpfr_setsign (value prec, value op, value s, value rnd)
{
  CAMLparam3 (op, s, rnd);
  CAMLlocal1 (rop);
  int ter;

  rop = caml_mpfr_init2 (prec);
  ter = mpfr_setsign (MPFR_val (rop), MPFR_val (op), SI_val (s), rnd_val (rnd));

  CAMLreturn (caml_tuple2 (rop, Val_int (ter)));
}

CAMLprim value caml_mpfr_copysign (value prec, value op1, value op2, value rnd)
{
  CAMLparam3 (op1, op2, rnd);
  CAMLlocal1 (rop);
  int ter;

  rop = caml_mpfr_init2 (prec);
  ter = mpfr_copysign (MPFR_val (rop), MPFR_val (op1), MPFR_val (op2), rnd_val (rnd));

  CAMLreturn (caml_tuple2 (rop, Val_int (ter)));
}

CAMLprim value caml_mpfr_get_version ()
{
  CAMLparam0 ();
  CAMLreturn (caml_copy_string (mpfr_get_version ()));
}

/*******************************/
/* Exception Related Functions */
/*******************************/

CAMLprim value caml_mpfr_get_emin ()
{
  CAMLparam0 ();
  CAMLreturn (Val_int (mpfr_get_emin ()));
}

CAMLprim value caml_mpfr_get_emax ()
{
  CAMLparam0 ();
  CAMLreturn (Val_int (mpfr_get_emax ()));
}

CAMLprim value caml_mpfr_set_emin (value exp)
{
  CAMLparam1 (exp);
  mpfr_set_emin (EXP_val (exp));
  CAMLreturn (Val_unit);
}

CAMLprim value caml_mpfr_set_emax (value exp)
{
  CAMLparam1 (exp);
  mpfr_set_emax (EXP_val (exp));
  CAMLreturn (Val_unit);
}

CAMLprim value caml_mpfr_get_emin_min ()
{
  CAMLparam0 ();
  CAMLreturn (Val_int (mpfr_get_emin_min ()));
}

CAMLprim value caml_mpfr_get_emin_max ()
{
  CAMLparam0 ();
  CAMLreturn (Val_int (mpfr_get_emin_max ()));
}

CAMLprim value caml_mpfr_get_emax_min ()
{
  CAMLparam0 ();
  CAMLreturn (Val_int (mpfr_get_emin_min ()));
}

CAMLprim value caml_mpfr_get_emax_max ()
{
  CAMLparam0 ();
  CAMLreturn (Val_int (mpfr_get_emin_max ()));
}

CAMLprim value caml_mpfr_check_range (value x, value t, value rnd)
{
  CAMLparam3 (x, t, rnd);
  CAMLlocal1 (rop);
  int ter;

  rop = caml_mpfr_init2 (caml_mpfr_get_prec (x));
  if (!mpfr_set (MPFR_val (rop), MPFR_val (x), MPFR_RNDN))
    ter = mpfr_check_range (MPFR_val (rop), SI_val (t), rnd);
  else
    caml_failwith(__FUNCTION__);

  CAMLreturn (caml_tuple2 (rop, Val_int (ter)));
}

CAMLprim value caml_mpfr_subnormalize (value x, value t, value rnd)
{
  CAMLparam3 (x, t, rnd);
  CAMLlocal1 (rop);
  int ter;

  rop = caml_mpfr_init2 (caml_mpfr_get_prec (x));
  if (!mpfr_set (MPFR_val (rop), MPFR_val (x), MPFR_RNDN))
    ter = mpfr_subnormalize (MPFR_val (rop), SI_val (t), rnd);
  else
    caml_failwith(__FUNCTION__);

  CAMLreturn (caml_tuple2 (rop, Val_int (ter)));
}

CAMLprim value caml_mpfr_clear_underflow ()
{
  CAMLparam0 ();
  mpfr_clear_underflow ();
  CAMLreturn (Val_unit);
}

CAMLprim value caml_mpfr_clear_overflow ()
{
  CAMLparam0 ();
  mpfr_clear_overflow ();
  CAMLreturn (Val_unit);
}

CAMLprim value caml_mpfr_clear_divby0 ()
{
  CAMLparam0 ();
  mpfr_clear_divby0 ();
  CAMLreturn (Val_unit);
}

CAMLprim value caml_mpfr_clear_nanflag ()
{
  CAMLparam0 ();
  mpfr_clear_nanflag ();
  CAMLreturn (Val_unit);
}

CAMLprim value caml_mpfr_clear_inexflag ()
{
  CAMLparam0 ();
  mpfr_clear_inexflag ();
  CAMLreturn (Val_unit);
}

CAMLprim value caml_mpfr_clear_erangeflag ()
{
  CAMLparam0 ();
  mpfr_clear_erangeflag ();
  CAMLreturn (Val_unit);
}

CAMLprim value caml_mpfr_set_underflow ()
{
  CAMLparam0 ();
  mpfr_set_underflow ();
  CAMLreturn (Val_unit);
}

CAMLprim value caml_mpfr_set_overflow ()
{
  CAMLparam0 ();
  mpfr_set_overflow ();
  CAMLreturn (Val_unit);
}

CAMLprim value caml_mpfr_set_divby0 ()
{
  CAMLparam0 ();
  mpfr_set_divby0 ();
  CAMLreturn (Val_unit);
}

CAMLprim value caml_mpfr_set_nanflag ()
{
  CAMLparam0 ();
  mpfr_set_nanflag ();
  CAMLreturn (Val_unit);
}

CAMLprim value caml_mpfr_set_inexflag ()
{
  CAMLparam0 ();
  mpfr_set_inexflag ();
  CAMLreturn (Val_unit);
}

CAMLprim value caml_mpfr_set_erangeflag ()
{
  CAMLparam0 ();
  mpfr_set_erangeflag ();
  CAMLreturn (Val_unit);
}

CAMLprim value caml_mpfr_underflow_p ()
{
  CAMLparam0 ();
  CAMLreturn (Val_bool (mpfr_underflow_p ()));
}

CAMLprim value caml_mpfr_overflow_p ()
{
  CAMLparam0 ();
  CAMLreturn (Val_bool (mpfr_overflow_p ()));
}

CAMLprim value caml_mpfr_divby0_p ()
{
  CAMLparam0 ();
  CAMLreturn (Val_bool (mpfr_divby0_p ()));
}

CAMLprim value caml_mpfr_nanflag_p ()
{
  CAMLparam0 ();
  CAMLreturn (Val_bool (mpfr_nanflag_p ()));
}

CAMLprim value caml_mpfr_inexflag_p ()
{
  CAMLparam0 ();
  CAMLreturn (Val_bool (mpfr_inexflag_p ()));
}

CAMLprim value caml_mpfr_erangeflag_p ()
{
  CAMLparam0 ();
  CAMLreturn (Val_bool (mpfr_erangeflag_p ()));
}
