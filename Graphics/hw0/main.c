/* -*- mode: c -*- */
#include <GL/glut.h>
#include "curve.h"

#define ptX(i) (curve.control_pts[i])[0]
#define ptY(i) (curve.control_pts[i])[1]

/* global */
CubicBezierCurve curve;
GLsizei width = 640, height = 480;
int edit_ctrlpts_idx = -1;
REAL xCoeff[3];
REAL yCoeff[3];




int hit_index(CubicBezierCurve *curve, int x, int y)
{
    int i;
    for (i=0; i<4; ++i) {
        REAL tx = curve->control_pts[i][0] - x;
        REAL ty = curve->control_pts[i][1] - y;
        if ((tx * tx + ty * ty) < 30)
            return i;
    }
    return -1;
}

void init()
{
    SET_PT2(curve.control_pts[0], 50, 100);
    SET_PT2(curve.control_pts[1], 200, 300);
    SET_PT2(curve.control_pts[2], 400, 300);
    SET_PT2(curve.control_pts[3], 550, 100);

    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, width, 0, height);
}

void reshape_callback(GLint nw, GLint nh)
{
    width = nw;
    height = nh;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, width, 0, height);
}

void display_callback(void)
{
#define RES 100
    int i;

    /* curve */
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3ub(0, 0, 0);
    glBegin(GL_LINE_STRIP);
    for (i=0; i<=RES; ++i) {
        Point pt;
        const REAL t = (REAL)i / (REAL)RES;
        evaluate(&curve, t, pt);
        glVertex2f(pt[0], pt[1]);
    }
    glEnd();

    /* control mesh */
    glColor3ub(255, 0, 0);
    glBegin(GL_LINE_STRIP);
    for (i=0; i<4; ++i) {
        REAL *pt = curve.control_pts[i];
        glVertex2f(pt[0], pt[1]);
    }
    glEnd();

    /* control pts */
    glColor3ub(0, 0, 255);
    glPointSize(10.0);
    glBegin(GL_POINTS);
    for (i=0; i<4; ++i) {
        REAL *pt = curve.control_pts[i];
        glVertex2f(pt[0], pt[1]);
    }
    glEnd();

    xCoeff[0] = ptX(1)-ptX(0);
    xCoeff[1] = ptX(2)-2*ptX(1)+ptX(0);
    xCoeff[2] = ptX(3)-3*ptX(2)+3*ptX(1)-ptX(0);

    yCoeff[0] = ptY(1)-ptY(0);
    yCoeff[1] = ptY(2)-2*ptY(1)+ptY(0);
    yCoeff[2] = ptY(3)-3*ptY(2)+3*ptY(1)-ptY(0);

    REAL xCoeffD = xCoeff[1]*xCoeff[1] - 4*xCoeff[2]*xCoeff[0];
    REAL yCoeffD = yCoeff[1]*yCoeff[1] - 4*yCoeff[2]*yCoeff[0];

    REAL tx1,tx2;
    REAL ty1,ty2;

    if(xCoeffD>=0){
    if(xCoeff[2]!=0){
      tx1 = (-xCoeff[1] + sqrt(xCoeffD))/2;
      tx2 = (-xCoeff[1] - sqrt(xCoeffD))/2;
    }
    else if(xCoeff[1]!=0){
      tx1 = -1*(xCoeff[0]/xCoeff[1]);
    }

    if(yCoeff[2]!=0){
      ty1 = (-yCoeff[1] + sqrt(yCoeffD))/2;
      ty2 = (-yCoeff[1] - sqrt(yCoeffD))/2;
    }
    else if(yCoeff[1]!=0){
      ty1 = -1*(yCoeff[0]/yCoeff[1]);
    }

    printf("xCoeffD : %lf, yCoeffD : %lf",xCoeffD,yCoeffD);

    glColor3ub(0, 0, 0);
    glPointSize(10.0);
    glBegin(GL_POINTS);
    Point pt;
    if(xCoeff[2]!=0){
      evaluate(&curve,tx1,pt);
      glVertex2f(pt[0],pt[1]);
      printf("Extreme Point : t = %lf, (x,y) = (%lf,%lf)\n",tx1,pt[0],pt[1]);
      evaluate(&curve,tx2,pt);
      glVertex2f(pt[0],pt[1]);
      printf("Extreme Point : t = %lf, (x,y) = (%lf,%lf)\n",tx2,pt[0],pt[1]);
    }
    else{
      evaluate(&curve,tx1,pt);
      glVertex2f(pt[0],pt[1]);
      printf("Extreme Point : t = %lf, (x,y) = (%lf,%lf)\n",tx1,pt[0],pt[1]);
    }
    if(yCoeff[2]!=0){
      evaluate(&curve,ty1,pt);
      glVertex2f(pt[0],pt[1]);
      printf("Extreme Point : t = %lf, (x,y) = (%lf,%lf)\n",ty1,pt[0],pt[1]);
      evaluate(&curve,ty2,pt);
      glVertex2f(pt[0],pt[1]);
      printf("Extreme Point : t = %lf, (x,y) = (%lf,%lf)\n",ty2,pt[0],pt[1]);
    }
    else{
      evaluate(&curve,ty1,pt);
      glVertex2f(pt[0],pt[1]);
      printf("Extreme Point : t = %lf, (x,y) = (%lf,%lf)\n",ty1,pt[0],pt[1]);
    }
    printf("\n\n");
    glEnd();







    glutSwapBuffers();
}

void mouse_callback(GLint button, GLint action, GLint x, GLint y)
{
    if (GLUT_LEFT_BUTTON == button) {
        switch (action) {
            case GLUT_DOWN:
                edit_ctrlpts_idx = hit_index(&curve, x, height - y);
                break;

            case GLUT_UP:
                edit_ctrlpts_idx = -1;
                break;
        }
    }
    glutSwapBuffers();
}

void mouse_move_callback(GLint x, GLint y)
{
    if (edit_ctrlpts_idx != -1) {
        curve.control_pts[edit_ctrlpts_idx][0] = (REAL)x;
		curve.control_pts[edit_ctrlpts_idx][1] = (REAL)(height - y);
    }
    glutPostRedisplay();
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(width, height);
    glutCreateWindow("Bezier Editor");

    init();
    glutReshapeFunc(reshape_callback);
    glutMouseFunc(mouse_callback);
    glutMotionFunc(mouse_move_callback);
    glutDisplayFunc(display_callback);
    glutMainLoop();
    return 0;
}
