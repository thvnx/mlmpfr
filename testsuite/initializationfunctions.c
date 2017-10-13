#include <stdio.h>
#include <mpfr.h>

int main()
{
  mpfr_t x, y;
  mpfr_init2 (x, 2);
  mpfr_clear (x);
  mpfr_init (x);
  mpfr_clear (x);
  mpfr_inits2 (2, x, y, (mpfr_ptr) 0);
  mpfr_clears (x, y,  (mpfr_ptr) 0);
  mpfr_inits (x, y, (mpfr_ptr) 0);
  mpfr_clears (x, y,  (mpfr_ptr) 0);
  mpfr_prec_t p = 64;
  mpfr_set_default_prec (p);
  if (mpfr_get_default_prec () == p)
    printf("1\n");
  else
    printf("0\n");
  mpfr_init (x);
  mpfr_set_prec (x, 1234);
  printf ("%ld\n", mpfr_get_prec (x));
  mpfr_clear (x);
  
  return 0;
}
