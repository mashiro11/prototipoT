#include "Reta.h"

Reta::Reta()
{
    //ctor
}

Reta::Reta(Point pt1, Point pt2){
    this->pt1 = pt1;
    this->pt2 = pt2;
}

Reta::Reta(double x1, double y1, double x2, double y2){
    this->pt1.x = x1;
    this->pt1.y = y1;
    this->pt2.x = x2;
    this->pt2.y = y2;
}

Reta::~Reta()
{
    //dtor
}
