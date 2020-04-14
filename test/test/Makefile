CC = xtensa-lx106-elf-gcc
CFLAGS = -I. -mlongcalls
LDLIBS = -nostdlib -Wl,--start-group -lmain -lnet80211 -lwpa -llwip -lpp -lphy -lcirom -lc -Wl,--end-group -lgcc
LDFLAGS = -Teagle.app.v6.ld

test-0x00000.bin: test
	esptool.py elf2image $^

test: test.o

test.o: test.c

flash: test-0x00000.bin
	esptool.py --baud 115200 --port /dev/ttyUSB0 write_flash 0 test-0x00000.bin 0x10000 test-0x10000.bin

clean:
	rm -f test test.o test-0x00000.bin test-0x10000.bin
