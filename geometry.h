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





#endif