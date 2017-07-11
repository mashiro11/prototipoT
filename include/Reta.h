#ifndef RETA_H
#define RETA_H

#include "Point.h"

class Reta
{
    public:
        Reta();
        Reta(Point pt1, Point pt2);
        Reta(double x1, double y1, double x2, double y2);
        virtual ~Reta();
        Point pt1;
        Point pt2;
    protected:

    private:
};

#endif // RETA_H
