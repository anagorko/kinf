all: stolik gracz
	# Done
stolik: stolik.cpp
	g++ stolik.cpp -o stolik -lwebsockets
gracz: gracz.cpp
	g++ gracz.cpp -o gracz -I/opt/local/include/ -L/opt/local/lib -lallegro -lallegro_main -lallegro_primitives -lallegro_image -lallegro_font -lallegro_ttf -lwebsockets
