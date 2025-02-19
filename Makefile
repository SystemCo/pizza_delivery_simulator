#CFLAGS = -I ./include
CFLAGS = 
##LIB    = ./libggfonts.so
LFLAGS = -lrt -lX11 -lGLU -lGL -pthread -lm -lpng #-lXrandr


all: objects/dcarter.o objects/log.o objects/timers.o \
	objects/image.o asteroids 

objects/dcarter.o: dcarter.cpp dcarter.h
	g++ -c -o objects/dcarter.o dcarter.cpp

objects/log.o: log.cpp log.h
	g++ -c -o objects/log.o log.cpp

objects/timers.o: timers.cpp
	g++ -c -o objects/timers.o timers.cpp

objects/image.o: image.cpp shared.h dcarter.h
	g++ -c -o objects/image.o image.cpp

asteroids: asteroids.cpp objects/dcarter.o objects/log.o \
	objects/timers.o objects/image.o
	g++ $(CFLAGS) asteroids.cpp objects/log.o objects/timers.o \
		objects/dcarter.o objects/image.o libggfonts.a \
		-Wall -Wextra $(LFLAGS) -oasteroids

clean:
	rm -f asteroids
	rm -f objects/*.o

