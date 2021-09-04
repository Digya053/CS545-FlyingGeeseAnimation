/////////////////////////////////////////////////////////////////////////////////////////////
// flyingGeeseAnimation.cpp
//
// This program implements a simple animation of three geese flying accross the screen. 
//
//
//
//
//
//
//
//
// Digya Acharya
/////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "OpenGL445Setup.h"

using namespace std;

int isAnimate = 0;
int animationPeriod = 100;

float g12_x1;
float g12_x2;
float g3_x1;
float g3_x2;
float g1_y;
float g2_y;
float g3_y;
float z;

float x_pos;
float wing_pos1;
float wing_pos2;

void init() {
	g12_x1 = 60.0;
	g12_x2 = 150.0;
	g3_x1 = 170.0;
	g3_x2 = 260.0;
	g1_y = 430.0;
	g2_y = 360.0;
	g3_y = 395.0;
	z = -1;
	x_pos = 0.0;
	wing_pos1 = 60.0;
	wing_pos2 = 170.0;
}

void draw_geese(float x1, float x2, float x_pos, float y, float z, float wing_pos) {
	float x_mid = (x1 + x2) / 2;

	glBegin(GL_LINES);
	glLineWidth(1);
	glVertex3f(x1 + x_pos, y, z);
	glVertex3f(x2 + x_pos, y, z);

	glVertex3f(x_mid + x_pos, y, z);
	glVertex3f(wing_pos + x_pos, y + 30, z);

	glVertex3f(x_mid + x_pos, y, z);
	glVertex3f(wing_pos + x_pos, y - 30, z);
	glEnd();
	glFlush();
}

void display_func(void)
{
	// this callback is automatically called whenever a window needs to be displayed or 
	// redisplayed
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.0, 0.0);

	draw_geese(g12_x1, g12_x2, x_pos, g1_y, z, wing_pos1);
	draw_geese(g12_x1, g12_x2, x_pos, g2_y, z, wing_pos1);
	draw_geese(g3_x1, g3_x2, x_pos, g3_y, z, wing_pos2);
}

void moveGeeseAndFlapWings()
{
	x_pos += 10.0;
	if (wing_pos1 < 105) {
		wing_pos1 += 15;
		wing_pos2 += 15;
	}
	else {
		wing_pos1 -= 15;
		wing_pos2 -= 15;
	}
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

void restartAnimationFromStart() {
	if (isAnimate == 0) {
		isAnimate = 1;
	}
	init();
	glutPostRedisplay();		
}

void startAnimationFromCurrentLocation() {
	if (isAnimate == 0) {
		isAnimate = 1;
		glutTimerFunc(animationPeriod, animate, 0);
	}
	cout << "Press enter to restart animation and space to pause animation." << endl;
}

void pauseAnimation() {
	isAnimate = 0;
}

// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y)
{
	//Any key to start, space to pause, any key to continue after pausing, enter to restart.
	{

		switch (key)
		{
		case 13: //Enter Key
			restartAnimationFromStart();
			break;
		case ' ':
			pauseAnimation();
			break;
		default:
			startAnimationFromCurrentLocation();
		}
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
	cout << "Any Key Click Will Start.." << endl;

	glClearColor(1.0, 1.0, 1.0, 1.0);
	
	glutTimerFunc(animationPeriod, animate, 0);
	
	glutDisplayFunc(display_func);
	//glutTimerFunc(animationPeriod, animate, 0);

	glutKeyboardFunc(keyInput);

	init();
	glutMainLoop();
	return 0;
}