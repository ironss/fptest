
EXES=fptest-O0 fptest-O1 fptest-O2 fptest-O3 fptest-Os fptest-Og

all: $(EXES)

check: $(EXES)
	./fptest-O0
	./fptest-O1
	./fptest-O2
	./fptest-O3
	./fptest-Os
	./fptest-Og

.PHONY: check


fptest-O0: fptest.c
	gcc -O0 -o $@ $<

fptest-O1: fptest.c
	gcc -O1 -o $@ $<

fptest-O2: fptest.c
	gcc -O2 -o $@ $<

fptest-O3: fptest.c
	gcc -O3 -o $@ $<

fptest-Os: fptest.c
	gcc -Os -o $@ $<

fptest-Og: fptest.c
	gcc -Og -o $@ $<

clean:
	rm -f $(EXES)
.PHONY: clean

