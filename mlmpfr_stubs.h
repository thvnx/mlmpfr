#ifndef MLMPFR_STUBS_H
#define MLMPFR_STUBS_H

#include <stdio.h>
#include <mpfr.h>
#include <caml/mlvalues.h>
#include <caml/memory.h>
#include <caml/alloc.h>
#include <caml/custom.h>
#include <caml/fail.h>

static int custom_compare (value, value);

static struct custom_operations mpfr_ops = {
  "github.com/thvnx/mlmpfr.1",
  custom_finalize_default,
  custom_compare,
  custom_hash_default,
  custom_serialize_default,
  custom_deserialize_default,
  custom_compare_ext_default
};

#define MPFR_val(m) (*((mpfr_t *) Data_custom_val (m)))
#define SI_val(s) ((long int) Int_val (s))
#define UI_val(s) ((unsigned long int) Int_val (s))
#define DBL_val(d) (Double_val (d))
#define EXP_val(e) ((mpfr_exp_t) Int_val (e))
#define PREC_val(p) ((mpfr_prec_t) Int_val (p))

static int rnd_val (r)
{
  switch (r)
    {
    case 0: return MPFR_RNDN;
    case 3: return MPFR_RNDZ;
    case 5: return MPFR_RNDU;
    case 7: return MPFR_RNDD;
    case 9: return MPFR_RNDA;
    default:
      caml_failwith(__FUNCTION__);
    }
}

static value caml_tuple2 (value e1, value e2)
{
  value t = caml_alloc_tuple (2);
  Store_field (t, 0, e1);
  Store_field (t, 1, e2);
  return t;
}

static value caml_tuple3 (value e1, value e2, value e3)
{
  value t = caml_alloc_tuple (3);
  Store_field (t, 0, e1);
  Store_field (t, 1, e2);
  Store_field (t, 2, e3);
  return t;
}

#define MPFR_SPECIAL_FUNCTION(N)				\
  {								\
    CAMLparam2 (op, rnd);					\
    CAMLlocal1 (rop);						\
    int ter;							\
    rop = caml_mpfr_init2 (prec);				\
    ter = N (MPFR_val (rop), MPFR_val (op), rnd_val (rnd));	\
    CAMLreturn (caml_tuple2 (rop, Val_int (ter)));		\
  }

#endif
