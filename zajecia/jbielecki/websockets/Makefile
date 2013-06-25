all: server client chat
	# Done
server: server.cpp
	g++ -o server server.cpp -lwebsockets
client: client.cpp
	g++ -o client client.cpp -lwebsockets
chat: chat.cpp
	g++ -o chat chat.cpp -lwebsockets
