(* This file is part of mlmpfr.

  mlmpfr is free software: you can redistribute it and/or modify it
  under the terms of the GNU Lesser General Public License as
  published by the Free Software Foundation, either version 3 of the
  License, or (at your option) any later version.

  mlmpfr is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with mlmpfr. If not, see
  <http://www.gnu.org/licenses/>. *)

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

(** {2 Initialization} *)

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
the mpfr_float (resp. int or float) value [x], rounded in direction [r].
@raise Precision_range if [p] is not allowed. *)

(** [make_from_str s ~base:b ~prec:p ~rnd:r] returns a fresh
[mpfr_float] of precision [p] from the string value [s] in base [b],
rounded in direction [r].
@raise Precision_range if [p] is not allowed.
@raise Base_range if [b] is not allowed. *)
val make_from_str : ?prec:int -> ?rnd:mpfr_rnd_t -> ?base:int -> string -> mpfr_float

val make_nan : ?prec:int -> unit -> mpfr_float (* see below *)
val make_inf : ?prec:int -> sign -> mpfr_float (* see below *)

(** [make_nan ~prec:p] returns a NaN value while [make_inf ~prec:p s]
(resp. [make_zero ~prec:p s]) returns a infinity (resp. zero) with
sign [s].  @raise Precision_range if [p] is not allowed. *)
val make_zero : ?prec:int -> sign -> mpfr_float

(** {2 Conversion} *)

val get_float : ?rnd:mpfr_rnd_t -> mpfr_float -> float (* see below *)

(** [get_float ~rnd:r x] (resp. [get_int]) converts [x] to a float
(resp. an int), using the rounding mode [r]. *)
val get_int : ?rnd:mpfr_rnd_t -> mpfr_float -> int

val get_float_2exp : ?rnd:mpfr_rnd_t -> mpfr_float -> float * int

(** [get_float_2exp ~rnd:r x] (resp. [get_mpfr_2exp ~rnd:r ~prec:p x])
returns [(n, exp)] such that [0.5 <= |n| < 1] and [d] times 2 raised
to [exp] equals [x] rounded to float (resp. [p]) precision.
@raise Precision_range if [p] is not allowed. *)
val get_mpfr_2exp : ?rnd:mpfr_rnd_t -> ?prec:int -> mpfr_float -> mpfr_float * int

val get_str : ?rnd:mpfr_rnd_t -> ?base:int -> ?size:int -> mpfr_float -> string * string
(** [get_str ~rnd:r ~base:b ~size:s x] converts [x] to a tuple [(frac,
exp)], where [frac] is a fraction (a string of digits in base [b])
with rounding to direction [r], and [exp] is an exponent. [s] is the
number of significand digits output in [frac]. If [s] is zero, the
number of digits of the significand is chosen large enough so that
re-reading the printed value with the same precision, assuming both
output and input use rounding to nearest, will recover the original
value of [x]. Decimal is the default base and default size is zero.
@raise Base_range if base is not allowed. *)

val get_formatted_str : ?rnd:mpfr_rnd_t -> ?base:int -> ?size:int -> mpfr_float -> string
(** [get_formatted_str] is identical to [get_str] except that it
returns a full-formatted string (equivalent to {e mpfr_printf("%.Re", x)}). *)

val fits_int_p : ?rnd:mpfr_rnd_t -> mpfr_float -> bool
(** Return true if the mpfr_float would fit in a int, when rounded to an integer in the direction [~rnd]. *)

(** {2 Basic Arithmetic} *)

val add : ?rnd:mpfr_rnd_t -> ?prec:int -> mpfr_float -> mpfr_float -> mpfr_float
val add_int : ?rnd:mpfr_rnd_t -> ?prec:int -> mpfr_float -> int -> mpfr_float
val add_float : ?rnd:mpfr_rnd_t -> ?prec:int -> mpfr_float -> float -> mpfr_float
val sub : ?rnd:mpfr_rnd_t -> ?prec:int -> mpfr_float -> mpfr_float -> mpfr_float
val sub_int : ?rnd:mpfr_rnd_t -> ?prec:int -> mpfr_float -> int -> mpfr_float
val int_sub : ?rnd:mpfr_rnd_t -> ?prec:int -> int -> mpfr_float -> mpfr_float
val sub_float : ?rnd:mpfr_rnd_t -> ?prec:int -> mpfr_float -> float -> mpfr_float
val float_sub : ?rnd:mpfr_rnd_t -> ?prec:int -> float -> mpfr_float -> mpfr_float
val mul : ?rnd:mpfr_rnd_t -> ?prec:int -> mpfr_float -> mpfr_float -> mpfr_float
val mul_int : ?rnd:mpfr_rnd_t -> ?prec:int -> mpfr_float -> int -> mpfr_float
val mul_float : ?rnd:mpfr_rnd_t -> ?prec:int -> mpfr_float -> float -> mpfr_float
val div : ?rnd:mpfr_rnd_t -> ?prec:int -> mpfr_float -> mpfr_float -> mpfr_float
val div_int : ?rnd:mpfr_rnd_t -> ?prec:int -> mpfr_float -> int -> mpfr_float
val int_div : ?rnd:mpfr_rnd_t -> ?prec:int -> int -> mpfr_float -> mpfr_float
val div_float : ?rnd:mpfr_rnd_t -> ?prec:int -> mpfr_float -> float -> mpfr_float
val float_div : ?rnd:mpfr_rnd_t -> ?prec:int -> float -> mpfr_float -> mpfr_float
val sqrt : ?rnd:mpfr_rnd_t -> ?prec:int -> mpfr_float -> mpfr_float
(** Addition subtraction, multiply, divide, and square root operations for different combinations
(described above) of [mpfr_float], [int], and [float] operands.
For instance, [add_int ~rnd:r ~prec:p x 1] adds [1] to [x].
Result is computed with precision [p] and rounded in the direction [r].
@raise Precision_range if precision not allowed. *)

(** [sqrt_int ~rnd:r ~prec:p x] returns the square root of [x]
(computed with precision [p]) rounded in the direction [r]. Return [nan] if [x] is negative.
@raise Precision_range if precision not allowed. *)
val sqrt_int : ?rnd:mpfr_rnd_t -> ?prec:int -> int -> mpfr_float

(** Compute the reciprocal square root of an [mpfr_float] number.
@raise Precision_range if precision not allowed. *)
val rec_sqrt : ?rnd:mpfr_rnd_t -> ?prec:int -> mpfr_float -> mpfr_float

val cbrt : ?rnd:mpfr_rnd_t -> ?prec:int -> mpfr_float -> mpfr_float
val root : ?rnd:mpfr_rnd_t -> ?prec:int -> mpfr_float -> int -> mpfr_float
(** [cbrt ~rnd:r ~prec:p x] (resp. [root ~rnd:r ~prec:p x k]) returns
<the cubic root (resp. the [k]-th root) of [x], in precision [p],
rounded in the direction [r].
@raise Precision_range if precision not allowed. *)

val pow : ?rnd:mpfr_rnd_t -> ?prec:int -> mpfr_float -> mpfr_float -> mpfr_float
val pow_int : ?rnd:mpfr_rnd_t -> ?prec:int -> mpfr_float -> int -> mpfr_float
(** [pow ~rnd:r ~prec:p x y] and [pow_int ~rnd:r ~prec:p x y] compute [x]
raised to [y], in precision [p], rounded in the direction [r].
@raise Invalid_math if [x] or [y] is negative.
@raise Precision_range if precision not allowed. *)

val neg : ?rnd:mpfr_rnd_t -> ?prec:int -> mpfr_float -> mpfr_float
(** Compute the negation of an [mpfr_float] number.
@raise Precision_range if precision not allowed. *)
val abs : ?rnd:mpfr_rnd_t -> ?prec:int -> mpfr_float -> mpfr_float
(** Compute the absolute value of an [mpfr_float] number.
@raise Precision_range if precision not allowed. *)
val dim : ?rnd:mpfr_rnd_t -> ?prec:int -> mpfr_float -> mpfr_float -> mpfr_float
(** [dim ~rnd:r ~prec:p x y] returs the positive difference of [x] and
[y] in precision [p], i.e., [x - y] rounded in the direction [r] if [x
> y], [+0] if [x <= y], and NaN if [x] or [y] is NaN.
@raise Precision_range if precision not allowed. *)
val mul_2int : ?rnd:mpfr_rnd_t -> ?prec:int -> mpfr_float -> int -> mpfr_float
val div_2int : ?rnd:mpfr_rnd_t -> ?prec:int -> mpfr_float -> int -> mpfr_float
(** [mul_2int ~rnd:r ~prec:p x y] (resp. [div_2int ~rnd:r ~prec:p x y]) returns [x]
times (resp. divided by) 2 raised to [y] in precision [p], rounded in the direction [r].
@raise Precision_range if precision not allowed. *)

(** {0 Comparison} *)
(** {0 Special} *)
(** {0 Input and Output} *)
(** {0 Integer and Remainder Related} *)
(** {0 Rounding Related} *)
(** {0 Miscellaneous} *)
(** {0 Exception Related} *)
