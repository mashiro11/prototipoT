#include "Point.h"

#define DEBUG
#ifdef DEBUG
        //se estiver definido debug, imprime os trecos
        #define DEBUG_PRINT(message) do{std::cout << message << std::endl;}while(0)
#else
        //caso contrario, recebe argumentos mas faz nada
        #define DEBUG_PRINT(message)
#endif //DEBUG

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
    if(x1 == x && y1 == y) return 0;
    double firstQ = asin( abs(y - y1) / DistTo(x1,y1) );
    if(y1 >= y && x1 >= x){//primeiro quadrante
        return firstQ;
    }else if(y1 >= y && x1 <= x){//segundo quadrante
        return PI - firstQ;
    }else if(y1 <= y && x1 <= x){//terceiro quadrante
        return firstQ + PI;
    }else{// quarto quadrante
        return 2*PI - firstQ;
    }
}

double Point::AngleTo(Point& pt){
    //valor do angulo no primeiro quadrante
    if(pt.x == x && pt.y == y) return 0;
    double firstQ = asin( abs(y - pt.y) / DistTo(pt.x,pt.y) );

    if(pt.y >= y && pt.x >= x){//primeiro quadrante
        return firstQ;
    }else if(pt.y >= y && pt.x <= x){//segundo quadrante
        return PI - firstQ;
    }else if(pt.y <= y && pt.x <= x){//terceiro quadrante
        return firstQ + PI;
    }else{// quarto quadrante
        return 2*PI - firstQ;
    }
}

#ifdef DEBUG
    #undef DEBUG
#endif // DEBUG
