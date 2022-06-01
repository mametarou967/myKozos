PREFIX = /usr/local
ARCH = h8300-elf
BINDIR = $(PREFIX)/bin
ADDNAME = $(ARCH)-

CC = $(BINDIR)/$(ADDNAME)gcc
OBJCOPY = $(BINDIR)/$(ADDNAME)objcopy

OBJS  = startup.o main.o interrupt.o
OBJS += lib.o serial.o
OBJS += kozos.o syscall.o test08_1.o

TARGET = kozos

CFLAGS =  -Wall -mh -nostdinc -nostdlib -fno-builtin
CFLAGS += -I.
CFLAGS += -Os
CFLAGS += -DKOZOS

LFLAGS = -static -T ld.scr -L.

.SUFFIXES: .c .o
.SUFFIXES: .s .o
.SUFFIXES: .S .o

all :			$(TARGET)

$(TARGET) :		$(OBJS)
				$(CC) -o $(TARGET) $(OBJS) $(CFLAGS) $(LFLAGS)

.c.o :			$<
				$(CC) -c $(CFLAGS) $<

.s.o :			$<
				$(CC) -c $(CFLAGS) $<

.S.o :			$<
				$(CC) -c $(CFLAGS) $<

clean :
				rm -f $(OBJS) $(TARGET) $(TARGET).elf
