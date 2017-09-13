EXES=vgrab

all: $(EXES)

check: $(EXES)
	./vgrab

.PHONY: check


vgrab: vgrab.c
	gcc -Og -o $@ $<


clean:
	rm -f $(EXES)
.PHONY: clean

