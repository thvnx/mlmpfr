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

(** [Precision_range] is raised if precision does not fit the
precision range (between [mpfr_prec_min] and [mpfr_prec_max]). *)
exception Precision_range of int

(** [Base_range] is raised if base does not fit the base range
(between [2] and [64]), or [0] for automatic detection. *)
exception Base_range of int

type sign = Positive | Negative

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

(** [rounding x] returns a string corresponding to the ternary value of [x]. *)
val rounding_to_string : mpfr_float -> string

(** Rounding
{{:http://www.mpfr.org/mpfr-current/mpfr.html#Rounding-Modes}modes}. *)
type mpfr_rnd_t =
  To_Nearest
| Toward_Zero
| Toward_Plus_Infinity
| Toward_Minus_Infinity
| Away_From_Zero

val mpfr_prec_min : int (** Minimum allowed precision. *)
val mpfr_prec_max : int (** Maximum allowed precision. *)

(** {0 Initialization} *)

(** [set_default_precision p] sets the default working precision to [p]. *)
val set_default_precision : int -> unit
(** @raise Precision_range if [p] is not allowed. *)

val get_default_precision : unit -> int

(** [get_precision x] returns the precision of [x]. *)
val get_precision : mpfr_float -> int

val make_from_mpfr : ?prec:int -> ?rnd:mpfr_rnd_t -> mpfr_float -> mpfr_float
val make_from_int : ?prec:int -> ?rnd:mpfr_rnd_t -> int -> mpfr_float
val make_from_float : ?prec:int -> ?rnd:mpfr_rnd_t -> float -> mpfr_float
(** [make_from_mpfr x ~prec:p ~rnd:r] (resp. [make_from_int] or
[make_from_float]) returns a fresh [mpfr_float] of precision [p] from
the mpfr_float (resp. int or float) value [x], rounded with [r].
@raise Precision_range if [p] is not allowed. *)

(** [make_from_str s ~base:b ~prec:p ~rnd:r] returns a fresh
[mpfr_float] of precision [p] from the string value [s] in base [b],
rounded with [r].
@raise Precision_range if [p] is not allowed.
@raise Base_range if [b] is not allowed. *)
val make_from_str : ?prec:int -> ?rnd:mpfr_rnd_t -> ?base:int -> string -> mpfr_float

val make_nan : ?prec:int -> unit -> mpfr_float (* see below *)
val make_inf : ?prec:int -> sign -> mpfr_float (* see below *)

(** [make_nan ~prec:p] returns a NaN value while [make_inf ~prec:p s]
(resp. [make_zero ~prec:p s]) returns a infinity (resp. zero) with
sign [s].  @raise Precision_range if [p] is not allowed. *)
val make_zero : ?prec:int -> sign -> mpfr_float

(** {0 Conversion} *)
(** {0 Basic Arithmetic} *)
(** {0 Comparison} *)
(** {0 Special} *)
(** {0 Input and Output} *)
(** {0 Integer and Remainder Related} *)
(** {0 Rounding Related} *)
(** {0 Miscellaneous} *)
(** {0 Exception Related} *)
