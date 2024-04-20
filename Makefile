CC=g++
CFLAGS = -g -std=c++20 -Wall

LIBS = -lncurses

clock: main.o tui.o clock.o clockMenu.o frame.o digit.o
	$(CC) -o clock main.o tui.o clock.o clockMenu.o frame.o digit.o $(CFLAGS) $(LIBS)
	rm *.o

main.o: src/main.cpp src/tui.hpp src/clock.hpp src/clockMenu.hpp
	$(CC) -c src/main.cpp $(CFLAGS)

tui.o: src/tui.cpp src/tui.hpp
	$(CC) -c src/tui.cpp $(CFLAGS)

clock.o: src/clock.cpp src/clock.hpp
	$(CC) -c src/clock.cpp $(CFLAGS)

clockMenu.o: src/clockMenu.cpp src/clockMenu.hpp
	$(CC) -c src/clockMenu.cpp $(CFLAGS)

frame.o: src/frame.cpp src/frame.hpp
	$(CC) -c src/frame.cpp $(CFLAGS)

digit.o: src/digit.cpp src/digit.hpp
	$(CC) -c src/digit.cpp $(CFLAGS)

clean:
	rm clock
