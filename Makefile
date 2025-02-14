CFLAGS = -I ./include
##LIB    = ./libggfonts.so
LFLAGS = -lrt -lX11 -lGLU -lGL -pthread -lm #-lXrandr

all: asteroids

asteroids: asteroids.cpp dcarter.cpp log.cpp timers.cpp dcarter.h image.cpp
	g++ $(CFLAGS) asteroids.cpp log.cpp timers.cpp dcarter.cpp image.cpp libggfonts.a -Wall -Wextra $(LFLAGS) -oasteroids

clean:
	rm -f asteroids
	rm -f *.o

