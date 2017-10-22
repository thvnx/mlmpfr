# mlmpfr
OCaml bindings for MPFR (in development).

This OCaml C interface to MPFR covers almost all the MPFR functions with stricts MPFR library calls. The following list describes the ones which are emulated or simply unsupported, and the ones that specification differs from the MPFR C functions.

- Function: the return value of `mpfr_frexp` is omited.
- Function: `char * mpfr_get_str (char *str, mpfr_exp_t *expptr, int b, size_t n, mpfr_t op, mpfr_rnd_t rnd)` is here `val mpfr_get_str : int -> int -> mpfr_t -> mpfr_rnd_t -> string * int = <fun>`. This binding uses the allocation function provided by MPFR (and uses `mpfr_free_str`). It returns a tuple containing the number significand and exponent.

- Function: `int mpfr_sqrt_ui (mpfr_t rop, unsigned long int op, mpfr_rnd_t rnd)` is supported (`mpfr_sqrt_int` here). The binding will convert _op_ from an OCaml signed integer to a C unsigned long int if _op_ is positive (it fails otherwise).
- Function: `int mpfr_root (mpfr_t rop, mpfr_t op, unsigned long int k, mpfr_rnd_t rnd)` is supported. The binding will convert _k_ from an OCaml signed integer to a C unsigned long int if _k_ is positive (it fails otherwise).

- Function: `size_t mpfr_out_str (FILE *stream, int base, size_t n, mpfr_t op, mpfr_rnd_t rnd)` is emulated here to avoid different buffering mechanism interactions. It uses `mpfr_get_str` to format the output string (decimal point is not defined by locale).

- Function: `mpfr_prec_round` is __not supported__, use `mpfr_init_set` instead.

- Functions: `mpfr_urandomb`, `mpfr_urandom`, and `mpfr_grandom` are __not supported__.
- Macros: `MPFR_VERSION*` are __not supported__.
- Functions: `mpfr_get_patches` and `mpfr_buildopt_*` are __not supported__.

Moreover:
- all the initialization and assignment functions are not supported. A more _functional_ approach is used (see `mpfr_init_set_mpfr` for example).
- all the functions dealing with `unsigned long int`, `uintmax_t`, `intmax_t`, `float`, `long double`, `_Decimal64`, `mpz_t`, `mpq_t`, and `mpf_t` types are __not supported__, except for `mpfr_sqrt_ui`, `mpfr_fac_ui` and `mpfr_zeta_ui` which are partially supported (on the range of the positive values of an OCaml signed integer);
- all the functions from _[Formatted Output Functions](http://www.mpfr.org/mpfr-current/mpfr.html#Formatted-Output-Functions)_ are __not supported__.
- all the functions dealing with `signed int`, such as `mpfr_set_si`, are renamed (i.e. _si_ is replaced by _int_);
- all the functions dealing with `double`, such as `mpfr_set_d`, are renamed (i.e. _d_ is replaced by _float_).
