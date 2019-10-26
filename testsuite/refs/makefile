TESTS=initializationfunctions \
      basicarithmeticfunctions comparisonfunctions \
      specialfunctions integerandremainderrelatedfunctions \
      roundingrelatedfunctions \
	    miscellaneousfunctions exceptionrelatedfunctions

all:
	@for tst in $(TESTS) ; do \
		gcc -o $$tst.co $$tst.c -L/usr/local/lib -lmpfr; \
    ./$$tst.co > ../$$tst.expected; \
	done
