#include <iostream>
#include <cstdlib>
#include <cmath>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "OpenGL445Setup.h"

// CS 445/545 OpenGL Program skeleton

float flap = 95.0;
float flap1 = 205.0;
// Vertex coordinate vectors for the annulus
/*static float vertices1[] =
{
	60.0, 430.0, 0.0,
	150.0, 430.0, 0.0,
	105.0, 430.0, 0.0,
	flap, 470.0, 0.0,
	105.0, 430.0, 0.0,
	flap, 390.0, 0.0,

	60.0, 360.0, 0.0,
	150.0, 360.0, 0.0,
	105.0, 360.0, 0.0,
	flap, 400.0, 0.0,
	105.0, 360.0, 0.0,
	flap, 320.0, 0.0,

	170.0, 395.0, 0.0,
	260.0, 395.0, 0.0,
	215.0, 395.0, 0.0,
	flap1, 435.0, 0.0,
	215.0, 395.0, 0.0,
	flap1, 355.0, 0.0
};*/

/*static float colors1[] =
{
	0.0, 0.0, 0.0,
	0.0, 0.0, 0.0,
	0.0, 0.0, 0.0,
	0.0, 0.0, 0.0,
	0.0, 0.0, 0.0,
	0.0, 0.0, 0.0,
	0.0, 0.0, 0.0,
	0.0, 0.0, 0.0,
	0.0, 0.0, 0.0,
	0.0, 0.0, 0.0,
	0.0, 0.0, 0.0,
	0.0, 0.0, 0.0,
	0.0, 0.0, 0.0,
	0.0, 0.0, 0.0,
	0.0, 0.0, 0.0,
	0.0, 0.0, 0.0,
	0.0, 0.0, 0.0,
	0.0, 0.0, 0.0
};*/

static float translate = 0.0;

static int isAnimate = 0;
static int animationPeriod = 100;
static unsigned int stripIndices[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17};


void display_func(void)
{
	// this callback is automatically called whenever a window needs to be displayed or 
	// redisplayed
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.0, 0.0);
	
	glLineWidth(1);
	glPushMatrix();
	//glTranslatef(flap, 0.0, 0.0);
	//glTranslatef(flap1, 0.0, 0.0);
	float vertices1[] =
	{
		60.0, 430.0, 0.0,
		150.0, 430.0, 0.0,
		105.0, 430.0, 0.0,
		flap, 470.0, 0.0,
		105.0, 430.0, 0.0,
		flap, 390.0, 0.0,

		60.0, 360.0, 0.0,
		150.0, 360.0, 0.0,
		105.0, 360.0, 0.0,
		flap, 400.0, 0.0,
		105.0, 360.0, 0.0,
		flap, 320.0, 0.0,

		170.0, 395.0, 0.0,
		260.0, 395.0, 0.0,
		215.0, 395.0, 0.0,
		flap1, 435.0, 0.0,
		215.0, 395.0, 0.0,
		flap1, 355.0, 0.0
	};

	glVertexPointer(3, GL_FLOAT, 0, vertices1);
	//glColorPointer(3, GL_FLOAT, 0, colors1);
	
	glTranslatef(translate, 0.0, 0.0);
	glDrawElements(GL_LINES, 18, GL_UNSIGNED_INT, stripIndices);
	glPopMatrix();
	//glutSwapBuffers();
	glFlush();
}



void moveGeeseAndFlapWings()
{
	translate += 10.0;
	if (flap < 105) {
		flap += 15;
		flap1 += 15;
	}
	else {
		flap -= 15;
		flap1 -= 15;
	}
	//flap, flap1 = flap_value(flap, flap1);
	/*flap += 5;
	flap1 += 5;*/
	/*float flap_array[] = {100.0,105.0,100.0,95.0};
	float flap1_array[] = {210.0, 215.0, 210.0, 205.0};
	for (int i = 0; i < 4; i++) {
		flap = flap_array[i];
		flap1 = flap1_array[i];
	}*/
}

void animate(int value)
{
	if (isAnimate)
	{
		moveGeeseAndFlapWings();

		glutPostRedisplay();
		glutTimerFunc(animationPeriod, animate, 0);
	}
}

// Keyboard input processing routine.

void keyInput(unsigned char key, int x, int y)

{

	switch (key)

	{

	case 27:

		exit(0);

		break;

	case ' ':

		if (isAnimate) isAnimate = 0;

		else

		{

			isAnimate = 1;

			animate(1);

		}

		break;

	default:

		break;

	}

}

//can customize the below 3 items to make canvas of ones own size and labelling

#define canvas_Width 480
#define canvas_Height 480
char canvas_Name[] = "NAME OF CANVAS";

// #define canvas_Name "NAME OF CANVAS"

int main(int argc, char ** argv)
{
	glutInit(&argc, argv);
	my_setup(canvas_Width, canvas_Height, canvas_Name);

	glClearColor(1.0, 1.0, 1.0, 1.0);
	
	
	glutDisplayFunc(display_func);

	
	glEnableClientState(GL_VERTEX_ARRAY);

	//glEnableClientState(GL_COLOR_ARRAY);
	glutKeyboardFunc(keyInput);


	glutMainLoop();
	return 0;
}