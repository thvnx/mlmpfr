# mlmpfr
OCaml bindings for MPFR.

#### build and install

From source: in mlmpfr main directory.

```bash
oasis setup
./configure --enable-tests
make
make test
make install
# `make uninstall` to remove mlmpfr library.
```

With _opam_ (comming soon)

```bash
opam install mlmpfr
# `opam remove mlmpfr` to remove the package.
```

#### documentation

```bash
make doc # Generate HTML documentation
```
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
