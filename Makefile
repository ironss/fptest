

check: fptest
	./fptest
.PHONY: check

fptest: fptest.c
	gcc -o $@ $<
	
clean:
	rm fptest
.PHONY: clean

