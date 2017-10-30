#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <mpfr.h>

char *rounding_to_string (int r)
{
  char * buf = malloc (32);
  if (r == 0)
    {
      strcpy (buf, "Correct");
    }
  else if ( r < 0)
    {
      strcpy (buf, "Lower");
    }
  else
    {
      strcpy (buf, "Higher");
    }
  return buf;
}

int main()
{
  mpfr_set_default_prec (12345);
  printf ("default_precision: %ld\n", mpfr_get_default_prec ());

  char* buffer;
  mpfr_t one, x;
  mpfr_inits (one, x, NULL);

  int r = mpfr_set_si (one, 1, MPFR_RNDN);
  buffer = rounding_to_string (r);
  printf ("%s\n", buffer);
  free (buffer);

  r = mpfr_set (x, one, MPFR_RNDN);
  buffer = rounding_to_string (r);
  printf ("%s\n", buffer);
  free (buffer);

  r = mpfr_set_d (x, 1., MPFR_RNDN);
  buffer = rounding_to_string (r);
  printf ("%s\n", buffer);
  free (buffer);

  r = mpfr_set_str (x, "1", 0, MPFR_RNDN);
  buffer = rounding_to_string (r);
  printf ("%s\n", buffer);
  free (buffer);

  mpfr_set_nan (x);
  printf ("No_Rounding\n");

  mpfr_set_inf (x, 1);
  printf ("No_Rounding\n");

  mpfr_set_zero (x, -1);
  printf ("No_Rounding\n");

  printf ("%ld\n", mpfr_get_prec (x));


  mpfr_clears (one, x, NULL);
  return 0;
}
