CC=$(CROSS_COMPILE)gcc

TARGET=serial-link
CFILES=serial-link.c

OBJS=$(CFILES:.c=.o)
DEPS=$(OBJS:.o=.d)

IDIR=../include/mavlink/v1.0/common

all: $(TARGET)

$(TARGET): $(OBJS) Makefile
	$(CC) $(VERBOSE) $(OBJS) $(OFLAGS) $(LIBFLAGS) $(SLIBS) -o $@

%.o: %.c
	$(CC) $(VERBOSE) $(CFLAGS) -I $(IDIR) -o $@ -c $<

clean:
	$(RM) *.o *.gdb $(TARGET) $(DEPS)


-include $(DEPS)
