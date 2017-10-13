#include <stdio.h>
#include <mpfr.h>

int main ()
{
  mpfr_t m;
  mpfr_init2 (m, 53);
  printf("%d\n", mpfr_set_d (m, 1., MPFR_RNDN));
  mpfr_clear (m);
  return 0;
}
 
