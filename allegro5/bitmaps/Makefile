all: bouncer load
	# Done
bouncer: bouncer.cpp
	g++ bouncer.cpp -o bouncer -I/opt/local/include/ -L/opt/local/lib -lallegro -lallegro_main
load: load.cpp
	g++ load.cpp -o load -I/opt/local/include/ -L/opt/local/lib -lallegro -lallegro_main -lallegro_image -lallegro_dialog
