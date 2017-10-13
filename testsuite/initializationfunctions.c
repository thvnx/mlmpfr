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
  
  return 0;
}
