#ifndef BITMAP_H
#define BITMAP_H

#include "../../Error.h"

#include <string>
using namespace std;

#include <allegro5.h>

// klasa narzędziowa
// opakowanie do ALLEGRO_BITMAP*

class Bitmap
{
public:

    Bitmap(string path) throw(Error);

    virtual ~Bitmap();

    Bitmap(const Bitmap& other) throw(Error);

    Bitmap& operator=(const Bitmap& other) throw(Error);

    ALLEGRO_BITMAP * operator()() const { return ptr; }

    void draw(int _x, int _y, int _flag = 0);
    void drawCentred(int _cx, int _cy, int _flag = 0);

private:

    ALLEGRO_BITMAP * ptr;

    int w, h;
};

#endif // BITMAP_H
