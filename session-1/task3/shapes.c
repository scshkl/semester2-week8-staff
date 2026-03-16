
#include <stdio.h>
#include "shapes.h"

int main( void ) {

    // complete the structure definition in the header file first
    // code in main to test the structures and functions

    Point p = {
        .x = 1,
        .y = 1
    };

    Point dp = {
        .x = 2,
        .y = 3
    };

    Rectangle r = makeRectangle(p, 4, 2);
    printf("Area of a rectange %.2f\n", area(r));

    shiftRectangle(&r, dp);
    printf("shift rectangle by Point %.1f %.1f is %.1f %.1f\n", dp.x, dp.x, r.p.x, r.p.y);

    return 0;
}

Rectangle makeRectangle( Point p, float width, float height ){
    Rectangle r;
    r.width = width;
    r.height = height;
    r.p = p;
    return r;
}

float area( Rectangle r ) {
    float a = 0.0;
    a = r.width * r.height;
    return a;
}

void shiftRectangle( Rectangle *r, Point dp ) {
    r->p.x += dp.x;
    r->p.y += dp.y;

    //return;
}

void scaleRectangle( Rectangle *r, float scale ) {
    r->width *= scale;
    r->height *= scale;
    //return;
}
