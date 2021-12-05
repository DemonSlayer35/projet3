CC=gcc
CFLAGS=-I.

wpi: 
	$(CC) main.c gpio-wpi.c -l wiringPi -o rpi-gpio $(CFLAGS)
libc: 
	$(CC) main.c gpio-libc.c -o rpi-gpio $(CFLAGS)
