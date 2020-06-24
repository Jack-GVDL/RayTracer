CPP_FILE	= main.cpp RayTracer_Camera.cpp
OUTPUT		= main


all:
	g++ $(CPP_FILE) -o $(OUTPUT)
	./$(OUTPUT) > image.ppm
