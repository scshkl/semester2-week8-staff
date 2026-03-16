
#include <stdio.h>
#include "points.h"
#include <math.h>

int main( void ) {

    // complete the structure definition in the header file first
    // implement code for the following
    // include necessary libraries
    /**/
    Point p1 = { .x=1, .y=2 };
    Point p2 = { .x=-2, .y=4 };
    
    printf(" Distance between (%.1f,%.1f) and (%.1f,%.1f) is %f\n", 
             p1.x,p1.y,p2.x,p2.y,distance(p1,p2));


    // reflect
    Point ref = reflect(p1);
    printf("reflect point (%.1f,%.1f) is (%.1f,%.1f)\n", p1.x,p1.y, ref.x, ref.y);

    // shift
    Point sh = shift(p1, p2);
    printf("shift point (%.1f,%.1f) and (%.1f,%.1f) is (%.1f,%.1f)\n", p1.x,p1.y, p2.x,p2.y, sh.x, sh.y);
    
    return 0;
}

float distance( Point p, Point q ) {
    // implement distance here
    float distance = sqrt(pow(p.x - q.x, 2) + pow(p.y - q.y, 2));

    return distance;
}

Point reflect(Point q){
    Point rq = {
        .x = q.x,
        .y = -q.y
    };
    return rq;

}

Point shift(Point q, Point dp){
    Point sp = {
        .x = q.x + dp.x,
        .y = q.y + dp.y
    };
    return sp;
}