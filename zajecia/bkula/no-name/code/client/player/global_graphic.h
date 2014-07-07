#ifndef __GLOBALGRAPHIC_H__
#define __GLOBALGRAPHIC_H__

/******************************
 Pomocne funkcje graficzne
******************************/

#include "Area.h"
#include "Color.h"

void drawGradient(Area area, const Color& from, const Color& to, bool withFrame = true);

#endif // __GLOBALGRAPHIC_H__
