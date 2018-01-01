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

#include <stdio.h>
#include <mpfr.h>

void all (mpfr_t op1, mpfr_t op2)
{
  mpfr_t rop;
  mpfr_init (rop);

  mpfr_add (rop, op1, op2, MPFR_RNDN);
  mpfr_printf ("%.Re\n", rop);
  mpfr_add_si (rop, op1, mpfr_get_si (op2, MPFR_RNDN), MPFR_RNDN);
  mpfr_printf ("%.Re\n", rop);
  mpfr_add_d (rop, op1, mpfr_get_d (op2, MPFR_RNDN), MPFR_RNDN);
  mpfr_printf ("%.Re\n", rop);

  mpfr_sub (rop, op1, op2, MPFR_RNDN);
  mpfr_printf ("%.Re\n", rop);
  mpfr_sub_si (rop, op1, mpfr_get_si (op2, MPFR_RNDN), MPFR_RNDN);
  mpfr_printf ("%.Re\n", rop);
  mpfr_si_sub (rop, mpfr_get_si (op1, MPFR_RNDN), op2, MPFR_RNDN);
  mpfr_printf ("%.Re\n", rop);
  mpfr_sub_d (rop, op1, mpfr_get_d (op2, MPFR_RNDN), MPFR_RNDN);
  mpfr_printf ("%.Re\n", rop);
  mpfr_d_sub (rop, mpfr_get_d (op1, MPFR_RNDN), op2, MPFR_RNDN);
  mpfr_printf ("%.Re\n", rop);

  mpfr_mul (rop, op1, op2, MPFR_RNDN);
  mpfr_printf ("%.Re\n", rop);
  mpfr_mul_si (rop, op1, mpfr_get_si (op2, MPFR_RNDN), MPFR_RNDN);
  mpfr_printf ("%.Re\n", rop);
  mpfr_mul_d (rop, op1, mpfr_get_d (op2, MPFR_RNDN), MPFR_RNDN);
  mpfr_printf ("%.Re\n", rop);

  mpfr_div (rop, op1, op2, MPFR_RNDN);
  mpfr_printf ("%.Re\n", rop);
  mpfr_div_si (rop, op1, mpfr_get_si (op2, MPFR_RNDN), MPFR_RNDN);
  mpfr_printf ("%.Re\n", rop);
  mpfr_si_div (rop, mpfr_get_si (op1, MPFR_RNDN), op2, MPFR_RNDN);
  mpfr_printf ("%.Re\n", rop);
  mpfr_div_d (rop, op1, mpfr_get_d (op2, MPFR_RNDN), MPFR_RNDN);
  mpfr_printf ("%.Re\n", rop);
  mpfr_d_div (rop, mpfr_get_d (op1, MPFR_RNDN), op2, MPFR_RNDN);
  mpfr_printf ("%.Re\n", rop);

  mpfr_sqrt (rop, op1, MPFR_RNDN);
  mpfr_printf ("%.Re\n", rop);
  if (mpfr_sgn (op1) < 0)
    mpfr_set_nan (rop);
  else
    mpfr_sqrt_ui (rop, mpfr_get_ui (op1, MPFR_RNDN), MPFR_RNDN);
  mpfr_printf ("%.Re\n", rop);

  mpfr_cbrt (rop, op1, MPFR_RNDN);
  mpfr_printf ("%.Re\n", rop);
  mpfr_rootn_ui (rop, op1, 10, MPFR_RNDN);
  mpfr_printf ("%.Re\n", rop);

  mpfr_pow (rop, op1, op2, MPFR_RNDN);
  mpfr_printf ("%.Re\n", rop);
  mpfr_pow_si (rop, op1, mpfr_get_si (op2, MPFR_RNDN), MPFR_RNDN);
  mpfr_printf ("%.Re\n", rop);

  mpfr_neg (rop, op1, MPFR_RNDN);
  mpfr_printf ("%.Re\n", rop);

  mpfr_abs (rop, op1, MPFR_RNDN);
  mpfr_printf ("%.Re\n", rop);

  mpfr_dim (rop, op1, op2, MPFR_RNDN);
  mpfr_printf ("%.Re\n", rop);

  mpfr_mul_2si (rop, op1, mpfr_get_si (op2, MPFR_RNDN), MPFR_RNDN);
  mpfr_printf ("%.Re\n", rop);

  mpfr_div_2si (rop, op1, mpfr_get_si (op2, MPFR_RNDN), MPFR_RNDN);
  mpfr_printf ("%.Re\n", rop);

  mpfr_clear (rop);
}

int main ()
{
  mpfr_t op1, op2;
  mpfr_inits (op1, op2, NULL);

  mpfr_set_d (op1, 1. / 3, MPFR_RNDN);
  mpfr_set_d (op2, 1. / 10, MPFR_RNDN);

  all(op1, op2);
  printf("\n");

  mpfr_set_d (op1, -4. / 3, MPFR_RNDN);

  all(op1, op2);
  printf("\n");

  mpfr_set_d (op1, 1. / 3, MPFR_RNDN);
  mpfr_set_d (op2, -113. / 10, MPFR_RNDN);

  all(op1, op2);
  printf("\n");

  mpfr_set_d (op1, +0, MPFR_RNDN);
  mpfr_set_d (op2, -1. / 10, MPFR_RNDN);

  all(op1, op2);
  printf("\n");

  mpfr_set_d (op1, -0., MPFR_RNDN);
  mpfr_set_d (op2, -0., MPFR_RNDN);

  all(op1, op2);

  mpfr_clears (op1, op2, NULL);
  return 0;
}
