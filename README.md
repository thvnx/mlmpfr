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

```bash
ocamlfind ocamlopt -o a.out -linkpkg -package mlmpfr file.ml -cclib -lmpfr
```
