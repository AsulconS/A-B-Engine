CC	= gcc
CXX	= g++

CC_STANDARD       = -std=c11
CXX_STANDARD      = -std=c++11
CXX_WSTD_FLAGS    = -Wall -Wextra
CXX_EXTRA_FLAGS   = -Wshadow -Wnon-virtual-dtor -pedantic
CXX_WARNING_FLAGS = $(CXX_WSTD_FLAGS) $(CXX_EXTRA_FLAGS)

CC_FLAGS  = $(CC_STANDARD)
CXX_FLAGS = $(CXX_STANDARD) $(CXX_WARNING_FLAGS)

CXX_LIBS  = -static-libgcc -static-libstdc++ -Wl,-Bstatic -lstdc++ -lpthread

INCLUDE_PATH = -Iinclude -Iexternal/include

GRAPHICS	= display.o model.o mesh.o light.o shader.o texture.o transform.o camera.o
SYSTEM		= time.o cameraEventHandler.o

OBJECTS 	:=
C_OS		:=
STATIC_LIBS :=
ifeq ($(OS),Windows_NT)
    OBJECTS += main.o $(GRAPHICS) $(SYSTEM) glad.o
    C_OS += Windows
    LIBRARY_PATH = -Lexternal/bin/win_x64 -L.
    STATIC_LIBS += -lglfw3 -lopengl32 -lglu32 -lgdi32 -luser32 -lkernel32 -lassimp
else
    OBJECTS += glad.o $(SYSTEM) $(GRAPHICS) main.o
    LIBRARY_PATH :=
    C_OS += Linux
    STATIC_LIBS += -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl -lassimp
endif

all: os build trash

os:
	@echo $(C_OS)

build: $(OBJECTS)
	$(CXX) $(CXX_FLAGS) $(OBJECTS) $(INCLUDE_PATH) $(LIBRARY_PATH) $(STATIC_LIBS) -o main $(CXX_LIBS)

glad.o: external/src/glad.c
	$(CC) -c $(CC_FLAGS) $(INCLUDE_PATH) external/src/glad.c

# GRAPHICS
display.o: src/graphics/display.cpp
	$(CXX) -c $(CXX_FLAGS) $(INCLUDE_PATH) src/graphics/display.cpp

model.o: src/graphics/model.cpp
	$(CXX) -c $(CXX_FLAGS) $(INCLUDE_PATH) src/graphics/model.cpp

mesh.o: src/graphics/mesh.cpp
	$(CXX) -c $(CXX_FLAGS) $(INCLUDE_PATH) src/graphics/mesh.cpp

light.o: src/graphics/light.cpp
	$(CXX) -c $(CXX_FLAGS) $(INCLUDE_PATH) src/graphics/light.cpp

shader.o: src/graphics/shader.cpp
	$(CXX) -c $(CXX_FLAGS) $(INCLUDE_PATH) src/graphics/shader.cpp

texture.o: src/graphics/texture.cpp
	$(CXX) -c $(CXX_FLAGS) $(INCLUDE_PATH) src/graphics/texture.cpp

transform.o: src/graphics/transform.cpp
	$(CXX) -c $(CXX_FLAGS) $(INCLUDE_PATH) src/graphics/transform.cpp

camera.o: src/graphics/camera.cpp
	$(CXX) -c $(CXX_FLAGS) $(INCLUDE_PATH) src/graphics/camera.cpp

# SYSTEM
time.o: src/system/time.cpp
	$(CXX) -c $(CXX_FLAGS) $(INCLUDE_PATH) src/system/time.cpp

cameraEventHandler.o: src/system/cameraEventHandler.cpp
	$(CXX) -c $(CXX_FLAGS) $(INCLUDE_PATH) src/system/cameraEventHandler.cpp

# MAIN
main.o: src/main.cpp
	$(CXX) -c $(CXX_FLAGS) $(INCLUDE_PATH) src/main.cpp

trash:
	rm -rf *.o

clean:
	rm -rf *.o main
