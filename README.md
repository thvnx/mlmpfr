| master | mlmpfr.4.0.2 | mlmpfr.4.0.1 | mlmpfr.4.0.0 | mlmpfr.3.1.6 |
|--------|--------------|--------------|--------------|--------------|
| [![Build Status](https://travis-ci.com/thvnx/mlmpfr.svg?branch=master)](https://travis-ci.com/thvnx/mlmpfr) | [![Build Status](https://travis-ci.com/thvnx/mlmpfr.svg?branch=release_402)](https://travis-ci.com/thvnx/mlmpfr) | [![Build Status](https://travis-ci.com/thvnx/mlmpfr.svg?branch=release_401)](https://travis-ci.com/thvnx/mlmpfr) | [![Build Status](https://travis-ci.com/thvnx/mlmpfr.svg?branch=release_400)](https://travis-ci.com/thvnx/mlmpfr) | [![Build Status](https://travis-ci.com/thvnx/mlmpfr.svg?branch=release_316)](https://travis-ci.com/thvnx/mlmpfr) |

(tested on linux and osx)

# mlmpfr
OCaml bindings for MPFR.

#### build and install

Building *mlmpfr* depends on
[_oasis_](http://oasis.forge.ocamlcore.org/) (an OCaml build system),
_ocaml_ version >= 4.04, and _MPFR_ library version 3.1.6, 4.0.0,
4.0.1 or 4.0.2. Basically you just need to install _oasis_ via the
_opam_ package manager, which will triggers all the dependencies (such
as ocamlfind for example).

From sources (github repo or
[releases](https://github.com/thvnx/mlmpfr/releases)): in mlmpfr main
directory, on branch _release_316_ (resp. release mlmpfr.3.1.6) for
_MPFR 3.1.6_, _release_40[0-2]_ for _MPFR 4.0.[0-2]_ (resp. releases
mlmpfr.4.0.[0-2]).  Make sure that you have the proper
_MPFR_ library version installed because mlmpfr won't check for it.

```bash
oasis setup
./configure --enable-tests
make
make test
make install
# `make uninstall` to remove mlmpfr library.
```

From _opam_ (targeting _MPFR 3.1.6_).

```bash
opam install mlmpfr.3.1.6
# `opam remove mlmpfr` to remove the package.
```

Note: opam package `mlmpfr.4.0.0` also exists and its suitable for
_MPFR 4.0.0_, _4.0.1_ and _4.0.2_ versions.

#### documentation

Run:
```bash
make doc # Generate HTML documentation
```

or see an HTML version
[here](https://thvnx.github.io/mlmpfr/Mpfr.html).

#### usage

For example, let _example.ml_ as follows:

```ocaml
module M = Mpfr

let _ =
  let op = M.make_from_float (~-. 1. /. 3.) in
  Printf.printf "%s\n" (M.get_formatted_str (M.cos op))
```

Compile the above code with:

```bash
ocamlfind ocamlopt -o a.out -linkpkg -package mlmpfr example.ml -cclib -lmpfr
```
will results in:

```bash
$ ./a.out
9.449569463147377e-01
```
