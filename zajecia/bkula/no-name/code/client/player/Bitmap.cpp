#include "Bitmap.h"

Bitmap::Bitmap(string path) throw(Error)
{

    ptr = al_load_bitmap(path.c_str());
    if (!ptr) {
        throw Error(__FILE__, __LINE__, "Nie udało się załadować bitmapy " + path);
    }

    w = al_get_bitmap_width(ptr);
    h = al_get_bitmap_height(ptr);

    // tu należałoby dopisać skalowanie bitmapy
}

Bitmap::~Bitmap()
{
    al_destroy_bitmap(ptr);
}

Bitmap::Bitmap(const Bitmap& other) throw(Error)
{
    ptr = al_clone_bitmap(other.ptr);
    if (!ptr) {
        throw Error(__FILE__, __LINE__, "Nie udało się skopiować bitmapy");
    }

    w = al_get_bitmap_width(ptr);
    h = al_get_bitmap_height(ptr);

    // tu należałoby dopisać skalowanie bitmapy
}

Bitmap& Bitmap::operator=(const Bitmap& other) throw(Error)
{
    if (this == &other) return *this;

    al_destroy_bitmap(ptr);

    ptr = al_clone_bitmap(other.ptr);
    if (!ptr) {
        throw Error(__FILE__, __LINE__, "Nie udało się skopiować bitmapy");
    }

    w = al_get_bitmap_width(ptr);
    h = al_get_bitmap_height(ptr);

    // tu należałoby dopisać skalowanie bitmapy

    return *this;
}

void Bitmap::draw(int _x, int _y, int _flag)
{
    al_draw_bitmap(ptr, _x, _y, _flag);
}

void Bitmap::drawCentred(int _cx, int _cy, int _flag)
{
    al_draw_bitmap(ptr, _cx - w/2, _cy - h/2, _flag);
}
