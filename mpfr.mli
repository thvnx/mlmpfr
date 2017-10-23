(** OCaml bindings for MPFR.

A [mpfr_float] is an immutable data structure that contains a {e
mpfr_t} number, as well as an optional ternary value, as provided by
(and described in) the {{:http://www.mpfr.org}MPFR library}.

A few distinctions are made from the original C library:

{ul {- {e mpfr_init*} and {e mpfr_set*} functions are not provided in
order to implement these bindings with respect to the functional
paradigm (i.e. immutability). Consequently, {e mpfr_clear*} functions
are not provided too, and so, the garbage collector is in charge of
memory management;}
{- functions managing the following types are not supported: {e
unsigned long int}, {e uintmax_t}, {e intmax_t}, {e float}, {e long
double}, {e _Decimal64}, {e mpz_t}, {e mpq_t}, and {e mpf_t}. Except
for {e mpfr_sqrt_ui}, {e mpfr_fac_ui} and {e mpfr_zeta_ui} which are
partially supported on the range of the positive values of an OCaml
signed integer. In fact, only the OCaml native types ([int], [float],
and [string]) are supported, assuming that a [float] is a
double-precision floating-point number and an [int] is a 64-bits
signed integer. Thus, all functions named with {e *_ui*} or {e *_d*}
are renamed here with {e *_int*} or {e *_float*}, respectively;}
{- bindings to functions {e mpfr_*printf}, {e mpfr_*random*}, {e
mpfr_get_patches}, {e mpfr_buildopt_*}, and macros {e MPFR_VERSION*}
are not implemented.}}

In the sequel, if not provided, optional parameters [prec] and [rnd]
are set to MPFR's defaults precision and rounding mode. *)

(** Binding to C MPFR {e
{{:http://www.mpfr.org/mpfr-current/mpfr.html#Nomenclature-and-Types}mpfr_t}}
type. *)
type mpfr_t

(** Associated to an [mpfr_t] value, a
{{:http://www.mpfr.org/mpfr-current/mpfr.html#Rounding-Modes}[ternary]}
value indicates if it was correctly rounded. *)
type ternary =
  Correctly_Rounded
| Greater
| Lower

type mpfr_float = mpfr_t * ternary option

(** Rounding
{{:http://www.mpfr.org/mpfr-current/mpfr.html#Rounding-Modes}modes}. *)
type mpfr_rnd_t =
  To_Nearest
| Toward_Zero
| Toward_Plus_Infinity
| Toward_Minus_Infinity
| Away_From_Zero

(** {0 Initialization} *)

(** [make_from_float f ~prec:p ~rnd:r] returns a fresh [mpfr_float] of
precision [p] from the float value [f], rounded with [r]. *)
val make_from_float : ?prec:int -> ?rnd:mpfr_rnd_t -> float -> mpfr_float

(** [set_default_precision p] sets the default working precision to [p]. *)
val set_default_precision : int -> unit

(** [get_precision x] returns the precision of [x]. *)
val get_precision : mpfr_float -> int

(** {0 Conversion} *)
(** {0 Basic Arithmetic} *)
(** {0 Comparison} *)
(** {0 Special} *)
(** {0 Input and Output} *)
(** {0 Integer and Remainder Related} *)
(** {0 Rounding Related} *)
(** {0 Miscellaneous} *)
(** {0 Exception Related} *)
