AS = as
CC = cc
OBJCOPY = objcopy

SMASH_ASFLAGS =
SMASH_CPPFLAGS =
SMASH_CFLAGS = -fno-stack-protector
SMASH_LDFLAGS = -Wl,-zexecstack

smash: main.o
	$(CC) $(LDFLAGS) $(SMASH_LDFLAGS) -o $@ $^

main.o: main.c smash.inc
	$(CC) $(CPPFLAGS) $(SMASH_CPPFLAGS) $(CFLAGS) $(SMASH_CFLAGS) -c -o $@ $<

smash.inc: smash.bin codegen
	./codegen $< smash >$@

smash.bin: smash.o
	$(OBJCOPY) -O binary -j .text $< $@

smash.o: smash.s
	$(AS) $(ASFLAGS) $(SMASH_ASFLAGS) -o $@ $<

codegen: codegen.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) -o $@ $<

.PHONY: clean
clean:
	$(RM) smash main.o smash.inc smash.bin smash.o codegen
