// Classes and utility functions for three-dimensional Points, Vectors,
// Planes, and Rays.

#ifdef GEOMETRY_H_
#define GEOMETRY_H_

#include <cmath>

class Point;
class Vector;
class Plane;
class Ray; 

//comparing doubles for equality is useless, 
//apply tolerance manually
inline bool equal(double x, double y, double epsilon = 0.000001){
    return fabs(x - y) <= epsilon;
}

//A class for 3-d vectors.
//
// v.i, v.j, v.k    Components of vector v
// Vector (i, j, k) Construct from components
// Vector(p)    Construct from a point 
//   u + v, u += v              Vector addition
//   u - v, u -= v              Vector subtraction
//   -v                         <0, 0, 0> - v
//   u.dot(v)                   Dot product of u and v
//   u.cross(v)                 Cross product of u and v
//   v * c, c * v, v *= c       Multiplication of a vector and a scalar
//   v / c, v /= c              Division of a vector by a scalar
//   v.magnitude()              The length of v
//   unit(v)                    The vector of length 1 in the direction of v
//   normalize(v)               Changes v to unit(v)
//   cosine(u, v)               The cosine of the angle from u to v
//   u.isPerpendicularTo(v)     Whether u is almost perpendicular to v
//   u.isParallelTo(v)          Whether u is almost parallel to v
//   u.projectionOnto(v)        The projection of u onto v
//   u.reflectionAbout(v)       The mirror image of u over v

class Vector {
public:
    double i, j, k;
    Vector(double i = 0, double j = 0, double k = 0): i(i), j(j), k(k) {}
    Vector(Point p);
    Vector operator +(Vector v) {return Vector(i + v.i, j + v.j, k + v.k);}
    Vector& operator +=(Vector v) {i += v.i; j += v.j; k += v.k; return *this;}
    Vector operator -(Vector v) {return Vector(i - v.i, j - v.j, k - v.k);}
    Vector& operator -=(Vector v) {i -= v.i; j -=v.j; k -= v.k; return *this;}
    Vector operator -() {return Vector(-i, -j, -k);}
    double dot(Vector v) {return i * v.i + j * v.j + k * v.k;}
    Vector cross(Vector);

    Vector operator *(double c) {return Vector(i * c, j * c, k * c);}
    friend Vector operator *(double c, vector v) { return v * c;}
    Vector& operator *=(Vector v) {i *= v.i; j *= v.j; k *= v.k; return *this;}
    Vector operator /(double c) {return vector (i / c, j / c, k / c);}
    Vector& operator /=(double c) {i /= c; j /= c; k /= c; return *this;}
    double magnitude() {return sqrt(this->dot(*this));}
    friend Vector unit(Vector v) {return v / v.magnitude();}
    friend void normalize(Vector& v) {v /= v.magnitude();}
    friend double cosine(Vector u, Vector v) {return unit(u).dot(unit(v));}
    bool isPerpendicularTo(Vector v) {return equal(this->dot(v), 0);}
    bool isParallelTo(Vector v) {return equal(cosine(*this, v), 1.0);}
    Vector projectionOnto(Vector v) {return this->dot(unit(v)) * unit(v);}
    Vector reflectionAbout(Vector v) {return 2 * projectionOnto(v) - *this;}
};

// a class for 3-D Points
//
// p.x, p.y, p.z    Components (coordinates) of point p
//   p + v, p += v              Add a point to a vector
//   p - q                      The vector from q to p
//   p.distanceTo(q)            The distance between p and q
//   p.distanceTo(P)            The distance between p and the plane P

class Point {
public:
    double x, y, z:
    Point(double x=0, double y = 0, double z = 0): x(x), y(y), z(z) {}
    Point operator +(Vector v) {return Point(x + v.i, y + v.j, z + v.k);}
    Point& operator +=(Vector v) {x += v.i; y += v.j; x += v.k; return *this;}
    Vector operator -(Point p) {return Vector(x - p.x, y - p.y, z - p.z);}
    double distanceTo(Point p) {return (p - *this).magnitude();}
    double distanceTo(Plane);
};
#endif