all: server client chat
	# Done
server: server.cpp
	c++ --std=c++0x -o server server.cpp -lwebsockets
client: client.cpp
	c++ -o client client.cpp -lwebsockets
chat: chat.cpp
	c++ -o chat chat.cpp -lwebsockets
