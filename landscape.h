// A simple landscape class.  A landscape is essentially an elevation grid
// which can be drawn in wireframe or as a solid.  Landscape elevations are
// set using the Random Midpoint Displacement technique.
//
// Landscape(m, n)      (constructor) sets the x and z bounds of the landscape
//                      so that the constructed object will be a set of points
//                      (x, y, z) where x and z are integers and 0 <= x < m
//                      and 0 <= z < n, and y is undefined.
// create(rug)          assigns random elevations based on the ruggedness
//                      coefficient rug (rug == 0 defines the completely
//                      flat grid).  This routine also generates OpenGL
//                      display lists for efficient drawing.
// draw()               draws the landscape using a fixed coloring scheme.
// drawWireFrame()      draws a wireframe representation of the landscape.