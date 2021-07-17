CC=gcc
WARNINGS=-Wall -Wstrict-prototypes
CFLAGS=-O2 $(WARNINGS) -g
PROGRAM=buff

SRC=main.c bufferline.c

HDR=bufferline.h

OBJ=main.o bufferline.o

$(PROGRAM): $(OBJ)
	$(CC) -o $@ $(OBJ) $(LIBS)
	
debug: $(OBJ)
	$(CC) -g -o $@ $(OBJ) $(LIBS)

clean:
	@rm -f $(PROGRAM) tags lintout *.o debug
