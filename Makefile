all:
	ocamlc -c mlmpfr.ml
	ocamlc -c mlmpfr_stubs.c

check: all
	cd testsuite && make check

doc: mlmpfr.ml
	mkdir doc
	ocamldoc -html -d doc mlmpfr.ml

clean:
	rm -f *.cmi *.cmo *.o
	rm -rf doc
	cd testsuite && make clean
