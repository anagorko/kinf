all: car server
	# Done
car: car.cpp client.h
	g++ car.cpp -std=c++11 -g -o car -I/opt/local/include/ -L/opt/local/lib -lallegro -lallegro_main -lallegro_image -lallegro_dialog -lallegro_primitives -lallegro_font -lallegro_ttf -lwebsockets -pthread
