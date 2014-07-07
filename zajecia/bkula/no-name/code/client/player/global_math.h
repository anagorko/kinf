#ifndef __GLOBALMATH_H__
#define __GLOBALMATH_H__

/******************************
 Pomocne funkcje matematyczne
******************************/

template<typename T> T difference(T a, T b)
{
    return a > b ? a-b : b-a;
}

template<typename T> T max3(T a, T b, T c)
{
    return max(max(a,b),c);
}

template<typename T> T range(T x, T from, T to)
{
    return max(min(x, max(to, from)), min(from, to));
}

#endif // __GLOBALMATH_H__
