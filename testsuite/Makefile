TESTS=initializationfunctions conversionfunctions basicarithmeticfunctions comparisonfunctions \
	specialfunctions integerandremainderrelatedfunctions roundingrelatedfunctions \
	miscellaneousfunctions exceptionrelatedfunctions

all:
	@for tst in $(TESTS) ; do \
		ocamlc -I ../_build/src -custom -o $$tst.ocaml ../_build/src/mpfr.cmo common.ml $$tst.ml ../_build/src/mlmpfr_stubs.o -cclib -lmpfr ; \
		gcc -o $$tst.gcc $$tst.c -lmpfr ; \
	done

check: all
	@for tst in $(TESTS) ; do \
		./$$tst.ocaml > /tmp/out.ocaml ; \
		./$$tst.gcc > /tmp/out.gcc ; \
		diff /tmp/out.ocaml /tmp/out.gcc ; \
		if [ "$$?" == "0" ]; then \
			echo "[PASS] $$tst" ; \
		else \
			echo "[FAIL] $$tst" ; \
		fi ;\
	done

clean:
	@rm -f *.ocaml *.gcc *.o *.cmi *.cmo
