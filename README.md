# mlmpfr
OCaml bindings for MPFR (in development).

This OCaml C interface to MPFR covers almost all the MPFR functions with stricts MPFR library calls. The following list describes the ones which are emulated or simply unsupported, and the ones that specification differs from the MPFR C functions. 

 - Function: `void mpfr_init2 (mpfr_t x, mpfr_prec_t prec)` is here `val mpfr_init2 : mpfr_prec_t -> mpfr_t = <fun>` (returns `x` instead of `void`).
 - Function: `void mpfr_inits2 (mpfr_prec_t prec, mpfr_t x, ...)` is here `val mpfr_inits2 : mpfr_prec_t -> int -> mpfrt_t list = <fun>`
 (returns a list of _n_ `mpfr_t` numbers instead of `void`). This function doesn't call the C function, but reuses `mpfr_init2`.
- Function: `void mpfr_clears (mpfr_t x, ...)` is here `val mpfr_clears : mpfr_t list -> unit = <fun>` and calls `mpfr_clear` on each elements of the list.
- Function: `void mpfr_init (mpfr_t x)` is here `val mpfr_init : unit -> mpfr_t = <fun>`.
- Function: `void mpfr_inits (mpfr_t x, ...)` is here `val mpfr_inits : unit -> mpfr_t list = <fun>`.
- Macro: `MPFR_DECL_INIT (name, prec)` is __not supported__.

- Functions: `mpfr_set_ui`, `mpfr_set_uj`, `mpfr_set_sj`, `mpfr_set_flt`, `mpfr_set_ld`, `mpfr_set_decimal64`, `mpfr_set_z`, `mpfr_set_q`, `mpfr_set_f`, `mpfr_set_ui_2exp`, `mpfr_set_si_2exp`, `mpfr_set_uj_2exp`, `mpfr_set_sj_2exp`, `mpfr_set_z_2exp` are __not supported__.
- Function: `mpfr_set_si` is renamed here `mpfr_set_int`.
- Function: `mpfr_set_d` is renamed here `mpfr_set_float`.
- Function: in `mpfr_strtofr`, `endptr` is a null pointer.

- Function: `char * mpfr_get_str (char *str, mpfr_exp_t *expptr, int b, size_t n, mpfr_t op, mpfr_rnd_t rnd)` is here `val mpfr_get_str : int -> int -> mpfr_t -> mpfr_rnd_t -> string * int = <fun>`. This binding uses the allocation function provided by MPFR (and uses `mpfr_free_str`). It returns a tuple containing the number significand and exponent.

- Function: `size_t mpfr_out_str (FILE *stream, int base, size_t n, mpfr_t op, mpfr_rnd_t rnd)` is emulated here to avoid different buffering mechanism interactions. It uses `mpfr_get_str` to format the output string (decimal point is not defined by locale).
