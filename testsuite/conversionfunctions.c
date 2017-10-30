#include <stdlib.h>
#include <stdio.h>
#include <mpfr.h>

int main()
{
  mpfr_t x, y;
  double d;
  int i;
  mpfr_exp_t e;

  mpfr_init (x);
  mpfr_set_d (x, 1./3., MPFR_RNDN);

  d = mpfr_get_d (x, MPFR_RNDN);
  printf ("%e\n", d);

  i = mpfr_get_si (x, MPFR_RNDN);
  printf ("%d\n", i);

  d = mpfr_get_d_2exp (&e, x, MPFR_RNDN);
  printf("%e %ld\n", d, e);

  mpfr_init (y);
  mpfr_frexp (&e, y, x, MPFR_RNDN);
  printf("%ld\n", e);

  char *buffer;
  buffer = mpfr_get_str (NULL, &e, 10, 0, x, MPFR_RNDN);
  printf("%s %ld\n", buffer, e);

  mpfr_printf ("%.Re\n", x);

  if (mpfr_fits_sint_p (x, MPFR_RNDN))
    printf ("true\n");
  else
    printf ("false\n");

  mpfr_free_str (buffer);
  mpfr_clear (x);
  mpfr_clear (y);
  return 0;
}
