all:
	ocamlc -I .. -custom -o initializationfunctions.ocaml ../mlmpfr.cmo ../mpfr.cmo initializationfunctions.ml ../mlmpfr_stubs.o -cclib -lmpfr
	ocamlc -I .. -custom -o conversionfunctions.ocaml ../mlmpfr.cmo ../mpfr.cmo conversionfunctions.ml ../mlmpfr_stubs.o -cclib -lmpfr
	gcc -o initializationfunctions.gcc initializationfunctions.c -lmpfr
	gcc -o conversionfunctions.gcc conversionfunctions.c -lmpfr

check: all
	./initializationfunctions.ocaml > /tmp/out1
	./initializationfunctions.gcc > /tmp/out2
	diff /tmp/out1 /tmp/out2
	./conversionfunctions.ocaml > /tmp/out1
	./conversionfunctions.gcc > /tmp/out2
	diff /tmp/out1 /tmp/out2

clean:
	rm -f *.ocaml *.gcc *.o *.cmi *.cmo
