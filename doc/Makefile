html:
	mkdir -p html
	ocamldoc -html -d html ../mpfr.mli
	@sed -i -e 's/-><br>      /->/g' html/Mpfr.html
	@ln -s html/index.html mlmpfr.html

pdf:
	mkdir -p latex
	ocamldoc -latex -o latex/mlmpfr.tex ../mpfr.mli
	cd latex && latexmk -pdf mlmpfr.tex
	@ln -s latex/mlmpfr.pdf mlmpfr.pdf

all: pdf html

clean:
	rm -rf html latex
	rm -f mlmpfr.html mlmpfr.pdf
