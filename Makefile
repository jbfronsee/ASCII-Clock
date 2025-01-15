CC=g++
CFLAGS = -g -std=c++20 -Wall

LIBS = -lncurses

bin/clock: bin/main.o bin/tui.o bin/clock.o bin/clockMenu.o bin/frame.o bin/digit.o bin/
	$(CC) -o bin/clock bin/main.o bin/tui.o bin/clock.o bin/clockMenu.o bin/frame.o bin/digit.o $(CFLAGS) $(LIBS)
	rm bin/*.o

bin/main.o: src/main.cpp src/tui/tui.hpp src/clock/clock.hpp src/menu/clockMenu.hpp bin/
	$(CC) -c src/main.cpp -o bin/main.o $(CFLAGS)

bin/tui.o: src/tui/tui.cpp src/tui/tui.hpp bin/
	$(CC) -c src/tui/tui.cpp -o bin/tui.o $(CFLAGS)

bin/clock.o: src/clock/clock.cpp src/clock/clock.hpp bin/
	$(CC) -c src/clock/clock.cpp -o bin/clock.o $(CFLAGS)

bin/clockMenu.o: src/menu/clockMenu.cpp src/menu/clockMenu.hpp bin/
	$(CC) -c src/menu/clockMenu.cpp -o bin/clockMenu.o $(CFLAGS)

bin/frame.o: src/clock/frame.cpp src/clock/frame.hpp bin/
	$(CC) -c src/clock/frame.cpp -o bin/frame.o $(CFLAGS)

bin/digit.o: src/clock/digit.cpp src/clock/digit.hpp bin/
	$(CC) -c src/clock/digit.cpp -o bin/digit.o $(CFLAGS)

bin/:
	mkdir bin

clean:
	rm bin/clock
