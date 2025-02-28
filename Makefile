all: pizza_deliv

pizza_deliv: dcarter.cpp aolmedo.cpp falrowhani.cpp lvaldivia.cpp \
	fandrade.cpp asteroids.cpp image.cpp \
	timers.cpp log.cpp animations.cpp
	g++ asteroids.cpp dcarter.cpp aolmedo.cpp falrowhani.cpp \
		lvaldivia.cpp fandrade.cpp image.cpp timers.cpp log.cpp \
		animations.cpp libggfonts.a \
		-Wall -lX11 -lGL -o pizza_deliv

clean:
	rm -f pizza_deliv

