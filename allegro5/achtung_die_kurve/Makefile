all: achtung_die_kurve chat server
	# Done
achtung_die_kurve: achtung_die_kurve.cpp
	g++ achtung_die_kurve.cpp -o achtung_die_kurve -I/opt/local/include/ -L/opt/local/lib -lallegro -lallegro_main -lallegro_primitives -lallegro_font -lallegro_ttf -lwebsockets
chat: chat.cpp
	g++ -o chat chat.cpp -lwebsocket
server: server.cpp
	g++ -o server server.cpp -lwebsockets
