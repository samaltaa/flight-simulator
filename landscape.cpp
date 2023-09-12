// Implementation of the Landscape class.

#include "landscape.h"
#include "geometry.h"

GLfloat blue[] = {0.0, 0.0, 1.0, 1.0};
GLfloat green[] = {0.0, 1.0, 0.0, 1.0};
GLfloat darkGreen[] = {0.0, 0.5, 0.0, 1.0};
GLfloat brown[] = {0.5, 0.5, 0.0, 1.0};
GLfloat lightBrown[] = {0.7, 0.7, 0.3, 1.0};
GLfloat gray[] = {0.6, 0.6, 0.6, 1.0};
GLfloat forest[] = {0.4, 0.8, 0.5, 1.0};
GLfloat white[] = {1.0, 1.0, 1.0, 1.0};

// Hack.
double Landscape::unused = -10032.4775;

// Constructor.  Ensure the matrix is loaded with the unused constant in
// every cell.
Landscape::Landscape(int r, int c): rows(r), columns(c) {
  std::vector<double> nullRow(columns, unused);
  std::vector< std::vector<double> > nullMatrix(rows, nullRow);
  d = nullMatrix;
}

// create() sets the elevations of the four grid corners to 0, generates
// internal elevations remembering the highest point, then generates display
// lists.
void Landscape::create(double rug) {
  int r, c;

  // First put zeros for the elevations around the whole boundary:
  for (r = 0; r < rows; r++) d[r][0] = d[r][columns-1] = 0;
  for (c = 0; c < columns; c++) d[0][c] = d[rows-1][c] = 0;

  // Then put zeros in the corners inset two units and generate
  // a fractal landscape in that rectangle.
  d[2][2] = d[2][columns-3] = d[rows-3][2] = d[rows-3][columns-3] = 0;
  generate(2, 2, rows - 3, columns - 3, rug);

  // Then smooth out the inner fractal so it meets the zeroed out
  // edges.  Make the part just outside the fractal one-third higher
  // so it simulates flatter beaches.
  for (r = 2; r < rows - 2; r++) d[r][1] = d[r][2] / 3.0;
  for (r = 2; r < rows - 2; r++) d[r][c-2] = d[r][c-3] / 3.0;
  for (c = 1; c < columns-1; c++) d[1][c] = d[2][c] / 3.0;
  for (c = 1; c < columns-1; c++) d[r-2][c] = d[r-3][c] / 3.0;

  // Finally it part of the land is underwater make that elevation 0.
  highest = 0.0;
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      if (d[i][j] < 0) d[i][j] = 0;
      if (d[i][j] > highest) highest = d[i][j];
    }
  }

  // Generate the display lists.
  solidId = glGenLists(2);
  wireFrameId = solidId + 1;
  createSolidDisplayList();
  createWireFrameDisplayList();
}

// Simple math for random midpoint displacement.
void Landscape::generate(int x1, int y1, int x2, int y2, double rug) {
  int x3 = (x1 + x2) / 2;
  int y3 = (y1 + y2) / 2;
  if (y3 < y2) {
    if (d[x1][y3] == unused) {
      d[x1][y3] = (d[x1][y1] + d[x1][y2])/2 + scale(rug*(y2-y1));
    }
    d[x2][y3] = (d[x2][y1] + d[x2][y2])/2 + scale(rug*(y2-y1));
  }
  if (x3 < x2) {
    if (d[x3][y1] == unused) {
      d[x3][y1] = (d[x1][y1] + d[x2][y1])/2 + scale(rug*(x2-x1));
    }
    d[x3][y2] = (d[x1][y2] + d[x2][y2])/2 + scale(rug*(x2-x1));
  }
  if (x3 < x2 && y3 < y2) {
    d[x3][y3] = (d[x1][y1] + d[x2][y1] + d[x1][y2] + d[x2][y2])/4
    + scale(rug * (fabs((double)(x2 - x1)) + fabs((double)(y2 - y1))));
  }
  if (x3 < x2 - 1 || y3 < y2 - 1) {
    generate(x1, y1, x3, y3, rug);
    generate(x1, y3, x3, y2, rug);
    generate(x3, y1, x2, y3, rug);
    generate(x3, y3, x2, y2, rug);
  }
}
