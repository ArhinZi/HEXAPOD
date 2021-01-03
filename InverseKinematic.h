#include <Arduino.h>
#include <math.h>

bool circle_circle_intersection(double x0, double y0, double r0,
                                double x1, double y1, double r1,
                                double *xi, double *yi);

bool find_angles(double Ax, double Ay, double a,
                 double Bx, double By, double b,
                 double Cx, double Cy,
                 int *femur_angle,
                 int *tibia_angle);
