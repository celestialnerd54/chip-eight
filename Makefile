CC = clang

TARG = chip
OBJS = main.o stack.o cpu.o display.o


$(TARG): $(OBJS)
	@echo [LD] $@
	@$(CC) $(OBJS) -o $@

%.o: %.c 
	@echo [CC] $@
	@$(CC) -o $@ -c $<

clean:
	@rm -rf $(TARG) $(OBJS)
