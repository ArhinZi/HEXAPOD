#include "InverseKinematic.h"


// From: http://paulbourke.net/geometry/circlesphere/tvoght.c
bool circle_circle_intersection(double x0, double y0, double r0,
                                double x1, double y1, double r1,
                                double *xi, double *yi)
{
  double a, dx, dy, d, h, rx, ry;
  double x2, y2;

  /* dx and dy are the vertical and horizontal distances between
     the circle centers.
  */
  dx = x1 - x0;
  dy = y1 - y0;

  /* Determine the straight-line distance between the centers. */
  d = sqrt((dy * dy) + (dx * dx));

  /* Check for solvability. */
  if (d > (r0 + r1))
  {
    /* no solution. circles do not intersect. */
    return 0;
  }
  if (d < fabs(r0 - r1))
  {
    /* no solution. one circle is contained in the other */
    return false;
  }

  /* 'point 2' is the point where the line through the circle
     intersection points crosses the line between the circle
     centers.
  */

  /* Determine the distance from point 0 to point 2. */
  a = ((r0 * r0) - (r1 * r1) + (d * d)) / (2.0 * d) ;

  /* Determine the coordinates of point 2. */
  x2 = x0 + (dx * a / d);
  y2 = y0 + (dy * a / d);

  /* Determine the distance from point 2 to either of the
     intersection points.
  */
  h = sqrt((r0 * r0) - (a * a));

  /* Now determine the offsets of the intersection points from
     point 2.
  */
  rx = -dy * (h / d);
  ry = dx * (h / d);

  /* Determine the absolute intersection points. */
  *xi = x2 + rx;
  *yi = y2 + ry;

  return true;
}

bool find_angles(double Ax, double Ay, double a,
                 double Bx, double By, double b,
                 double Cx, double Cy,
                 int *femur_angle,
                 int *tibia_angle) {
  double cos_femur = (Bx*1)/a;
  double cos_tibia = ((Ax-Bx)*(Cx-Bx)+(Ay-By)*(Cy-By))/(a*b);

  // 180/3.14 = 57.3
  *femur_angle = acos(cos_femur)*57.3;
  *tibia_angle = acos(cos_tibia)*57.3;
  return true;
}
