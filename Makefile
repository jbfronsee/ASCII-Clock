CC=g++
CFLAGS = -g -std=c++20 -Wall

LIBS = -lncurses

bin/clock: bin/main.o bin/tui.o bin/config.o bin/clock.o bin/time.o bin/analogDisplay.o bin/clockMenu.o bin/digitalDisplay.o bin/digit.o bin/
	$(CC) -o bin/clock bin/main.o bin/tui.o bin/config.o bin/clock.o bin/time.o bin/analogDisplay.o bin/clockMenu.o bin/digitalDisplay.o bin/digit.o $(CFLAGS) $(LIBS)
	rm bin/*.o

bin/main.o: src/main.cpp src/tui/tui.hpp src/config/config.hpp src/clock/clock.hpp src/menu/clockMenu.hpp bin/
	$(CC) -c src/main.cpp -o bin/main.o $(CFLAGS)

bin/tui.o: src/tui/tui.cpp src/tui/tui.hpp bin/
	$(CC) -c src/tui/tui.cpp -o bin/tui.o $(CFLAGS)

bin/config.o: src/config/config.cpp src/config/config.hpp bin/
	$(CC) -c src/config/config.cpp -o bin/config.o $(CFLAGS)

bin/clock.o: src/clock/clock.cpp src/clock/clock.hpp bin/
	$(CC) -c src/clock/clock.cpp -o bin/clock.o $(CFLAGS)

bin/time.o: src/clock/time/time.cpp src/clock/time/time.hpp bin/
	$(CC) -c src/clock/time/time.cpp -o bin/time.o $(CFLAGS)

bin/analogDisplay.o: src/clock/analog/analogDisplay.cpp src/clock/analog/analogDisplay.hpp bin/
	$(CC) -c src/clock/analog/analogDisplay.cpp -o bin/analogDisplay.o $(CFLAGS)

bin/clockMenu.o: src/menu/clockMenu.cpp src/menu/clockMenu.hpp bin/
	$(CC) -c src/menu/clockMenu.cpp -o bin/clockMenu.o $(CFLAGS)

bin/digitalDisplay.o: src/clock/digital/digitalDisplay.cpp src/clock/digital/digitalDisplay.hpp bin/
	$(CC) -c src/clock/digital/digitalDisplay.cpp -o bin/digitalDisplay.o $(CFLAGS)

bin/digit.o: src/clock/digital/digit.cpp src/clock/digital/digit.hpp bin/
	$(CC) -c src/clock/digital/digit.cpp -o bin/digit.o $(CFLAGS)

bin/:
	mkdir bin

clean:
	rm -f bin/clock
	rm -f bin/*.o
