#ifndef MAP_H
#define MAP_H

#include <vector>
#include <QDebug>
#include <math.h>

struct point{
    point(){
        x = 0;
        y = 0;
    }

    point(long double a, long double b){
        x = a;
        y = b;
    }

    long double x;
    long double y;
};

struct square{
    square(point x, point y){
        a = x;
        b = y;
    }

    point a;
    point b;
};

class map
{
public:
    map();
    void addPoints();
    point getCenter();
    void findExtremePoints(point &, point &);
    point getMidpoint(point, point);
    long double toRadians(long double);
    long double toDegrees(long double x);
private:
    std::vector<point> points;
};

#endif // MAP_H
