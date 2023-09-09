// A simplified aerial vehivle that you can use in flybys, flight simulators and
// other 3D programs.  A ship has a position, an orientation and a speed.
// The position is simply a point.  The orientation is given by three
// UNIT vectors: (1) forward, the vector along which the ship is currently
// moving, (2) up, a vector perpendicular to forward that describes which
// direction is "up" to someone sitting in the ship, and (3) right, which
// is really just the cross product of forward and up that we store to
// simplify most of the calculations.  The speed of the ship is simply the
// distance that the ship moves every time fly() is called.
//
// The public members of the Ship class are:
//
// Ship()           initialize the ship so that it is located at the
//                  origin, is travelling in the direction <0, 0, -1>
//                  that is, along the -z axis, has up vector <0, 1, 0>
//                  (and therefore right = <1, 0, 0>) and has initial
//                  speed 0.01.
// getPosition()    return the current position of the ship.
// teleport(p)      move the ship to absolute position p, but preserve
//                  the orientation and speed.
// getDirection()   return the current direction of the ship.
// getVertical()    return the "up" vector of the ship.
// pitch(theta)     reorient the ship so that it is rising theta radians;
//                  technically, rotate forward and up theta radians
//                  around right.
// roll(theta)      rotate up and right theta radians around forward.
// yaw(theta)       rotate forward and right theta radians around up.
// getSpeed()       return the current speed.
// setSpeed(s)      set the current speed to s.
