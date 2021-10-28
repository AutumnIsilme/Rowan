CXX = g++
CC = gcc

CXXFLAGS := -std=c++2a -flto
CFLAGS := -Iinclude -Wall -Wextra -Wpedantic -Wno-c99-extensions
LDFLAGS := 

OBJS := src/main.o src/Frontend/Scanner.o src/Frontend/Math.o src/Error.o src/Timer.o src/Frontend/Parser.o
FILES := src/main.cpp src/Frontend/Scanner.cpp src/Frontend/Math.cpp src/Error.cpp src/Timer.cpp src/Frontend/Parser.cpp

%.o: %.cpp
	$(CXX) $(CFLAGS) $(CXXFLAGS) -c $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: test build clean release debug

all: build

build:
	mkdir -p build
	$(CXX) $(LDFLAGS) $(CXXFLAGS) $(CFLAGS) $(FILES) -o build/rwc.out

release: CFLAGS += -O3
release: CXXFLAGS += -D NDEBUG
release: build

dist: CXXFLAGS += -D NO_TIMERS
dist: release

debug: build

test: build
	build/rwc.out

celan: clean
clean:
	rm -rf src/*.o
	rm -rf src/*.d
	rm -rf src/Frontend/*.o
	rm -rf src/Frontend/*.d
	rm -rf srcpp/*.o
	rm -rf srcpp/*.d
	rm -rf build