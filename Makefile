all: pizza_deliv

pizza_deliv: dcarter.cpp aolmedo.cpp falrowhani.cpp lvaldivia.cpp \
	fandrade.cpp asteroids.cpp image.cpp \
	timers.cpp log.cpp
	g++ asteroids.cpp dcarter.cpp aolmedo.cpp falrowhani.cpp \
		lvaldivia.cpp fandrade.cpp image.cpp timers.cpp log.cpp \
		libggfonts.a \
		-Wall -lX11 -lGL -o pizza_deliv

sleep_test: dcarter.cpp aolmedo.cpp falrowhani.cpp lvaldivia.cpp \
	fandrade.cpp asteroids.cpp image.cpp \
	timers.cpp log.cpp
	g++ asteroids.cpp dcarter.cpp aolmedo.cpp falrowhani.cpp \
		lvaldivia.cpp fandrade.cpp image.cpp timers.cpp log.cpp \
		libggfonts.a \
		-D SLEEP_TEST \
		-Wall -lX11 -lGL -o sleep_test

clean:
	rm -f pizza_deliv sleep_test

