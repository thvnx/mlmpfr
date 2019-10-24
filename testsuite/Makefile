# ocamlc -> -ccopt -L/usr/local/lib
# gcc -> -L/usr/local/lib
# make check -> LD_LIBRARY_PATH=/usr/local/lib make check

TESTS=initializationfunctions conversionfunctions basicarithmeticfunctions comparisonfunctions \
	specialfunctions integerandremainderrelatedfunctions roundingrelatedfunctions \
	miscellaneousfunctions exceptionrelatedfunctions

all:
	@for tst in $(TESTS) ; do \
		ocamlc -I ../_build/src -custom -o $$tst.ocaml ../_build/src/mpfr.cmo common.ml $$tst.ml ../_build/src/mlmpfr_stubs.o -ccopt -L/usr/local/lib -cclib -lmpfr || exit 1 ; \
		gcc -o $$tst.gcc $$tst.c -L /usr/local/lib -lmpfr || exit 1 ; \
	done

check: all
	@for tst in $(TESTS) ; do \
		./$$tst.ocaml > /tmp/out.ocaml ; \
		./$$tst.gcc > /tmp/out.gcc ; \
		diff /tmp/out.ocaml /tmp/out.gcc ; \
		if [ "$$?" = "0" ]; then \
			echo "[PASS] $$tst" ; \
		else \
			echo "[FAIL] $$tst" ; \
			exit 1 ; \
		fi ;\
	done
	@diff ./fpif_export.ocaml.data ./fpif_export.c.data ; \
		if [ "$$?" = "0" ]; then \
			echo "[PASS] fpif_export data" ; \
		else \
			echo "[FAIL] fpif_export data" ; \
			exit 1 ; \
		fi ;\

clean:
	@rm -f *.ocaml *.gcc *.o *.cmi *.cmo
