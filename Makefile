all:
	ocamlc -c mlmpfr.ml
	ocamlc -c mlmpfr_stubs.c
	ocamlc -c mpfr.mli
	ocamlc -c mpfr.ml

check: all
	cd testsuite && make check

doc: mpfr.mli
	mkdir -p doc
	ocamldoc -html -d doc mpfr.mli
	@sed -i -e 's/-><br>      /->/g' doc/Mpfr.html

clean:
	rm -f *.cmi *.cmo *.o
	rm -rf doc
	cd testsuite && make clean
