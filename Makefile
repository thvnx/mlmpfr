all:
	ocamlc -c mlmpfr.ml
	ocamlc -c mlmpfr_stubs.c

check: all
	cd testsuite && make check

clean:
	rm -f *.cmi *.cmo *.o
	cd testsuite && make clean
