all:
	ocamlc -custom -o assignmentfunctions.ocaml unix.cma ../mlmpfr.cmo assignmentfunctions.c ../mlmpfr_stubs.o -cclib -lmpfr
	ocamlc -custom -o initializationfunctions.ocaml unix.cma ../mlmpfr.cmo initializationfunctions.c ../mlmpfr_stubs.o -cclib -lmpfr
	gcc -o assignmentfunctions.gcc assignmentfunctions.c -lmpfr
	gcc -o initializationfunctions.gcc initializationfunctions.c -lmpfr

check: all
	./assignmentfunctions.ocaml > /tmp/out1
	./assignmentfunctions.gcc > /tmp/out2
	diff /tmp/out1 /tmp/out2
	./initializationfunctions.ocaml > /tmp/out1
	./initializationfunctions.gcc > /tmp/out2
	diff /tmp/out1 /tmp/out2

clean:
	rm -f *.ocaml *.gcc *.o
