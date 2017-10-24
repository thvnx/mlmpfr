#include <stdlib.h>
#include <stdio.h>
#include <mpfr.h>

void rounding_to_string (char **buf, int r)
{
  if (r == 0)
    {
      *buf = "Correct\0";
    }
  else if ( r < 0)
    {
      *buf = "Lower\0";
    }
  else
    {
      *buf = "Higher\0";
    }
}

int main()
{
  mpfr_set_default_prec (12345);
  printf ("default_precision: %ld\n", mpfr_get_default_prec ());

  char *buffer = malloc (128 * sizeof(char));
  mpfr_t one, x;
  mpfr_inits (one, x, NULL);

  int r = mpfr_set_si (one, 1, MPFR_RNDN);
  rounding_to_string (&buffer, r);
  printf ("%s\n", buffer);

  r = mpfr_set (x, one, MPFR_RNDN);
  rounding_to_string (&buffer, r);
  printf ("%s\n", buffer);

  r = mpfr_set_d (x, 1., MPFR_RNDN);
  rounding_to_string (&buffer, r);
  printf ("%s\n", buffer);

  r = mpfr_set_str (x, "1", 0, MPFR_RNDN);
  rounding_to_string (&buffer, r);
  printf ("%s\n", buffer);

  mpfr_set_nan (x);
  printf ("No_Rounding\n");

  mpfr_set_inf (x, 1);
  printf ("No_Rounding\n");

  mpfr_set_zero (x, -1);
  printf ("No_Rounding\n");

  printf ("%ld\n", mpfr_get_prec (x));

  //free (buffer);
  mpfr_clears (one, x, NULL);
  return 0;
}
