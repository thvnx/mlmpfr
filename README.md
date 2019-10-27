| master | mlmpfr.4.0.2 | mlmpfr.4.0.1 | mlmpfr.4.0.0 | mlmpfr.3.1.6 |
|--------|--------------|--------------|--------------|--------------|
| [![Build Status](https://travis-ci.com/thvnx/mlmpfr.svg?branch=master)](https://travis-ci.com/thvnx/mlmpfr) | [![Build Status](https://travis-ci.com/thvnx/mlmpfr.svg?branch=release_402)](https://travis-ci.com/thvnx/mlmpfr) | [![Build Status](https://travis-ci.com/thvnx/mlmpfr.svg?branch=release_401)](https://travis-ci.com/thvnx/mlmpfr) | [![Build Status](https://travis-ci.com/thvnx/mlmpfr.svg?branch=release_400)](https://travis-ci.com/thvnx/mlmpfr) | [![Build Status](https://travis-ci.com/thvnx/mlmpfr.svg?branch=release_316)](https://travis-ci.com/thvnx/mlmpfr) |

(tested on linux and osx)

# mlmpfr
OCaml bindings for MPFR.

#### build and install

Building *mlmpfr.4.0.2* depends on [_dune_](https://github.com/ocaml/dune) (an
OCaml build system), _ocaml_ version >= 4.04, and _MPFR_ library version 4.0.2
(see footnote for building older _mlmpfr_ releases). Basically you just need to
install _mlmpfr_ via the _opam_ package manager, which will triggers all the
dependencies (such as _dune_ for example).

- From sources (github repo or with latest
[releases](https://github.com/thvnx/mlmpfr/releases)): in _mlmpfr_ main
directory, on branch `master` or `release_402`. Make sure that you have the
proper _MPFR_ library version installed on your system because _mlmpfr_ won't
check for it (see `utils/mpfr_version.c`).

```bash
dune build @install @runtest
```

- From _opam_ (targeting _MPFR 4.0.2_):

```bash
opam install mlmpfr.4.0.2
# `opam remove mlmpfr` to remove the package.
```

#### documentation

Documentation depends on package [_odoc_](https://github.com/ocaml/odoc).

```bash
dune build @doc
```
then, see `_build/default/_doc/_html/index.html`. An online version
is available [here](https://thvnx.github.io/mlmpfr/Mpfr.html).

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
$ ocamlfind ocamlc -package mlmpfr -linkpkg example.ml -o a.out
```
will result in:

```bash
$ ./a.out
9.449569463147377e-01
```

You can also use _dune_ with

```bash
$ dune exec examples/example.exe
9.449569463147377e-01
```
----

##### Note: install an older release of _mlmpfr_

Older releases of mlmpfr (3.1.6, 4.0.0, and 4.0.1) depend on
[_oasis_](http://oasis.forge.ocamlcore.org/), an obsolete build system replaced
by dune since `mlmpfr.4.0.2`. Use _opam_ if you need to install an older release
of mlmpfr, as for example:

```bash
opam install mlmpfr.3.1.6
```

Or, you can build it from the sources, as for example from branch _release_316_:

```bash
oasis setup
./configure --enable-tests
make
make test
make install
# `make uninstall` to remove mlmpfr library.
```

opam packages `mlmpfr.4.0.0` and `mlmpfr.4.0.1` also exist and are suitable for
_MPFR 4.0.0_ and _4.0.1_ versions.

##### Note: build examples with an older release of _mlmpfr_

You'll need to link with `-cclib -lmpfr` (along with `ocamlopt`) if you are
using released versions of mlmpfr (as the ones provided by _opam_), since mlmpfr
wasn't linked with mpfr by default before.
