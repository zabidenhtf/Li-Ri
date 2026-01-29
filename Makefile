TARGETS = $(wildcard src/*.cpp)
LDFLAGS = -lz -lpng -lglfw -lGL -lGLU -lX11 -lpthread -lrt -l dl
CXX = g++
EXEC = lirienginetest

all:
	$(CXX) $(TARGETS) $(LDFLAGS) -o $(EXEC)
