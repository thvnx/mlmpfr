/* This file is part of mlmpfr.

  mlmpfr is free software: you can redistribute it and/or modify it
  under the terms of the GNU Lesser General Public License as
  published by the Free Software Foundation, either version 3 of the
  License, or (at your option) any later version.

  mlmpfr is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with mlmpfr. If not, see
 <http://www.gnu.org/licenses/>. */

#ifndef MLMPFR_STUBS_H
#define MLMPFR_STUBS_H

#include <stdio.h>
#include <mpfr.h>
#include <limits.h>
#include <caml/mlvalues.h>
#include <caml/memory.h>
#include <caml/alloc.h>
#include <caml/custom.h>
#include <caml/fail.h>
#include <caml/callback.h>

static int custom_compare (value, value);

static void custom_finalize (value);

static struct custom_operations mpfr_ops = {
  "https://github.com/thvnx/mlmpfr/releases/tag/mlmpfr.3.1.6",
  custom_finalize,
  custom_compare,
  custom_hash_default,
  custom_serialize_default,
  custom_deserialize_default,
  custom_compare_ext_default
};

#define Val_none Val_int(0)
#define Some_val(v) Field(v,0)

static value val_some (value v)
{
  CAMLparam1 (v);
  CAMLlocal1 (some);
  some = caml_alloc (1, 0);
  Store_field (some, 0, v);
  CAMLreturn (some);
}

#define MPFR_val(m) (*((mpfr_t *) Data_custom_val (m)))
#define MPFR_val2(m) (*((mpfr_t *) Data_custom_val (Field(m, 0))))
#define SI_val(s) ((long int) Int_val (s))
#define MPFR_val22(s) (Field(s, 1))
#define UI_val(s) ((unsigned long int) Int_val (s))
#define DBL_val(d) (Double_val (d))
#define EXP_val(e) ((mpfr_exp_t) Int_val (e))
#define PREC_val(p) ((mpfr_prec_t) Int_val (p))

static value val_ter (int t)
{
  CAMLparam0 ();
  CAMLlocal1 (ter);

  if (t == 0)
    ter = Val_int (0);
  else if ( t > 0)
    ter = Val_int (1);
  else
    ter = Val_int (2);

  CAMLreturn (ter);
}

static int ter_val_opt (value r)
{
  if (r == Val_none)
    {
      caml_failwith(__FUNCTION__);
    }
  else
    {
      switch (Long_val (Some_val (r)))
	{
	case 0: return 0;
	case 1: return 1;
	case 2: return -1;
	default:
	  caml_failwith(__FUNCTION__);
	}
      return 0;
    }
}

static int rnd_val (value r)
{
  switch (Long_val (r))
    {
    case 0: return MPFR_RNDN;
    case 1: return MPFR_RNDZ;
    case 2: return MPFR_RNDU;
    case 3: return MPFR_RNDD;
    case 4: return MPFR_RNDA;
    case 5: return MPFR_RNDF;
    default:
      caml_failwith(__FUNCTION__);
    }
}

static int rnd_val_opt (value r)
{
  return r == Val_none
    ? rnd_val (Val_int (mpfr_get_default_rounding_mode ()))
    : rnd_val (Some_val (r));
}

static int sign_val (value s)
{
  switch (Long_val (s))
    {
    case 0: return 1;
    case 1: return -1;
    default:
      caml_failwith(__FUNCTION__);
    }
}

static value val_sign (int s)
{
  CAMLparam0 ();

  if (s >= 0)
    CAMLreturn (Val_int (0));
  else
    CAMLreturn (Val_int (1));
}

static int flags_val (value f)
{
  value head;
  int flags = 0;

  while (f != Val_emptylist) {
    head = Field(f, 0);
    switch (Long_val (head))
      {
      case 0: flags|=MPFR_FLAGS_UNDERFLOW; break;
      case 1: flags|=MPFR_FLAGS_OVERFLOW; break;
      case 2: flags|=MPFR_FLAGS_DIVBY0; break;
      case 3: flags|=MPFR_FLAGS_NAN; break;
      case 4: flags|=MPFR_FLAGS_INEXACT; break;
      case 5: flags|=MPFR_FLAGS_ERANGE; break;
      case 6: flags|=MPFR_FLAGS_ALL; break;
      default:
	caml_failwith(__FUNCTION__);
      }
    f = Field(f, 1);
  }

  return flags;
}

static value val_flags (int s)
{
  value head, tail = Val_emptylist;
  int i = 0;

  while (i < 7) {
    switch (s >> i & 0x1)
      {
      case 0:
	break;
      case 1:
	head = caml_alloc(2, 0);
	Store_field(head, 0, Val_int(i));
	Store_field(head, 1, tail);
	tail = head;
	break;
      default:
	caml_failwith(__FUNCTION__);
      }
    i++;
  }

  return tail;
}

static value caml_tuple2 (value e1, value e2)
{
  value t = caml_alloc_tuple (2);
  Store_field (t, 0, e1);
  Store_field (t, 1, e2);
  return t;
}

static value mpfr_float (value mpfr_t, value ternary)
{
  return caml_tuple2 (mpfr_t, ternary);
}

/*static value caml_tuple3 (value e1, value e2, value e3)
{
  value t = caml_alloc_tuple (3);
  Store_field (t, 0, e1);
  Store_field (t, 1, e2);
  Store_field (t, 2, e3);
  return t;
  }*/

#define MPFR_REGULAR_FUNCTION1(N)				 \
  {								 \
    CAMLparam3 (op, rnd, prec);					 \
    CAMLlocal1 (rop);						 \
    int ter;							 \
    rop = caml_mpfr_init2_opt (prec);				 \
    ter = N (MPFR_val (rop), MPFR_val2 (op), rnd_val_opt (rnd)); \
    CAMLreturn (mpfr_float (rop, val_some (val_ter (ter))));	 \
  }

value caml_mpfr_get_default_prec ();

#endif
