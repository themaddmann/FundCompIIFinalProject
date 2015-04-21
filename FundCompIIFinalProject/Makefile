all:	main
main: main.o Person.o Player.o Level.o Door.o DoorKey.o Enemy.o
	g++ -w -lSDL2 -lSDL2_image main.o Person.o Player.o Level.o Door.o DoorKey.o Enemy.o -o main

main.o: main.cpp
	g++ -c main.cpp
Person.o: Person.cpp
	g++ -c Person.cpp
Player.o: Player.cpp
	g++ -c Player.cpp
Level.o: Level.cpp
	g++ -c Level.cpp
Door.o: Door.cpp
	g++ -c Door.cpp
DoorKey.o: DoorKey.cpp
	g++ -c DoorKey.cpp
Enemy.o: Enemy.cpp
	g++ -c Enemy.cpp

clean:
	rm *.o main

