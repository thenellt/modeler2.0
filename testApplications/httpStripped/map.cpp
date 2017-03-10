#include "map.h"



map::map(){
    addPoints();
}

long double map::toRadians(long double x){
    long double temp = (x * (M_PI/180));
    qDebug() << "toRadians input: " << (double)x << " output: " << (double)temp;
    return (x * (M_PI/180));
}

long double map::toDegrees(long double x){
    return (x * (180/M_PI));
}

void map::addPoints(){
    //points.push_back(point(44.578609, -123.291258));
    //points.push_back(point(44.57186, -123.28329));
    //points.push_back(point(44.571838, -123.290955));
    //points.push_back(point(44.578756, -123.283095));
    //points.push_back(point(44.582971, -123.275941));
    points.push_back(point(41.027569, -116.722164));
    points.push_back(point(40.789791, -116.739157));
    points.push_back(point(40.793834, -116.205558));
    points.push_back(point(41.047346, -116.213326));

}

point map::getCenter(){
    point a, b;
    findExtremePoints(a,b);
    return getMidpoint(a, b);
}

void map::findExtremePoints(point &a, point &b){
    double ymin = 1000, ymax = -1000, xmin = 1000, xmax = -1000;
    point temp;
    for(int i = 0; i < points.size(); i++){
        temp = points.at(i);
        if(temp.x > xmax)
            xmax = temp.x;
        if(temp.x < xmin)
            xmin = temp.x;

        if(temp.y > ymax)
            ymax = temp.y;
        if(temp.y < ymin)
            ymin = temp.y;
    }

    qDebug() << "Max: (" << xmax << ", " << ymax << ") Min: (" << xmin << ", " << ymin << ")";
    a.x = xmin;
    a.y = ymin;
    b.x = xmax;
    b.y = ymax;
}

point map::getMidpoint(point p1, point p2){
    long double delta, tempX, tempY;
    double bearingX, bearingY;
    point a, b, c, d;

    a.x = toRadians(p1.x);
    a.y = toRadians(p1.y);
    b.x = toRadians(p2.x);
    b.y = toRadians(p2.y);
    delta = toRadians(p2.y - p1.y);
    qDebug() << "delta: " << (double)delta;

    bearingX = cos(b.x) * cos(delta);
    bearingY = cos(b.x) * sin(delta);
    qDebug() << "bearing: (" << bearingX << "," << bearingY << ")";

    tempX = sqrt((cos(a.x) + bearingX) * (cos(a.x) + bearingX) + (bearingX * bearingY));
    tempY = sin(a.x) + sin(b.x);

    c.x = atan2(tempY, tempX);
    c.y = a.y + atan2(bearingY, cos(a.x) + bearingX);

    qDebug() << "midpoint radians: (" << (double)c.x << "," << (double)c.y << ")";
    d.x = toDegrees(c.x);
    d.y = (fmod(toDegrees(c.y) + 540, 360) - 180);
    qDebug() << qSetRealNumberPrecision(12) << "midpoint degrees: (" << (double)d.x << "," << (double)d.y << ")";
    return c;
}
