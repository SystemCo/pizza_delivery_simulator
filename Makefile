CFLAGS = -I ./include
##LIB    = ./libggfonts.so
LFLAGS = -lrt -lX11 -lGLU -lGL -pthread -lm -lpng #-lXrandr

all: asteroids

asteroids: asteroids.cpp dcarter.cpp log.cpp timers.cpp dcarter.h image.cpp image3.cpp
	g++ $(CFLAGS) asteroids.cpp log.cpp timers.cpp dcarter.cpp image.cpp image3.cpp libggfonts.a -Wall -Wextra $(LFLAGS) -oasteroids

clean:
	rm -f asteroids
	rm -f *.o

