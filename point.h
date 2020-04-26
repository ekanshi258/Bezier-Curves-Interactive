#ifndef POINT
#define POINT

class Point{
public:
    //! x coordinate of point
    double x;
    //! y coordinate of point
    double y;
    //! z coordinate of point
    double z;

    /**
     * Constructor.
     * @param x x coordinate
     * @param y y coordinate
     * @param z z coordinate
     */
    Point(double x, double y, double z){
        this->x = x;
        this->y = y;
        this->z = z;
    }
};

#endif