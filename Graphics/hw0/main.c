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
REAL inflecCoeff[3];
Point ptG[15];
int ptCount;




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
  ptCount =0;

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


  /* extreme points */
  glColor3ub(0, 0, 0);
  glPointSize(15.0);
  glBegin(GL_POINTS);
  Point pt;
  REAL tx1,tx2;
  REAL ty1,ty2;

  xCoeff[0] = ptX(1)-ptX(0);
  xCoeff[1] = ptX(2)-2*ptX(1)+ptX(0);
  xCoeff[2] = ptX(3)-3*ptX(2)+3*ptX(1)-ptX(0);
  REAL xCoeffD = xCoeff[1]*xCoeff[1] - 4*xCoeff[2]*xCoeff[0];

  if(xCoeffD>=0){
    if(xCoeff[2]!=0){
      tx1 = (-xCoeff[1] + sqrt(xCoeffD))/(2*xCoeff[2]);
      tx2 = (-xCoeff[1] - sqrt(xCoeffD))/(2*xCoeff[2]);
    }
    else if(xCoeff[1]!=0){
      tx1 = -1*(xCoeff[0]/xCoeff[1]);
    }

    if(xCoeff[2]!=0){
      if(0<=tx1&&tx1<=1){
        evaluate(&curve,tx1,pt);
        ptG[ptCount] = pt;
        ptCount++;        
        glVertex2f(pt[0],pt[1]);
        printf("Extreme Point : t = %lf, (x,y) = (%lf,%lf)\n",tx1,pt[0],pt[1]);
      }

      if(0<=tx2&&tx2<=1){
        evaluate(&curve,tx2,pt);
        ptG[ptCount] = pt;
        ptCount++;
        glVertex2f(pt[0],pt[1]);
        printf("Extreme Point : t = %lf, (x,y) = (%lf,%lf)\n",tx2,pt[0],pt[1]);
      }
    }
    else{
      if(0<=tx1&&tx1<=1){
        evaluate(&curve,tx1,pt);
        ptG[ptCount] = pt;
        ptCount++;        
        glVertex2f(pt[0],pt[1]);
        printf("Extreme Point : t = %lf, (x,y) = (%lf,%lf)\n",tx1,pt[0],pt[1]);
      }
    }
  }


  yCoeff[0] = ptY(1)-ptY(0);
  yCoeff[1] = ptY(2)-2*ptY(1)+ptY(0);
  yCoeff[2] = ptY(3)-3*ptY(2)+3*ptY(1)-ptY(0);
  REAL yCoeffD = yCoeff[1]*yCoeff[1] - 4*yCoeff[2]*yCoeff[0];

  if(yCoeffD>=0){
    if(yCoeff[2]!=0){
      ty1 = (-yCoeff[1] + sqrt(yCoeffD))/(2*yCoeff[2]);
      ty2 = (-yCoeff[1] - sqrt(yCoeffD))/(2*yCoeff[2]);
    }
    else if(yCoeff[1]!=0){
      ty1 = -1*(yCoeff[0]/yCoeff[1]);
    }

    if(yCoeff[2]!=0){
      if(0<=ty1&&ty1<=1){
        evaluate(&curve,ty1,pt);
        ptG[ptCount] = pt;
        ptCount++;         
        glVertex2f(pt[0],pt[1]);
        printf("Extreme Point : t = %lf, (x,y) = (%lf,%lf)\n",ty1,pt[0],pt[1]);
      }

      if(0<=ty2&&ty2<=1){
        evaluate(&curve,ty2,pt);
        ptG[ptCount] = pt;
        ptCount++;         
        glVertex2f(pt[0],pt[1]);
        printf("Extreme Point : t = %lf, (x,y) = (%lf,%lf)\n",ty2,pt[0],pt[1]);
      }
    }
    else{
      if(0<=ty1&&ty1<=1){
        evaluate(&curve,ty1,pt);
        ptG[ptCount] = pt;
        ptCount++;         
        glVertex2f(pt[0],pt[1]);
        printf("Extreme Point : t = %lf, (x,y) = (%lf,%lf)\n",ty1,pt[0],pt[1]);
      }
    }
  }
  printf("xCoeffD : %lf, yCoeffD : %lf\n",xCoeffD,yCoeffD);
  glEnd();

  /* inflection points */
  glColor3ub(0, 255, 0);
  glPointSize(15.0);
  glBegin(GL_POINTS);
  REAL tInflec1,tInflec2,inflecCoeffD;
  inflecCoeff[0] = xCoeff[0]*yCoeff[1]-xCoeff[1]*yCoeff[0];
  inflecCoeff[1] = xCoeff[0]*yCoeff[2]+xCoeff[1]*yCoeff[1]-(xCoeff[2]*yCoeff[0]+xCoeff[1]*yCoeff[1]);
  inflecCoeff[2] = xCoeff[1]*yCoeff[2]+xCoeff[2]*yCoeff[1]-(xCoeff[2]*yCoeff[1]+xCoeff[1]*yCoeff[2]);

  inflecCoeffD = inflecCoeff[1]*inflecCoeff[1] - 4*inflecCoeff[0]*inflecCoeff[2];
  if(inflecCoeffD>=0){
    if(inflecCoeff[2]!=0){
      tInflec1 = (-inflecCoeff[1] + sqrt(inflecCoeffD))/(2*inflecCoeff[2]);
      tInflec2 = (-inflecCoeff[1] - sqrt(inflecCoeffD))/(2*inflecCoeff[2]);
    }
    else if(inflecCoeff[1]!=0){
      tInflec1 = -1*(inflecCoeff[0]/inflecCoeff[1]);
    }

    if(inflecCoeff[2]!=0){
      if(0<=tInflec1&&tInflec1<=1){
        evaluate(&curve,tInflec1,pt);
        ptG[ptCount] = pt;
        ptCount++;         
        glVertex2f(pt[0],pt[1]);
        printf("Inflection Point : t = %lf, (x,y) = (%lf,%lf)\n",tInflec1,pt[0],pt[1]);
      }

      if(0<=tInflec2&&tInflec2<=1){
        evaluate(&curve,tInflec2,pt);
        ptG[ptCount] = pt;
        ptCount++;         
        glVertex2f(pt[0],pt[1]);
        printf("Inflection Point : t = %lf, (x,y) = (%lf,%lf)\n",tInflec2,pt[0],pt[1]);
      }
    }
    else{
      if(0<=tInflec1&&tInflec1<=1){
        evaluate(&curve,tInflec1,pt);
        ptG[ptCount] = pt;
        ptCount++;         
        glVertex2f(pt[0],pt[1]);
        printf("Inflection Point : t = %lf, (x,y) = (%lf,%lf)\n",tInflec1,pt[0],pt[1]);
      }
    }
  }
  printf("inflecCoeffD : %lf\n",inflecCoeffD);
  glEnd();


  /* curvature extreme points */
  REAL aCoeff[3];
  aCoeff[0] = inflecCoeff[0]*18;
  aCoeff[1] = inflecCoeff[1]*18;
  aCoeff[2] = inflecCoeff[2]*18;

  REAL bCoeff[5];
  bCoeff[0] = xCoeff[0]*xCoeff[0]*9 + yCoeff[0]*yCoeff[0]*9;
  bCoeff[1] = xCoeff[0]*xCoeff[1]*2*9 + yCoeff[0]*yCoeff[1]*2*9;
  bCoeff[2] = 9*(xCoeff[2]*xCoeff[0]*2+xCoeff[1]*xCoeff[1]+yCoeff[2]*yCoeff[0]*2+yCoeff[1]*yCoeff[1]);
  bCoeff[3] = 9*(xCoeff[1]*xCoeff[2]*2+yCoeff[1]*yCoeff[2]*2);
  bCoeff[4] = 9*(xCoeff[2]*xCoeff[2] + yCoeff[2]*yCoeff[2]);
  REAL retVal;
  int depth;
  
  REAL t_list[5];
  int tCount=0;
  int tNOW;
  t_list[tCount]=0;
  REAL t_tmp =0;

  for(i=0;i<32;i++){
    evaluate_curvature(&curve,t_tmp,aCoeff,bCoeff,&retVal);
    REAL save = retVal;
    REAL save_t = t_tmp;
    t_tmp+=1/32;
    evaluate_curvature(&curve,t_tmp,aCoeff,bCoeff,&retVal);
    if(save*retVal<=0){
      int j;
      int same=-1;
      for(j=0;j<tCount;j++){
        if(t_list[j]==save_t)
          same *= -1;
      }
      if(same<0){
        t_list[tCount]=save_t;
        tCount++;
      }
    }
  }
  for(depth=1;depth<4;depth++){
    for(tNOW = 0;tNOW<tCount;tNOW++){
      t_tmp = t_list[tNOW];
      for(i=0;i<32;i++){
        evaluate_curvature(&curve,t_tmp,aCoeff,bCoeff,&retVal);
        REAL save = retVal;
        REAL save_t = t_tmp;
        t_tmp+=pow(1/32,depth+1);
        evaluate_curvature(&curve,t_tmp,aCoeff,bCoeff,&retVal);
        if(save*retVal<=0)
          t_list[tNOW] = save_t;
      }
    }
  }
  glColor3ub(255, 0, 0);
  glPointSize(15.0);
  glBegin(GL_POINTS);

  for(i=0;i<tCount;i++){
    evaluate(&curve,t_list[i],pt);
    ptG[ptCount] = pt;
    ptCount++;         
    glVertex2f(pt[0],pt[1]);
    printf("Curvature Extreme Point : t = %lf, (x,y) = (%lf,%lf)\n",t_list[i],pt[0],pt[1]);
  }
  glEnd();


  /* bca */
  for(i=0;i<=tCount;i++){
    Point pt0;
    Point pt1;
    evaluate(&curve,0,pt0);
    evaluate(&curve,1,pt1);
    Point ptL = i==0 ? pt0 : ptG[i-1];
    Point ptR = i==tCount ? pt1 : ptG[i];
    Point vecH;

  }




  printf("\n\n");
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
