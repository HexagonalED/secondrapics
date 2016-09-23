/* -*- mode: c -*- */
#include "curve.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

enum XY { X = 0, Y };

#define SET_VECTOR2(V, V1, V2)          do { (V)[X] = (V1); (V)[Y] = (V2); } while (0)
#define COPY_PT(DST, SRC)               do { (DST)[X] = SRC[X]; (DST)[Y] = SRC[Y]; } while (0)
#define VECTOR2_X_SCALA_ADD(O, V, S)    do { O[X] += (S) * (V)[X]; O[Y] += (S) * (V)[Y]; } while (0)

#ifdef DEBUG
void PRINT_CTRLPTS(CubicBezierCurve* crv) {
    int i;
    printf("curve %p\n[\n", crv);
    for (i=0; i<4; ++i)
        printf("[%f, %f]\n", crv->control_pts[i][X], crv->control_pts[i][Y]);
    printf("]\n");
}
#endif

void evaluate(const CubicBezierCurve *curve, const REAL t, Point value)
{
    const REAL t_inv = 1.0f - t;
    const REAL t_inv_sq = t_inv * t_inv;
    const REAL t_sq = t * t;
    const REAL b0 = t_inv_sq * t_inv;
    const REAL b1 = 3 * t_inv_sq * t;
    const REAL b2 = 3 * t_inv * t_sq;
    const REAL b3 = t_sq * t;
    SET_VECTOR2(value, 0, 0);
    VECTOR2_X_SCALA_ADD(value, curve->control_pts[0], b0);
    VECTOR2_X_SCALA_ADD(value, curve->control_pts[1], b1);
    VECTOR2_X_SCALA_ADD(value, curve->control_pts[2], b2);
    VECTOR2_X_SCALA_ADD(value, curve->control_pts[3], b3);
}



void evaluate_curvature(const CubicBezierCurve *curve, const REAL t, REAL* a, REAL* b, REAL* value){
    const t_sq = t*t;
    const REAL c0 = (a[1]*b[0]            )-(a[0]*b[1]                        )*3/2;
    const REAL c1 = (a[1]*b[1]+2*a[2]*b[0])-(2*a[0]*b[2]+a[1]*b[1]            )*3/2;
    const REAL c2 = (a[1]*b[2]+2*a[2]*b[1])-(3*a[0]*b[3]+2*a[1]*b[2]+a[2]*b[1])*3/2;
    const REAL c3 = (a[1]*b[3]+2*a[2]*b[2])-(4*a[0]*b[4]+3*a[1]*b[3]+2*a[2]*b[2])*3/2;
    const REAL c4 = (a[1]*b[4]+2*a[2]*b[3])-(            4*a[1]*b[4]+3*a[2]*b[3])*3/2;
    const REAL c5 = (          2*a[2]*b[4])-(                        4*a[2]*b[4])*3/2;

    (*value) = c0+c1*t+c2*t_sq+c3*t_sq*t+c4*t_sq*t_sq+c5*t_sq*t_sq*t;
}
