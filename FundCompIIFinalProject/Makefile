all:    main
main: main.o Player.o
        g++ main.o Player.o -o main

main.o: main.cpp
        g++ -c main.cpp
Player.o: Player.cpp
        g++ -c Player.cpp

clean:
        rm *.o main
