#ifndef __GLOBALGRAPHIC_H__
#define __GLOBALGRAPHIC_H__

/******************************
 Pomocne funkcje graficzne
******************************/

#include "Area.h"
#include "Color.h"
#include "global_main.h"

void drawGradient(Area area, const Color& from, const Color& to, bool withFrame = true);

class Scale
{
public:

    Scale(double _w, double _h) : w(_w), h(_h) {}

    double operator()(double x) const {
        return x * min(
            static_cast<double>(screen().w()) / w,
            static_cast<double>(screen().h()) / h
        );
    }

    static Scale bk;

private:

    const double w, h;
};

#endif // __GLOBALGRAPHIC_H__
