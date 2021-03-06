.SUFFIXES: .bin .o .o64 .obj .obj64 .exe .asm .lst .pl

NASM	= ../nasm
NASMOPT = -Ox -I../misc
PERL	= perl
TESTS	= $(wildcard *.asm)

%.bin: %.asm $(NASM)
	$(NASM) $(NASMOPT) -f bin -o $@ -l $*.lst $<

%.ith: %.asm $(NASM)
	$(NASM) $(NASMOPT) -f ith -o $@ -l $*.lst $<

%.srec: %.asm $(NASM)
	$(NASM) $(NASMOPT) -f srec -o $@ -l $*.lst $<

%.o: %.asm $(NASM)
	$(NASM) $(NASMOPT) -f elf32 -o $@ -l $*.lst $<

%.o64: %.asm $(NASM)
	$(NASM) $(NASMOPT) -f elf64 -o $@ -l $*.lst $<

%.obj: %.asm $(NASM)
	$(NASM) $(NASMOPT) -f obj -o $@ -l $*.lst $<

%.coff: %.asm $(NASM)
	$(NASM) $(NASMOPT) -f coff -o $@ -l $*.lst $<

%.win32: %.asm $(NASM)
	$(NASM) $(NASMOPT) -f win32 -o $@ -l $*.lst $<

%.win64: %.asm $(NASM)
	$(NASM) $(NASMOPT) -f win64 -o $@ -l $*.lst $<

%.mo32: %.asm $(NASM)
	$(NASM) $(NASMOPT) -f macho32 -o $@ -l $*.lst $<

%.mo64: %.asm $(NASM)
	$(NASM) $(NASMOPT) -f macho64 -o $@ -l $*.lst $<

%.dbg: %.asm $(NASM)
	$(NASM) $(NASMOPT) -f dbg -o $@ -l $*.lst $<

%.asm: %.pl
	$(PERL) $< > $@

all:

golden: performtest.pl $(TESTS)
	$(PERL) performtest.pl --golden --nasm='$(NASM)' $(TESTS)

test:	performtest.pl $(NASM) $(TESTS)
	$(PERL) performtest.pl --nasm='$(NASM)' $(TESTS)

diff:	performtest.pl $(NASM) $(TESTS)
	$(PERL) performtest.pl --diff --nasm='$(NASM)' $(TESTS)

clean:
	rm -f *.com *.o *.o64 *.obj *.win32 *.win64 *.exe *.lst *.bin
	rm -f *.dbg *.coff *.ith *.srec *.mo32 *.mo64
	rm -rf testresults
	rm -f elftest elftest64

spotless: clean
	rm -rf golden

#
# Test for ELF32 shared libraries; assumes an x86 Linux system
#
elfso.o: elfso.asm $(NASM)
	$(NASM) $(NASMOPT) -f elf32 -F stabs -o $@ -l $*.lst $<

elfso.so: elfso.o
	$(LD) -m elf_i386 -shared -o $@ $<

elftest: elftest.c elfso.so
	$(CC) -g -m32 -o $@ $^
	-env LD_LIBRARY_PATH=.:$$LD_LIBRARY_PATH ./elftest

#
# Test for ELF64 shared libraries; assumes an x86-64 Linux system
#
elf64so.o: elf64so.asm $(NASM)
	$(NASM) $(NASMOPT) -f elf64 -F dwarf -o $@ -l $*.lst $<

elf64so.so: elf64so.o
	$(LD) -shared -o $@ $<

elftest64: elftest64.c elf64so.so
	$(CC) -g -o $@ $^
	-env LD_LIBRARY_PATH=.:$$LD_LIBRARY_PATH ./elftest64
