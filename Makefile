CC	= gcc
CXX	= g++

GRAPHICS	= display.o model.o mesh.o light.o shader.o texture.o transform.o camera.o
SYSTEM		= time.o cameraEventHandler.o
CXX_FLAGS	= -std=c++11
INCLUDE		= -Iinclude/

OBJECTS 	:=
C_OS		:=
LIBS		:=
ifeq ($(OS),Windows_NT)
	OBJECTS += main.o $(GRAPHICS) $(SYSTEM) glad.o
	C_OS += Windows
	LIBS += -lglfw3 -lopengl32 -lglu32 -lgdi32 -luser32 -lkernel32 -lassimp
else
	OBJECTS += glad.o $(SYSTEM) $(GRAPHICS) main.o
	C_OS += Linux
	LIBS += -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl -lassimp
endif

all: os build trash

os:
	@echo $(C_OS)

build: $(OBJECTS)
	$(CXX) $(CXX_FLAGS) $(OBJECTS) $(INCLUDE) $(LIBS) -o main

glad.o: src/glad.c
	$(CC) -c src/glad.c

# GRAPHICS
display.o: src/graphics/display.cpp
	$(CXX) $(CXX_FLAGS) $(INCLUDE) -c src/graphics/display.cpp

model.o: src/graphics/model.cpp
	$(CXX) $(CXX_FLAGS) $(INCLUDE) -c src/graphics/model.cpp

mesh.o: src/graphics/mesh.cpp
	$(CXX) $(CXX_FLAGS) $(INCLUDE) -c src/graphics/mesh.cpp

light.o: src/graphics/light.cpp
	$(CXX) $(CXX_FLAGS) $(INCLUDE) -c src/graphics/light.cpp

shader.o: src/graphics/shader.cpp
	$(CXX) $(CXX_FLAGS) $(INCLUDE) -c src/graphics/shader.cpp

texture.o: src/graphics/texture.cpp
	$(CXX) $(CXX_FLAGS) $(INCLUDE) -c src/graphics/texture.cpp

transform.o: src/graphics/transform.cpp
	$(CXX) $(CXX_FLAGS) $(INCLUDE) -c src/graphics/transform.cpp

camera.o: src/graphics/camera.cpp
	$(CXX) $(CXX_FLAGS) $(INCLUDE) -c src/graphics/camera.cpp

# SYSTEM
time.o: src/system/time.cpp
	$(CXX) $(CXX_FLAGS) $(INCLUDE) -c src/system/time.cpp

cameraEventHandler.o: src/system/cameraEventHandler.cpp
	$(CXX) $(CXX_FLAGS) $(INCLUDE) -c src/system/cameraEventHandler.cpp

# MAIN
main.o: src/main.cpp
	$(CXX) $(CXX_FLAGS) $(INCLUDE) -c src/main.cpp

trash:
	rm -rf *.o

clean:
	rm -rf *.o main
