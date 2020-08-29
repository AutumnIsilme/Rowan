CXX = clang++
CC = gcc

CXXFLAGS := -std=c++1z
CFLAGS := -std=c11
LDFLAGS := 

OBJS := src/main.o src/Scanner.o src/Token.o src/Timer.o

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: test build clean

all: build

build: $(OBJS)
	mkdir -p build
	$(CC) $(LDFLAGS) $(OBJS) -o build/rwc.out

release: CFLAGS += -O3 -D FASTBUILD
release: CXXFLAGS += -O3
release: $(OBJS)
release: build

test: build
	./build/rwc.out

clean:
	rm -rf src/*.o
	rm -rf src/*.d
	rm -rf srcpp/*.o
	rm -rf srcpp/*.d
	rm -rf build