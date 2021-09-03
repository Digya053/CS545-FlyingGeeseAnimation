#include <GL/glew.h>
#include <GL/freeglut.h>
#include "OpenGL445Setup.h"

static float x_pos = 0.0;
static float wing_pos1 = 60.0;
static float wing_pos2 = 170.0;

static int isAnimate = 0;
static int animationPeriod = 100;


void draw_geese(float x1, float x2, float x_pos, float y, float z, float wing_pos) {
	float x_mid = (x1 + x2) / 2;
	
	glVertex3f(x1 + x_pos, y, z);
	glVertex3f(x2 + x_pos, y, z);
		
	glVertex3f(x_mid + x_pos, y, z);
	glVertex3f(wing_pos + x_pos, y + 30, z);
		
	glVertex3f(x_mid + x_pos, y, z);
	glVertex3f(wing_pos + x_pos, y - 30, z);
	
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

void restartAnimation() {
	if (isAnimate == 0) {
		isAnimate = 1;
		glutTimerFunc(animationPeriod, animate, 0);
	}
}

void pauseAnimation() {
	isAnimate = 0;
}

// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y)
{
	if (key == 'p') {
		if (isAnimate) {
			pauseAnimation();
		}
	}
	else {
		restartAnimation();
	}
}

void display_func(void)
{
	// this callback is automatically called whenever a window needs to be displayed or 
	// redisplayed
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.0, 0.0);

	glLineWidth(1);
	glBegin(GL_LINES);
	draw_geese(60.0, 150.0, x_pos, 430.0, -1, wing_pos1);
	draw_geese(60.0, 150.0, x_pos, 360.0, -1, wing_pos1);
	draw_geese(170.0, 260.0, x_pos, 395.0, -1, wing_pos2);
	glEnd();
	glFlush();
		
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

	glutKeyboardFunc(keyInput);


	glutMainLoop();
	return 0;
}