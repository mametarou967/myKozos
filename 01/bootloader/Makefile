PREFIX = /usr/local
ARCH = h8300-elf
BINDIR = $(PREFIX)/bin
ADDNAME = $(ARCH)-

CC = $(BINDIR)/$(ADDNAME)gcc
OBJCOPY = $(BINDIR)/$(ADDNAME)objcopy

H8WRITE = ../../kz_h8write-v0.2.1/PackageFiles/src/kz_h8write
H8WRITE_SERDEV = /dev/ttyS1

OBJS  = vector.o main.o startup.o

TARGET = kzload

CFLAGS = -Wall -mh -nostdinc -nostdlib -fno-builtin

LFLAGS = -static -T ld.scr -L.

all :			$(TARGET)

$(TARGET) :		$(OBJS)
				$(CC) -o $(TARGET) $(OBJS) $(CFLAGS) $(LFLAGS)

.c.o :			$<
				$(CC) -c $(CFLAGS) $<

.s.o :			$<
				$(CC) -c $(CFLAGS) $<

$(TARGET).mot : $(TARGET)
				$(OBJCOPY) -O srec $(TARGET) $(TARGET).mot 

image : 		$(TARGET).mot

write : 		$(TARGET).mot
				$(H8WRITE) -3069 -f20 $(TARGET).mot $(H8WRITE_SERDEV)

clean :
				rm -f $(OBJS) $(TARGET) $(TARGET).mot
