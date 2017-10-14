#include <stdio.h>
#include <mpfr.h>

int main ()
{
  mpfr_t m;
  mpfr_init2 (m, 53);
  printf("%d\n", mpfr_set (m, m, MPFR_RNDN));
  printf("%d\n", mpfr_set_ui (m, 1, MPFR_RNDN));
  printf("%d\n", mpfr_set_d (m, 1., MPFR_RNDN));
  printf("%d\n", mpfr_set_str (m, "1", 10, MPFR_RNDN));
  printf("%d\n", mpfr_strtofr (m, "1", NULL, 10, MPFR_RNDN));
  mpfr_set_nan (m);
  mpfr_set_inf (m, 0);
  mpfr_set_zero (m, 0);
  mpfr_swap (m , m);

  mpfr_clear (m);
  return 0;
}
