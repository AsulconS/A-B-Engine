CC	= gcc
CXX	= g++

GRAPHICS	= display.o shader.o camera.o texture.o
SYSTEM		= time.o
OBJECTS		= glad.o $(GRAPHICS) $(SYSTEM) main.o
CXX_FLAGS	= -std=c++11
INCLUDE		= -Iinclude/
LIBS		= -lglfw3 -lopengl32 -lglu32 -lgdi32 -luser32 -lkernel32

all: build trash

build: $(OBJECTS)
	$(CXX) $(CXX_FLAGS) $(OBJECTS) $(INCLUDE) $(LIBS) -o main

glad.o: src/glad.c
	$(CC) -c src/glad.c

# GRAPHICS
display.o: src/display.cpp
	$(CXX) $(CXX_FLAGS) $(INCLUDE) -c src/display.cpp

shader.o: src/shader.cpp
	$(CXX) $(CXX_FLAGS) $(INCLUDE) -c src/shader.cpp

camera.o: src/camera.cpp
	$(CXX) $(CXX_FLAGS) $(INCLUDE) -c src/camera.cpp

texture.o: src/texture.cpp
	$(CXX) $(CXX_FLAGS) $(INCLUDE) -c src/texture.cpp

time.o: src/time.cpp
	$(CXX) $(CXX_FLAGS) $(INCLUDE) -c src/time.cpp

main.o: src/main.cpp
	$(CXX) $(CXX_FLAGS) $(INCLUDE) -c src/main.cpp

trash:
	rm -rf *.o

clean:
	rm -rf *.o main
