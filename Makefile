all: pizza_deliv

pizza_deliv: dcarter.cpp aolmedo.cpp falrowhani.cpp lvaldivia.cpp \
	fandrade.cpp asteroids.cpp image.cpp \
	timers.cpp log.cpp \
	dcarter.h aolmedo.h falrowhani.h lvaldivia.h fandrade.h shared.h \
	image.h log.h
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

generic_test: dcarter.cpp aolmedo.cpp falrowhani.cpp lvaldivia.cpp \
	fandrade.cpp asteroids.cpp image.cpp \
	timers.cpp log.cpp
	g++ asteroids.cpp dcarter.cpp aolmedo.cpp falrowhani.cpp \
		lvaldivia.cpp fandrade.cpp image.cpp timers.cpp log.cpp \
		libggfonts.a \
		-D GENERIC_TEST \
		-Wall -lX11 -lGL -o generic_test

preprocessing: aolmedo.cpp dcarter.cpp falrowhani.cpp fandrade.cpp \
	lvaldivia.cpp \
	asteroids.cpp image.cpp \
	timers.cpp log.cpp
	g++ asteroids.cpp dcarter.cpp aolmedo.cpp falrowhani.cpp \
		lvaldivia.cpp fandrade.cpp image.cpp timers.cpp log.cpp \
		libggfonts.a \
		-C -E > preprocessing.cpp

sound_test: dcarter.cpp aolmedo.cpp falrowhani.cpp lvaldivia.cpp \
	fandrade.cpp asteroids.cpp image.cpp \
	timers.cpp log.cpp \
	dcarter.h aolmedo.h falrowhani.h lvaldivia.h fandrade.h shared.h \
	image.h log.h
	g++ asteroids.cpp dcarter.cpp aolmedo.cpp falrowhani.cpp \
		lvaldivia.cpp fandrade.cpp image.cpp timers.cpp log.cpp \
		libggfonts.a \
		-Wall -lX11 -lGL -o sound_test \
		-D USE_OPENAL_SOUND \
		/usr/lib/x86_64-linux-gnu/libopenal.so \
		/usr/lib/x86_64-linux-gnu/libalut.so

clean:
	rm -f pizza_deliv sleep_test generic_test sound_test
