all: prog-e-centric prog-s-hidden prog-s-centric

prog-e-centric: functions.o e-centric.o
		gcc -o prog-e-centric functions.o e-centric.o

prog-s-hidden: functions.o s-hidden.o
		gcc -o prog-s-hidden functions.o s-hidden.o

prog-s-centric: functions.o s-centric.o
		gcc -o prog-s-centric functions.o s-centric.o

functions.o: functions.c
		gcc -c functions.c

functionsh.o: functions.h
		gcc -c funtionc.h

s-centric.o: s-centric.c
		gcc -c s-centric.c

s-hidden.o: s-hidden.c
		gcc -c s-hidden.c

e-centric.o: e-centric.c
		gcc -c e-centric.c

clean:
		rm prog-s-centric prog-s-hidden prog-e-centric