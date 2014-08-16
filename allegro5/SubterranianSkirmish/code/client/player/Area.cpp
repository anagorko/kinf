#include "Area.h"

Area::Area() : initialized(false)
{
    //
}

Area::Area(Style s, float a1, float a2, float a3, float a4) throw(Error)
{
    reInit(s, a1, a2, a3, a4);
}

void Area::reInit(Style s, float a1, float a2, float a3, float a4) throw(Error)
{
    switch(s) {

    case XYXY:
        _x1 = a1;
        _y1 = a2;
        _x2 = a3;
        _y2 = a4;
        break;

    case XYWH:
        _x1 = a1;
        _y1 = a2;
        _x2 = a1 + a3;
        _y2 = a2 + a4;
        break;

    case CXYWH:
        _x1 = a1 - a3/2;
        _y1 = a2 - a4/2;
        _x2 = a1 + a3/2;
        _y2 = a2 + a4/2;
        break;

    default:
        throw Error(__FILE__, __LINE__, "Nierozpoznany styl opisu pozycji");
    }

    initialized = true;
}

void Area::reInit(const Area& other)
{
    _x1 = other._x1;
    _y1 = other._y1;
    _x2 = other._x2;
    _y2 = other._y2;
    initialized = other.initialized;
}
