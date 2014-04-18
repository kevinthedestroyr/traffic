CFLAGS=-g -Iinclude -Wall
EXEC=traffic

all: $(EXEC)

$(EXEC): build/Road.o build/Vehicle.o build/Driver.o build/Main.o
	g++ build/Road.o build/Vehicle.o build/Driver.o build/Main.o -o $(EXEC) $(CFLAGS)

build/Main.o: src/Main.cpp
	g++ -c src/Main.cpp -o build/Main.o $(CFLAGS)

build/Vehicle.o: src/Vehicle.cpp
	g++ -c src/Vehicle.cpp -o build/Vehicle.o $(CFLAGS)

build/Driver.o: src/Driver.cpp
	g++ -c src/Driver.cpp -o build/Driver.o $(CFLAGS)

build/Road.o: src/Road.cpp
	g++ -c src/Road.cpp -o build/Road.o $(CFLAGS)

clean:
	rm -rf build traffic
