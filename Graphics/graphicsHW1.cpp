#include <GL/freeglut.h>

enum {
	BUTTON_LEFT = 0,
	BUTTON_RIGHT,
	BUTTON_LEFT_TRANSLATE,
};

/* set global variables */
int mButton = -1;
int mOldY, mOldX;

/* vectors that makes the rotation and translation of the cube */
float eye[3] = {0.0f, 0.0f, 10.0f};
float rot[3] = {0.0f, 0.0f, 0.0f};

void clamp(float *v)
{
    int i;

    for (i = 0; i < 3; i ++)
        if (v[i] > 360 || v[i] < -360)
            v[i] = 0;
}

//------------------------------------------------------------------------
// Moves the screen based on mouse pressed button
//------------------------------------------------------------------------
void glutMotion(int x, int y)
{
    if (mButton == BUTTON_LEFT)
    {
        /* rotates screen */
        rot[0] -= (mOldY - y);
        rot[1] -= (mOldX - x);
        clamp (rot);
    }
	else if (mButton == BUTTON_RIGHT)
    {
        /*
           translate the screen, z axis
           gives the idea of zooming in and out 
        */        
        eye[2] -= (mOldY - y) * 0.05f; // here I multiply by a 0.2 factor to 
                                      // slow down the zoom
        clamp (rot);
    } 
    else if (mButton == BUTTON_LEFT_TRANSLATE)
    {
        eye[0] += (mOldX - x) * 0.01f;
        eye[1] -= (mOldY - y) * 0.01f;
        clamp (rot);
    }

    mOldX = x;
    mOldY = y;
}

//------------------------------------------------------------------------
// Function that handles mouse input
//------------------------------------------------------------------------
void glutMouse(int button, int state, int x, int y)
{
    if(state == GLUT_DOWN)
    {
        mOldX = x;
        mOldY = y;
        switch(button)
        {
            case GLUT_LEFT_BUTTON:
                if (glutGetModifiers() == GLUT_ACTIVE_CTRL)
                {
                   mButton = BUTTON_LEFT_TRANSLATE;
                   break;
                } else
                {
                   mButton = BUTTON_LEFT;
                   break;
                }
            case GLUT_RIGHT_BUTTON:
                mButton = BUTTON_RIGHT;
                break;
        }
    } else if (state == GLUT_UP)
      mButton = -1;
}

void drawBox() {
	glColor3f(1.f, 0.f, 0.f);
	glBegin(GL_LINE_LOOP);
		glVertex3f(-1.f, -1.f, -1.f);
		glVertex3f(1.f, -1.f, -1.f);
		glVertex3f(1.f, 1.f, -1.f);
		glVertex3f(-1.f, 1.f, -1.f);
	glEnd();
	glColor3f(0.f, 1.f, 0.f);
	glBegin(GL_LINE_LOOP);
		glVertex3f(-1.f, -1.f, 1.f);
		glVertex3f(1.f, -1.f, 1.f);
		glVertex3f(1.f, 1.f, 1.f);
		glVertex3f(-1.f, 1.f, 1.f);
	glEnd();
	glColor3f(0.f, 0.f, 1.f);
	glBegin(GL_LINES);
		glVertex3f(-1.f, -1.f, -1.f);
		glVertex3f(-1.f, -1.f, 1.f);
		glVertex3f(1.f, -1.f, -1.f);
		glVertex3f(1.f, -1.f, 1.f);		
		glVertex3f(1.f, 1.f, -1.f);
		glVertex3f(1.f, 1.f, 1.f);
		glVertex3f(-1.f, 1.f, -1.f);
		glVertex3f(-1.f, 1.f, 1.f);
	glEnd();
}

void display() {

	glClearColor(1.f, 1.f, 1.f, 1.f);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glLoadIdentity();	
	
	glTranslatef (-eye[0], -eye[1], -eye[2]);

	glRotatef(rot[0], 1.0f, 0.0f, 0.0f);
	glRotatef(rot[1], 0.0f, 1.0f, 0.0f);
	glRotatef(rot[2], 0.0f, 0.0f, 1.0f);


	drawBox();

	
	glutSwapBuffers();
}

void resize(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f,(GLfloat)w/(GLfloat)h,.1f,100.0f);	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void keyboard(unsigned char key, int x, int y) {
	switch (key) {		
		case 27:
			exit(0);
			break;
		default:
			break;
	}
}

void idle(){
	glutPostRedisplay();
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(250, 250);
	glutCreateWindow("Example");
	
	glutDisplayFunc(display);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(glutMouse);
	glutMotionFunc(glutMotion);
	glutIdleFunc(idle);
	glutMainLoop();

	return 0;
}
