CFLAGS=-g -Iinclude -Wall -lSDL2 -std=c++0x -pthread
EXEC=traffic
MKDIR_P = mkdir -p

all: directories $(EXEC)

directories: build

build:
	$(MKDIR_P) build

$(EXEC): build/display.o build/road.o build/vehicle.o build/driver.o build/main.o
	g++ build/display.o build/road.o build/vehicle.o build/driver.o build/main.o -o $(EXEC) $(CFLAGS)

build/main.o: src/main.cc
	g++ -c src/main.cc -o build/main.o $(CFLAGS)

build/vehicle.o: src/vehicle.cc
	g++ -c src/vehicle.cc -o build/vehicle.o $(CFLAGS)

build/driver.o: src/driver.cc
	g++ -c src/driver.cc -o build/driver.o $(CFLAGS)

build/road.o: src/road.cc
	g++ -c src/road.cc -o build/road.o $(CFLAGS)

build/display.o: src/display.cc
	g++ -c src/display.cc -o build/display.o $(CFLAGS)

clean:
	rm -rf build traffic
