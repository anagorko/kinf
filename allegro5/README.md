Instalacja allegro5 w Ubuntu
-----

Na podstawie http://wiki.allegro.cc/index.php?title=Install_Allegro5_From_Git/Linux/Debian

> sudo apt-get install build-essential git cmake xorg-dev libgl1-mesa-dev libglu-dev
>
> sudo apt-get install libpng-dev libcurl4-nss-dev libfreetype6-dev libjpeg-dev 
libvorbis-dev libopenal-dev libphysfs-dev libgtk2.0-dev libasound-dev libpulse-dev 
libflac-dev libdumb1-dev
>
> sudo apt-get install exuberant-ctags dvi2ps dvipdfmx latex2html pandoc

Następnie

>git clone git://git.code.sf.net/p/alleg/allegro

>cd allegro

>git checkout 5.0

>mkdir build

>cd build

>cmake -DCMAKE_INSTALL_PREFIX=/usr ..

>make

>sudo make install

Instalację przetestuj kompilując i uruchamiając przykładowy program hello.cpp z katalogu
allegro5/hello/

>cd allegro5/hello
>make
>./hello

