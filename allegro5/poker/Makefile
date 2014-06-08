all: stolik gracz
	# Done
stolik: stolik.cpp ../../network/websockets/client.h
	g++ --std=c++0x stolik.cpp -o stolik -lwebsockets
gracz: gracz.cpp ../../network/websockets/client.h
	g++ --std=c++0x gracz.cpp -o gracz -I/usr/local/include/ -L/usr/local/lib -lallegro -lallegro_main -lallegro_primitives -lallegro_image -lallegro_font -lallegro_ttf -lwebsockets
