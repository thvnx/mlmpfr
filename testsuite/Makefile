# Instructions to build tests, linked to a local installation of mpfr,
# assuming library installed in /usr/local/lib:
# -> ocamlc: add "-ccopt -L/usr/local/lib" flag,
# -> gcc: add "-L/usr/local/lib" flag,
# then run with:
# LD_LIBRARY_PATH=/usr/local/lib make check

TESTS=initializationfunctions conversionfunctions basicarithmeticfunctions comparisonfunctions \
	specialfunctions integerandremainderrelatedfunctions roundingrelatedfunctions \
	miscellaneousfunctions exceptionrelatedfunctions

all:
	@for tst in $(TESTS) ; do \
		ocamlc -I ../_build/src -custom -o $$tst.oo ../_build/src/mpfr.cmo common.ml $$tst.ml ../_build/src/mlmpfr_stubs.o -ccopt -L/usr/local/lib -cclib -lmpfr || exit 1 ; \
		gcc -o $$tst.co $$tst.c -L/usr/local/lib -lmpfr || exit 1 ; \
	done

check: all
	@for tst in $(TESTS) ; do \
		./$$tst.oo > ./$$tst.oo.out ; \
		./$$tst.co > ./$$tst.co.out ; \
		diff ./$$tst.oo.out ./$$tst.co.out ; \
		if [ "$$?" = "0" ]; then \
			echo "[PASS] $$tst" ; \
		else \
			echo "[FAIL] $$tst" ; \
			exit 1 ; \
		fi ;\
	done
	@diff ./fpif_export.oo.data ./fpif_export.co.data ; \
		if [ "$$?" = "0" ]; then \
			echo "[PASS] fpif_export data" ; \
		else \
			echo "[FAIL] fpif_export data" ; \
			exit 1 ; \
		fi ;\

clean:
	@rm -f *.oo *.co *.cmi *.cmo *.oo.out *.co.out *.*o.data
