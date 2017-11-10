all:
	ocamlc -c mlmpfr_stubs.c
	ocamlc -w +A-4 -c mpfr.mli
	ocamlc -w +A-4 -c mpfr.ml

check: all
	cd testsuite && make check

doc:
	cd doc && make html

doc-all:
	cd doc && make all

clean:
	rm -f *.cmi *.cmo *.o
	cd testsuite && make clean
	cd doc && make clean

.PHONY: doc doc-all
