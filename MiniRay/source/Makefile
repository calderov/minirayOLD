CC     = g++
CFLAGS = -O3 -std=c++11
OBJ    = camera.o scene.o sphere.o plane.o

# Build miniray
all: $(OBJ)
	make dirs
	$(CC) miniray.cpp -o miniray $(OBJ) $(CFLAGS)

# Build miniray (debug)
debug: $(OBJ)
	g++ -g -std=c++11 camera.cpp scene.cpp sphere.cpp plane.cpp miniray.cpp -o miniray

# Clean build files
clean:
	rm -rfv *.o *.bmp *.mp4 miniray renders

dirs:
	if [ ! -d "renders" ]; then mkdir renders; fi

# Compile objects
%.o: ./%.cpp
	$(CC) -c -o $@ $< $(CFLAGS)