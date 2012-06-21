CC=$(CROSS_COMPILE)gcc

TARGET=jstest
CFILES=jstest.c

OBJS=$(CFILES:.c=.o)
DEPS=$(OBJS:.o=.d)


all: $(TARGET)

$(TARGET): $(OBJS) Makefile
	$(CC) $(VERBOSE) $(OBJS) $(OFLAGS) $(LIBFLAGS) $(SLIBS) -o $@

%.o: %.c
	$(CC) $(VERBOSE) $(CFLAGS) -o $@ -c $<

clean:
	$(RM) *.o *.gdb $(TARGET) $(DEPS)


-include $(DEPS)
