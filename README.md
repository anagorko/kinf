kinf
====

Kółko Informatyczne Szkoły Żagle

Na tej stronie znajdziesz repozytorium plików z naszego kółka. Jeżeli jesteś tu pierwszy
raz powinieneś skopiować pliki za pomocą polecenia

>git clone https://github.com/anagorko/kinf.git

a następnie zainstalować bibliotekę allegro 5.0. Instrukcje instalacji w Ubuntu
znajdziesz poniżej.

Instalacja allegro5 w Ubuntu
-----

> sudo apt-get install build-essential git cmake xorg-dev libgl1-mesa-dev libgl
>
> sudo apt-get install libpng-dev libcurl4-nss-dev libfreetype6-dev libjpeg-dev
>
> sudo apt-get install exuberant-ctags dvi2ps dvipdfmx latex2html pando

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

