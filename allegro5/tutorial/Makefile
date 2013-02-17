all: bouncer load keyboard mouse fullscreen font
	# Done
bouncer: bouncer.cpp
	g++ bouncer.cpp -o bouncer -I/opt/local/include/ -L/opt/local/lib -lallegro -lallegro_main
load: load.cpp
	g++ load.cpp -o load -I/opt/local/include/ -L/opt/local/lib -lallegro -lallegro_main -lallegro_image -lallegro_dialog
keyboard: keyboard.cpp
	g++ keyboard.cpp -o keyboard -I/opt/local/include/ -L/opt/local/lib -lallegro -lallegro_main -lallegro_image -lallegro_dialog
mouse: mouse.cpp
	g++ mouse.cpp -o mouse -I/opt/local/include/ -L/opt/local/lib -lallegro -lallegro_main -lallegro_image -lallegro_dialog
fullscreen: fullscreen.cpp
	g++ fullscreen.cpp -o fullscreen -I/opt/local/include/ -L/opt/local/lib -lallegro -lallegro_main -lallegro_image -lallegro_dialog -lallegro_primitives
font: font.cpp
	g++ font.cpp -o font -I/opt/local/include/ -L/opt/local/lib -lallegro -lallegro_main -lallegro_image -lallegro_dialog -lallegro_primitives -lallegro_font -lallegro_ttf
