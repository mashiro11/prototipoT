#include "Point.h"

Point::Point()
{
    //ctor
}

Point::Point(double x, double y){
    this->x = x;
    this->y = y;
}

Point::Point::~Point()
{
    //dtor
}

double Point::DistTo(Point point){
    double distX = point.x - x; //distancia entre o centro e o mouse em x
    double distY = point.y - y; //distancia entre o centro e o mouse em y
    distX *= distX; //dist^2
    distY *= distY; //
    return sqrt(distX + distY);
}

double Point::DistTo(double x, double y){
    double distX = this->x - x; //distancia entre o centro e o mouse em x
    double distY = this->y - y; //distancia entre o centro e o mouse em y
    distX *= distX; //dist^2
    distY *= distY; //
    return sqrt(distX + distY);
}

double Point::AngleTo(double x1, double y1){
    double firstQ = asin( abs(y - y1) / DistTo(x1,y1) );
    if(y1 >= y && x1 > x){//primeiro quadrante
        return firstQ;
    }else if(y1 >= y && x1 < x){//segundo quadrante
        return PI - firstQ;
    }else if(y1 <= y && x1 < x){//terceiro quadrante
        return firstQ + PI;
    }else{// quarto quadrante
        return 2*PI - firstQ;
    }
}
