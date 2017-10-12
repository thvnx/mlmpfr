all:
	ocamlc -c mlmpfr.ml
	ocamlc -c mlmpfr_stubs.c
	ocamlc -custom -o mlmpfr unix.cma mlmpfr.cmo test.ml mlmpfr_stubs.o -cclib -lmpfr
