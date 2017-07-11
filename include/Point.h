#ifndef POINT_H
#define POINT_H

#include <iostream>
#include <math.h>
#define PI 3.1415

using std::cout;
using std::endl;
class Point
{
    public:
        Point();
        Point(double x, double y);
        virtual ~Point();
        double x;
        double y;
        double DistTo(Point point);
        double DistTo(double x, double y);
        double AngleTo(double x, double y);
    protected:

    private:
};

#endif // POINT_H
