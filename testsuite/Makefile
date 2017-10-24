all:
	ocamlc -I .. -custom -o initializationfunctions.ocaml ../mlmpfr.cmo ../mpfr.cmo initializationfunctions.ml ../mlmpfr_stubs.o -cclib -lmpfr
	gcc -o initializationfunctions.gcc initializationfunctions.c -lmpfr

check: all
	./initializationfunctions.ocaml > /tmp/out1
	./initializationfunctions.gcc > /tmp/out2
	diff /tmp/out1 /tmp/out2

clean:
	rm -f *.ocaml *.gcc *.o *.cmi *.cmo
