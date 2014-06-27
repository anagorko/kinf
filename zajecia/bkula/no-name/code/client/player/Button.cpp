#include "Button.h"
#include "global.h"

Button::Button(int _x, int _y, int _w, int _h, string _text, Color _color, void(*_fn)())
: x(_x), y(_y), w(_w), h(_h), text(_text), color(_color), cs(x, y, x+w, y+h), fn(_fn)
{
    //
}

void Button::update()
{
    cs.update();
    if (cs.click()) fn();
}

void Button::draw()
{
    int x;
    Color c1 = color;
    Color c2 = color;
    drawRectangle(x+w/2, y+h/2, w, h, c1+=50, c2+=50);
    al_draw_text(font((3/5)*float(h)), [](bool b)->Color{return b ? Color::white() : Color::black();}(color.ifDark()), x, y - (1/6)*float(h), ALLEGRO_ALIGN_CENTER, text.c_str());
}

void Button::drawRectangle (int cx, int cy, int w, int h, const Color& c1, const Color& c2)
{

    int r1 = c1.getR();
    int g1 = c1.getG();
    int b1 = c1.getB();
    int r2 = c2.getR();
    int g2 = c2.getG();
    int b2 = c2.getB();
    int a = c1.getA();

    /// implementacja tymczsowa zaczerpnięta z pokera

    float grubosc_lini = (float) ((float) h / (float) max3 (difference(r1,r2),difference(g1,g2),difference(b1,b2)));
    bool r=false, g=false, b=false;
    if(difference(r1,r2)==max3(difference(r1,r2),difference(g1,g2),difference(b1,b2)))r=true;
    if(difference(g1,g2)==max3(difference(r1,r2),difference(g1,g2),difference(b1,b2)))g=true;
    if(difference(b1,b2)==max3(difference(r1,r2),difference(g1,g2),difference(b1,b2)))b=true;
    r1=max(r1,r2), g1=max(g1,g2), b1=max(b1,b2);
    float y = cy-h/2;

    for (int i = 0; y < cy+h/2; i++) {
            al_draw_line(cx-w/2,y,cx+w/2,y,al_map_rgba(r1,g1,b1,a),grubosc_lini);
            if(r)r1--; if(g)g1--; if(b)b1--;
            y += (float) grubosc_lini;
    }

    al_draw_rectangle (cx-w/2,cy-h/2,cx+w/2,cy+h/2,Color::black(),1);
}
