// CS 445/545 Prog 1 for Digya Achayrya
/////////////////////////////////////////////////////////////////////////////////////////////
// flyingGeeseAnimation.cpp
// This program implements a frame-based animation (timer event-based) of three geese flying 
// accross the screen at the rate of 10 units (1 move) per 100 msec.
//
// EXTRA CREDIT:
// 1. Birds flap their wings as they move. 
// 2. Pressing 'ENTER' restarts the animation after the birds fly off the screen. 
// 3. Press 'SPACE' for pausing the animation and any key for starting/playing it again from
// the paused position.
//
// Interaction: Press any key (numbers and alphabets) to start the animation.
//
// Digya Acharya
/////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "OpenGL445Setup.h"

// Global variables
static int isAnimate = 0; // Flag to keep track of the animation state
static int animationPeriod = 100; // Time interval between consecutive frames

// Position of birds
static float z; // Position in the z-plane
static float g12_x1; // Position of the tip of tail of the two leftmost birds
static float g12_x2; // Position of the tip of head of the two leftmost birds
static float g3_x1; // Position of the tip of tail of a bird in the front
static float g3_x2; // Position of the tip of head of a bird in the front
static float g1_y; // Value in the y-axis where the topmost bird in left lies
static float g2_y; // Value in the y-axis where the bottom bird in left lies
static float g3_y; // Value in the y-axis where the front bird lies

static float x_pos; // current offset for movement in x-direction each frame
static float wing_pos1; // the first wing value set to be approx. 90 degree with the next wing
static float wing_pos2; // the second wing value set to be approx. 90 degree with the first one


void init() {
	/* Sets background color and value of the coordinates at the initial position. */

	// Sets initial background color
	glClearColor(1.0, 1.0, 1.0, 1.0);

	// Sets initial value of the coordinates
	z = -1;
	g12_x1 = 60.0;
	g12_x2 = 150.0;
	g3_x1 = 170.0;
	g3_x2 = 260.0;
	g1_y = 430.0;
	g2_y = 360.0;
	g3_y = 395.0;
	
	// Initial values of the x-offset and wing position
	x_pos = 0.0;
	wing_pos1 = 75.0;
	wing_pos2 = 185.0;
}

void draw_geese(float x1, float x2, float x_pos, float y, float z, float wing_pos) {
	/* This function draws a single geese with the given parameters.*/

	// x_mid - the position from where the wing starts
	float x_mid = (x1 + x2) / 2;

	// Draws a geese with three line segments
	glBegin(GL_LINES);
	glVertex3f(x1 + x_pos, y, z);
	glVertex3f(x2 + x_pos, y, z);

	glVertex3f(x_mid + x_pos, y, z);
	glVertex3f(wing_pos + x_pos, y + 30, z);

	glVertex3f(x_mid + x_pos, y, z);
	glVertex3f(wing_pos + x_pos, y - 30, z);
	glEnd();
	glFlush();
}

void display_func(void) {
	/* This is called whenever a window needs to be displayed or redisplayed. */

	// Clears the geese in the last position by setting the background color to white 
	glClear(GL_COLOR_BUFFER_BIT);

	// Draws a black geese with a line width of 1.
	glColor3f(0.0, 0.0, 0.0);
	glLineWidth(1.0);
	draw_geese(g12_x1, g12_x2, x_pos, g1_y, z, wing_pos1);
	draw_geese(g12_x1, g12_x2, x_pos, g2_y, z, wing_pos1);
	draw_geese(g3_x1, g3_x2, x_pos, g3_y, z, wing_pos2);
}

void moveGeeseAndFlapWings() {
	/* This function increases the x position and wing position to the right of the screen. */

	x_pos += 10.0;

	// Wing position cycles between 3 values, i.e, 75, 95 and 115 for the leftmost birds and 185, 205 and 225
	//for a front bird.

	// Increases value from 75 if less than 115
	wing_pos1 += 20.0;
	wing_pos2 += 20.0;
	// Resets value to 75 if greater than 115
	if (wing_pos1 > 115) {
		wing_pos1 = 75.0;
		wing_pos2 = 185.0;
	}
}

void animate(int value) {
	/* Recursive call to animate after each 100 msec. */

	// At each 100 msec, checks isAnimate flag and proceeds animation 
	if (isAnimate)
	{
			moveGeeseAndFlapWings();
			glutPostRedisplay();
			glutTimerFunc(animationPeriod, animate, 0);	
	}
}

void restartAnimationFromStart() {
	/* Restarts the animation from start by setting initial global values and calls display_func. */
	if (isAnimate == 0) {
		isAnimate = 1;
	}
	// Initialize global variables
	init();
	glutPostRedisplay();		
}

void startAnimationFromCurrentLocation() {
	/* Starts animation from the current location. */
	if (isAnimate == 0) {
		isAnimate = 1;
		glutTimerFunc(animationPeriod, animate, 0);
	}
	std::cout << "Press enter to restart animation and space to pause animation." << std::endl;
}

void pauseAnimation() {
	/* Sets 'isAnimate' flag to 0 to pause animation. */
	isAnimate = 0;
}

void keyInput(unsigned char key, int x, int y) {
	/* Function to handle keyboard input. */
		switch (key)
		{
		case 13: 
			// Restarts animation from start on pressing ENTER
			restartAnimationFromStart();
			break;
		case ' ':
			// Pauses animation on pressing SPACE
			pauseAnimation();
			break;
		default:
			// Starts animation on any key press
			startAnimationFromCurrentLocation();
		}
}

// Set width and height of canvas to 480 by 480.
#define canvas_Width 480
#define canvas_Height 480
char canvas_Name[] = "FLYING GEESE ANIMATION";

int main(int argc, char ** argv) {
	std::cout << "Any Key Click Will Start Animation.." << std::endl;
	glutInit(&argc, argv);
	my_setup(canvas_Width, canvas_Height, canvas_Name);
	
	// Timer function for moving geese every 100 msec
	glutTimerFunc(animationPeriod, animate, 0);
	// Display function for clearing the screen and redrawing before each new frame is generated
	glutDisplayFunc(display_func);
	// Keyboard function for handling different key press
	glutKeyboardFunc(keyInput);

	// Initialize global variables
	init();
	glutMainLoop();
	return 0;
}