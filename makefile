LDFLAGS = -lSDL -lSDL_image
OBJ = main.o jeu.o bibMario.o fmap.o
CC = g++
CC_OPT = -Wall

MarioTSP : main.o jeu.o bibMario.o fmap.o
	$(CC) $(LDFLAGS) $(CC_OPT) $(OBJ) -o MarioTSP 

main.o : main.cpp bibMario.h jeu.h
	$(CC) $(LDFLAGS) $(CC_OPT) -c main.cpp

jeu.o : jeu.cpp jeu.h
	$(CC) $(LDFLAGS) $(CC_OPT) -c jeu.cpp

bibMario.o : bibMario.cpp bibMario.h
	$(CC) $(LDFLAGS) $(CC_OPT) -c bibMario.cpp

fmap.o : fmap.cpp
	$(CC) $(LDFLAGS) $(CC_OPT) -c fmap.cpp
