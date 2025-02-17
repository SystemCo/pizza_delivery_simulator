CFLAGS = -I ./include
##LIB    = ./libggfonts.so
LFLAGS = -lrt -lX11 -lGLU -lGL -pthread -lm -lpng #-lXrandr

all: dcarter.o log.o timers.o image.o asteroids 

dcarter.o: dcarter.cpp dcarter.h
	g++ -c dcarter.cpp

log.o: log.cpp log.h
	g++ -c log.cpp

timers.o: timers.cpp
	g++ -c timers.cpp

image.o: image.cpp shared.h dcarter.h
	g++ -c image.cpp

asteroids: asteroids.cpp dcarter.cpp log.cpp timers.cpp dcarter.h image.cpp shared.h
	g++ $(CFLAGS) asteroids.cpp log.o timers.o dcarter.o image.o libggfonts.a -Wall -Wextra $(LFLAGS) -oasteroids

clean:
	rm -f asteroids
	rm -f *.o

