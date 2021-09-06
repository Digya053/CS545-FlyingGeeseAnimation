///////////////////////////////////////////////////////////////////////////////////////////////////////////
// CS 445/545 Prog 1 for Digya Acharya
//
// flyingGeeseAnimation.cpp
// This program implements a frame-based animation (timer event-based) of three geese flying across the
// screen at the rate of 10 units (1 move) per 100 msec. A single function (draw_geese()) has been used to 
// draw all three birds, moveGeeseAndFlapWings() increases the x-offset and wing position and animate() is
// called every 100 msec which calls that function and redraws geese in new position.
//
// EXTRA CREDIT:
// 1. Birds flap their wings as they move. 
// 2. Pressing any key (numbers and alphabets) starts and restarts the animation. 
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "OpenGL445Setup.h"

// Global variables
static int isAnimate = 0; // Flag to keep track of the animation state
static int animationPeriod = 100; // Time interval between consecutive frames
static float start_flag; // Keeps track of whether the program has started for the first time or it's a restart

// Position of birds
static float z; // Position in the z-plane
static float g12_x1; // Position of the tip of tail of the two leftmost birds
static float g12_x2; // Position of the tip of head of the two leftmost birds
static float g3_x1; // Position of the tip of tail of a bird in the front
static float g3_x2; // Position of the tip of head of a bird in the front
static float g1_y; // Value in the y-axis where the topmost bird in left lies
static float g2_y; // Value in the y-axis where the bottom bird in left lies
static float g3_y; // Value in the y-axis where the front bird lies

static float x_pos; // Current offset for movement in x-direction each frame
static float wing_pos1; // the first wing value set to be approx. 90 degree with the next wing
static float wing_pos2; // the second wing value set to be approx. 90 degree with the first one


void init() {
	/* Sets the background color and value of the coordinates at the initial position. */

	// Sets the background color to white
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

	// Wing position cycles between 3 values, i.e, 75, 95 and 115 for the leftmost birds and 185, 205 and
	// 225 for a front bird.

	// Increases value from 75 and 185
	wing_pos1 += 20.0;
	wing_pos2 += 20.0;
	// Resets value to 75 and 185 if position of the wing of first bird is greater than 115
	if (wing_pos1 > 115) {
		wing_pos1 = 75.0;
		wing_pos2 = 185.0;
	}
}

void animate(int value) {
	/* Recursive call to animate after each 100 msec. */

	// At each 100 msec, checks if isAnimate flag is 1 and if it is, starts animation
	if (isAnimate)
	{
		//Move birds toward the right of the screen and redraws frame
		moveGeeseAndFlapWings();
		glutPostRedisplay();
		glutTimerFunc(animationPeriod, animate, 0);	
	}
}

void restartAnimationFromStart() {
	/* Restarts the animation from start by setting initial global values and calls display_func(). */
	if (isAnimate == 0) {
		isAnimate = 1;
	}
	// Initializes global variables
	init();
	glutPostRedisplay();		
}

void startAnimationFromCurrentLocation() {
	/* Starts animation from the current location. */
	if (isAnimate == 0) {
		isAnimate = 1;
		glutPostRedisplay();
		glutTimerFunc(animationPeriod, animate, 0);
	}
	// Start flag is increased on each animation
	start_flag += 1;
	std::cout << "Press any key to restart animation.." << std::endl;
}

void keyInput(unsigned char key, int x, int y) {
	/* Function to handle keyboard input. */
	if (start_flag == 0) {
	// On new start, animation starts from the current location
		startAnimationFromCurrentLocation();
	}
	else {
	// On restart, the geese are placed in the initial position again before animation
		restartAnimationFromStart();
	}
}


// Sets width and height of canvas to 480 by 480.
#define canvas_Width 480
#define canvas_Height 480
char canvas_Name[] = "FLYING GEESE ANIMATION";


int main(int argc, char ** argv) {
	std::cout << "Any Key Click Will Start Animation.." << std::endl;
	glutInit(&argc, argv);
	my_setup(canvas_Width, canvas_Height, canvas_Name);
	
	// Moves geese every 100 msec
	glutTimerFunc(animationPeriod, animate, 0);
	// Clears the screen and redraws before each new frame is generated
	glutDisplayFunc(display_func);
	// Handles different key press
	glutKeyboardFunc(keyInput);

	// Initializes global variables
	init();
	glutMainLoop();
	return 0;
}