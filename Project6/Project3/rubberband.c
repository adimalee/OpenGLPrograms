#include <stdlib.h>
#include <GL/glut.h>

float xm, ym, xmm, ymm;
float width = 500, height = 500;
int first = 0;

void mouse(int btn, int state, int x, int y)
{
	if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		xm = x / 500.0;
		ym = (height - y) / 500.0;
		glColor3f(0.0, 0.0, 1.0);
		glLogicOp(GL_XOR);
		first = 0;
	}
	if (btn == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		//glBegin(GL_LINES);
		//	glVertex2f(xm, ym);
		//	glVertex2f(xmm, ymm);
		//glEnd();
		//glFlush();
		glRectf(xm, ym, xmm, ymm);
		glFlush();
		glColor3f(0.0, 1.0, 0.0);
		//glLogicOp(GL_COPY);
		xmm = x / 500.0;
		ymm = (height - y) / 500.0;
		glLogicOp(GL_COPY);
		glRectf(xm, ym, xmm, ymm);
		//glBegin(GL_LINES);
		//glVertex2f(xm, ym);
		//glVertex2f(xmm, ymm);
		//glEnd();
		glFlush();
	}
}

void myReshape(int w, int h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 1, 0, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glViewport(0, 0, w, h);
	width = w; height = h;
}


void move(int x, int y)
{
	if (first == 1)
	{
		//glBegin(GL_LINES);
		//glVertex2f(xm, ym);
		//glVertex2f(xmm, ymm);
		//glEnd();
		glRectf(xm, ym, xmm, ymm);
		glFlush();
	}

	xmm = x / 500.0;
	ymm = (500 - y) / 500.0;
	//glBegin(GL_LINES);
	//glVertex2f(xm, ym);
	//glVertex2f(xmm, ymm);
	//glEnd();
	glRectf(xm, ym, xmm, ymm);
	glFlush();

	first = 1;
}


void myinit()
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glLineWidth(3.0);
}

/* display callback required by GLUT */

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glutSwapBuffers();
	glFlush();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(width, height);
	glutCreateWindow("Rubberband");
	myinit();
	glEnable(GL_COLOR_LOGIC_OP);
	glutReshapeFunc(myReshape);
	glutMouseFunc(mouse);
	glutMotionFunc(move);
	glutDisplayFunc(display);

	glutMainLoop();
}