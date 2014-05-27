all: server client chat echo_server websockets_client
	# Done
server: server.cpp
	c++ --std=c++0x -o server server.cpp -lwebsockets
client: client.cpp client.h
	c++ -o client client.cpp -lwebsockets
websockets_client: websockets_client.cpp websockets_client.h
	c++ -o websockets_client websockets_client.cpp -lwebsockets
chat: chat.cpp
	c++ -o chat chat.cpp -lwebsockets
websockets_server.o: websockets_server.cpp websockets_server.h
	c++ -c -o websockets_server.o websockets_server.cpp
echo_server: echo_server.cpp websockets_server.h websockets_server.o
	c++ --std=c++0x -o echo_server echo_server.cpp -lwebsockets websockets_server.o
