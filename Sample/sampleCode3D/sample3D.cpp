//	This is a sample program that illustrates OpenGL and GLUT in 3D. It
//	renders a picture of 36 snowmen. The camera can be moved by dragging
//	the mouse. The camera moves forward by hitting the up-arrow key and
//	back by moving the down-arrow key. Hit ESC, 'q' or 'Q' to exit.
//
//	Warning #1: This program uses the function glutSpecialUpFunc, which
//	may not be available in all GLUT implementations. If your system
//	does not have it, you can comment this line out, but the up arrow
//	processing will not be correct.
//----------------------------------------------------------------------

#include <stdlib.h> 
#include <math.h> 
#include <stdio.h> 
#include <cstdlib>
#include <cmath>
// The following works for both linux and MacOS
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

// escape key (for exit)
#define ESC 27
#define PI 3.141592653589
#define DEG2RAD(deg) (deg * PI / 180)
#include <string>
#include <iostream>
using namespace std;
int win_width = 800, win_height = 400;

//----------------------------------------------------------------------
// Global variables
//
// The coordinate system is set up so that the (x,y)-coordinate plane
// is the ground, and the z-axis is directed upwards. The y-axis points
// to the north and the x-axis points to the east.
//
// The values (x,y) are the current camera position. The values (lx, ly)
// point in the direction the camera is looking. The variables angle and
// deltaAngle control the camera's angle. The variable deltaMove
// indicates the amount of incremental motion for the camera with each
// redraw cycle. The variables isDragging and xDragStart are used to
// monitor the mouse when it drags (with the left button down).
//----------------------------------------------------------------------

// Camera position
float x = 0.0, y = -5.0; // initially 5 units south of origin
float deltaMove = 0.0; // initially camera doesn't move

// Camera direction
float lx = 0.0, ly = 1.0; // camera points initially along y-axis
float angle = 0.0; // angle of rotation for the camera direction
float deltaAngle = 0.0; // additional angle change when dragging

// Mouse drag control
int isDragging = 0; // true when dragging
int xDragStart = 0; // records the x-coordinate when dragging starts


int moving = 0;		// is bike moving 
int direction_move = 0;  // 1 when forward; -1 when backward

float bwheelrad = 0.5;
float blen = 2.0;
float bwheelthick = 0.2;
float tilta = 0;            // positive tilt angle will turn the handle right
float bturna = 0.0;			// Turn angle of bike with y axis.
float bacceleration = 0.0;
float bvelx =0.0;
float bvely =0.0;
float bposx =0.0;
float bposy =5.0;
float bposz =0.0;
float roc;
float omega;
float tempa;
float angla=0.0;

float meuw = 0.5;				// To be decided
float g = 10;
float mass = 100;
float friction;




//----------------------------------------------------------------------
// Reshape callback
//
// Window size has been set/changed to w by h pixels. Set the camera
// perspective to 45 degree vertical field of view, a window aspect
// ratio of w/h, a near clipping plane at depth 1, and a far clipping
// plane at depth 100. The viewport is the entire window.
//
//----------------------------------------------------------------------
void changeSize(int w, int h) 
{
	float ratio =  ((float) w) / ((float) h); // window aspect ratio
	glMatrixMode(GL_PROJECTION); // projection matrix is active
	glLoadIdentity(); // reset the projection
	gluPerspective(45.0, ratio, 0.1, 100.0); // perspective transformation
	glMatrixMode(GL_MODELVIEW); // return to modelview mode
	glViewport(0, 0, w, h); // set viewport (drawing area) to entire window
}

//----------------------------------------------------------------------
// Draw one snowmen (at the origin)
//
// A snowman consists of a large body sphere and a smaller head sphere.
// The head sphere has two black eyes and an orange conical nose. To
// better create the impression they are sitting on the ground, we draw
// a fake shadow, consisting of a dark circle under each.
//
// We make extensive use of nested transformations. Everything is drawn
// relative to the origin. The snowman's eyes and nose are positioned
// relative to a head sphere centered at the origin. Then the head is
// translated into its final position. The body is drawn and translated
// into its final position.
//----------------------------------------------------------------------
void drawSnowman()
{
	// Draw body (a 20x20 spherical mesh of radius 0.75 at height 0.75)
	glColor3f(1.0, 1.0, 1.0); // set drawing color to white
	glPushMatrix();
	glTranslatef(0.0, 0.0, 0.75);
	glutSolidSphere(0.75, 25, 25);
	glPopMatrix();

	// Draw the head (a sphere of radius 0.25 at height 1.75)
	glPushMatrix();
	glTranslatef(0.0, 0.0, 1.75); // position head
	glutSolidSphere(0.25, 20, 20); // head sphere

	// Draw Eyes (two small black spheres)
	glColor3f(0.0, 0.0, 0.0); // eyes are black
	glPushMatrix();
	glTranslatef(0.0, -0.18, 0.10); // lift eyes to final position
	glPushMatrix();
	glTranslatef(-0.05, 0.0, 0.0);
	glutSolidSphere(0.05, 10, 10); // right eye
	glPopMatrix();
	glPushMatrix();
	glTranslatef(+0.05, 0.0, 0.0);
	glutSolidSphere(0.05, 10, 10); // left eye
	glPopMatrix();
	glPopMatrix();

	// Draw Nose (the nose is an orange cone)
	glColor3f(1.0, 0.5, 0.5); // nose is orange
	glPushMatrix();
	glRotatef(90.0, 1.0, 0.0, 0.0); // rotate to point along -y
	glutSolidCone(0.08, 0.5, 10, 2); // draw cone
	glPopMatrix();
	glPopMatrix();

	// Draw a faux shadow beneath snow man (dark green circle)
	glColor3f(0.0, 0.5, 0.0);
	glPushMatrix();
	glTranslatef(0.2, 0.2, 0.001);	// translate to just above ground
	glScalef(1.0, 1.0, 0.0); // scale sphere into a flat pancake
	glutSolidSphere(0.75, 20, 20); // shadow same size as body
	glPopMatrix();
}

void drawBike()
{
	GLfloat cyan[] = {0.8f, .8f, .8f, 0.f};
	glMaterialfv(GL_FRONT, GL_DIFFUSE, cyan);
	glTranslatef(0.0,0.0,bwheelrad + bwheelthick );
	glRotatef( tilta , 0 , 1 , 0 );
	//--------------------Body-----------------
	glPushMatrix();
	glColor3f(0.5, 0.5, 0.5); 
	glScalef(0.5, blen , 0.5);
	glutSolidCube(1.0);
	glPopMatrix();

	//--------------------Tank------------------
	glPushMatrix();
	glTranslatef( 0.0 , blen/4 ,0.2);
	glColor3f(0.9, 0.8, 0.0); 
	glScalef(0.5, 1.0, 1.0); // scale sphere into a tank
	glutSolidSphere(0.5, 20, 20); // shadow same size as body
	glScalef(1.5, 1.0, 1.0);
	glRotatef(90.0, 0.0, 1.0, 0.0);	
	glColor3f(0.0, 0.2, 1.0);
	glutWireTorus( 0.25, 0.25, 15, 20);
	glPopMatrix();
	
	//--------------------Person----------------
	glPushMatrix();				// Seat
		glTranslatef(0.0,-blen/4,0.3);
		glColor3f(0.9, 0.9, 0.9); 
		glScalef(0.7 , 0.5, 0.5);
		glutSolidCube(1.0);
		
		glTranslatef(0.0,0.5,1.2);		// Body
		glRotatef(-30.0, 1.0, 0.0, 0.0);
		glScalef(1.0 , 1.0, 2.5);
		glutSolidCube(1.0);

		glPushMatrix();				// Hands
			glTranslatef(0.0,-0.5,0.5);
			glRotatef(-5,1.0,0,0);	
			
			glPushMatrix();
			glTranslatef(-0.65,1.8,0.0);		//left
			glScalef(0.35,3.0,0.2);
			glutSolidCube(1.0);
			glPopMatrix();
			
			glPushMatrix();
			glTranslatef(0.65,1.8,0.0);		//right
			glScalef(0.35,3.0,0.2);
			glutSolidCube(1.0);
			glPopMatrix();
		glPopMatrix();

		glPushMatrix();				// Legs
			glTranslatef(0.0,-0.5,-0.5);
			glRotatef(5,1.0,0,0);	
			
			glPushMatrix();
			glTranslatef(-0.65,1.8,0.0);		//left
			glScalef(0.35,2.5,0.2);
			glutSolidCube(1.0);
			glPopMatrix();
			
			glPushMatrix();
			glTranslatef(0.65,1.8,0.0);		//right
			glScalef(0.35,2.5,0.2);
			glutSolidCube(1.0);
			glPopMatrix();
		glPopMatrix();
		
		glScalef(4.0 , 5.0, 2.0);
		
		glPushMatrix();
		glTranslatef(0.0, 0.0, 0.5); // position head
		glutSolidSphere(0.25, 20, 20); // head sphere

		// Draw Eyes (two small black spheres)
		glColor3f(0.0, 0.0, 0.0); // eyes are black
		glPushMatrix();
		glTranslatef(0.0, 0.18, 0.10); // lift eyes to final position
		glPushMatrix();
		glTranslatef(-0.05, 0.0, 0.0);
		glutSolidSphere(0.05, 10, 10); // right eye
		glPopMatrix();
		glPushMatrix();
		glTranslatef(+0.05, 0.0, 0.0);
		glutSolidSphere(0.05, 10, 10); // left eye
		glPopMatrix();
		glPopMatrix();

		// Draw Nose (the nose is an orange cone)
		glColor3f(1.0, 0.5, 0.5); // nose is orange
		glPushMatrix();
		glRotatef(-90.0, 1.0, 0.0, 0.0); // rotate to point along y
		glutSolidCone(0.08, 0.5, 10, 2); // draw cone
		glPopMatrix();
		glPopMatrix();
	glPopMatrix();

	//-------------------Handle----------------
	glPushMatrix();
	glTranslatef( 0.0 , blen/2 ,0.5);
	glColor3f(0.0, 0.0, 0.0); 
	glScalef(1.2 , 0.2, 0.2);
	glutSolidCube(1.0);
	glColor3f(0.9, 0.8, 0.0); 
	glutWireCube(1.0);
	glPopMatrix();

	//------------------- Rear Mudguard ---------
	glPushMatrix();
	glTranslatef( 0.0,-blen/2,0.5 );
	glPushMatrix();
	glRotatef(-60,1,0,0);
	glColor3f(1.0,0.0,0.0);
	glScalef(0.5, blen/1.8 , 0.1);
	glutSolidCube(1.0);
	glPopMatrix();
	glTranslatef( 0.0, -blen*cos(DEG2RAD(60))/1.8 , blen*sin(DEG2RAD(60))/3.6); 
	glColor3f(1.0,0.0,0.0);
	glScalef(0.5, blen/2.5 , 0.1);
	glutSolidCube(1.0);
	glPopMatrix();
	

	//------------------- Front Mudguard ---------
	glPushMatrix();
	glTranslatef( 0.0,blen/2+0.1,0.4 );
	glRotatef(55,1,0,0);
	glColor3f(1.0,0.0,0.0);
	glScalef(0.5, blen/4 , 0.1);
	glutSolidCube(1.0);
	glPopMatrix();

	//----------------- Silencer r --------------------
	glPushMatrix();
	glColor3f(0.3,0.3,0.3);
	glTranslatef(0.3,-1.5,0.0);
	glRotatef(-90.0, 1.0, 0.0, 0.0); // rotate to point along -y
	glutSolidCone(0.2, 2.0, 10, 2); // draw cone
	glPopMatrix();
	
	//----------------- Silencer l--------------------
	glPushMatrix();
	glColor3f(0.3,0.3,0.3);
	glTranslatef(-0.3,-1.5,0.0);
	glRotatef(-90.0, 1.0, 0.0, 0.0); // rotate to point along -y
	glutSolidCone(0.2, 2.0, 10, 2); // draw cone
	glPopMatrix();
	

	//-------------------Front wheel -------------
	glPushMatrix();
	glTranslatef(0.0, blen/2 + bwheelrad + bwheelthick,0.0);
	glRotatef(90,0,1,0);
	glColor3f(0.0, 0.0, 0.0);
	glutSolidTorus( bwheelthick, bwheelrad, 25, 30);
	glColor3f(0.0, 0.7, 1.0);
	glutWireTorus( bwheelthick, bwheelrad, 15, 60);
	glPopMatrix();

	//------------------ Rear wheel----------------
	glPushMatrix();
	glTranslatef(0.0,-( blen/2 + bwheelrad + bwheelthick ),0.0);
	glRotatef(90,0,1,0);
	glColor3f(0.0, 0.0, 0.0);
	glutSolidTorus( bwheelthick, bwheelrad , 25 , 30);
	glColor3f(0.0, 0.7, 1.0);
	glutWireTorus( bwheelthick, bwheelrad, 15, 60);
	glPopMatrix();

}

//----------------------------------------------------------------------
// Update with each idle event
//
// This incrementally moves the camera and requests that the scene be
// redrawn.
//----------------------------------------------------------------------
void update(void) 
{
	if (deltaMove) { // update camera position
		x += deltaMove * lx * 0.1;
		y += deltaMove * ly * 0.1;
	}
	if (moving){
		bposy += direction_move;
	}
	moving = 0;
	glutPostRedisplay(); // redisplay everything
}

//----------------------------------------------------------------------
// Draw the entire scene
//
// We first update the camera location based on its distance from the
// origin and its direction.
//----------------------------------------------------------------------
void renderScene(void) 
{
	int i, j;

	// Clear color and depth buffers
	glClearColor(0.0, 0.7, 1.0, 1.0); // sky color is light blue
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Reset transformations
	glLoadIdentity();

	// Set the camera centered at (x,y,1) and looking along directional
	// vector (lx, ly, 0), with the z-axis pointing up
	gluLookAt(
			x,      y,      1.0,
			x + lx, y + ly, 1.0,
			0.0,    0.0,    1.0);


	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0.0, win_width, 0.0, win_height);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();



	glMatrixMode(GL_PROJECTION); //swapped this with...
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW); //...this
	glPopMatrix();



	// Draw ground - 200x200 square colored green
	glColor3f(0.0, 0.7, 0.0);
	glBegin(GL_QUADS);
	glVertex3f(-100.0, -100.0, 0.0);
	glVertex3f(-100.0,  100.0, 0.0);
	glVertex3f( 100.0,  100.0, 0.0);
	glVertex3f( 100.0, -100.0, 0.0);
	glEnd();

	glPushMatrix();
	//glTranslatef( bposx , bposy , bposz );
	//glRotatef( 90 , 0 , 0 , 1 );
	glRotatef( 90 , 0 , 0 , 1 );
	glTranslatef( bposx , bposy , bposz );
	drawBike();
	glPopMatrix();

	// Draw 36 snow men
	for(i = -3; i < 3; i++)
		for(j = -3; j < 3; j++) {
			if(i==0)	continue;
			glPushMatrix();
			glTranslatef(i*7.5, j*7.5, 0);
			drawSnowman();
			glPopMatrix();
		}

	glutSwapBuffers(); // Make it all visible
} 

//----------------------------------------------------------------------
// User-input callbacks
//
// processNormalKeys: ESC, q, and Q cause program to exit
// pressSpecialKey: Up arrow = forward motion, down arrow = backwards
// releaseSpecialKey: Set incremental motion to zero
//----------------------------------------------------------------------
void processNormalKeys(unsigned char key, int xx, int yy)
{
	if (key == ESC || key == 'q' || key == 'Q') exit(0);
	if(key=='w'){
		moving = 1;
		direction_move = 1;
	}
	else if(key=='s'){
		moving = 1;
		direction_move = -1;
	}
	else
		moving = 0;
} 

void pressSpecialKey(int key, int xx, int yy)
{
	switch (key) {
		case GLUT_KEY_UP : deltaMove = 1.0; break;
		case GLUT_KEY_DOWN : deltaMove = -1.0; break;
	}
} 

void releaseSpecialKey(int key, int x, int y) 
{
	switch (key) {
		case GLUT_KEY_UP : deltaMove = 0.0; break;
		case GLUT_KEY_DOWN : deltaMove = 0.0; break;
	}
} 

//----------------------------------------------------------------------
// Process mouse drag events
// 
// This is called when dragging motion occurs. The variable
// angle stores the camera angle at the instance when dragging
// started, and deltaAngle is a additional angle based on the
// mouse movement since dragging started.
//----------------------------------------------------------------------
void mouseMove(int x, int y) 
{ 	
	if (isDragging) { // only when dragging
		// update the change in angle
		deltaAngle = (x - xDragStart) * 0.005;

		// camera's direction is set to angle + deltaAngle
		lx = -sin(angle + deltaAngle);
		//ly = cos(angle + deltaAngle);
	}
}

void mouseButton(int button, int state, int x, int y) 
{
	if (button == GLUT_LEFT_BUTTON) {
		if (state == GLUT_DOWN) { // left mouse button pressed
			isDragging = 1; // start dragging
			xDragStart = x; // save x where button first pressed
		}
		else  { /* (state = GLUT_UP) */
			angle += deltaAngle; // update camera turning angle
			isDragging = 0; // no longer dragging
		}
	}
}

//----------------------------------------------------------------------
// Main program  - standard GLUT initializations and callbacks
//----------------------------------------------------------------------
int main(int argc, char **argv) 
{
	/*printf("\n\
			-----------------------------------------------------------------------\n\
			OpenGL Sample Program:\n\
			- Drag mouse left-right to rotate camera\n\
			- Hold up-arrow/down-arrow to move camera forward/backward\n\
			- Press 'w' and 's' to move bike forward and backward\n\
			- q or ESC to quit\n\
			-----------------------------------------------------------------------\n");*/

	// general initializations
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 400);
	glutCreateWindow("OpenGL/GLUT Sampe Program");

	// register callbacks
	glutReshapeFunc(changeSize); // window reshape callback
	glutDisplayFunc(renderScene); // (re)display callback
	glutIdleFunc(update); // incremental update 
	//glutIgnoreKeyRepeat(1); // ignore key repeat when holding key down
	glutMouseFunc(mouseButton); // process mouse button push/release
	glutMotionFunc(mouseMove); // process mouse dragging motion
	glutKeyboardFunc(processNormalKeys); // process standard key clicks
	glutSpecialFunc(pressSpecialKey); // process special key pressed
	// Warning: Nonstandard function! Delete if desired.
	glutSpecialUpFunc(releaseSpecialKey); // process special key release

	// OpenGL init
	glEnable(GL_DEPTH_TEST);

	// enter GLUT event processing cycle
	glutMainLoop();

	return 0; // this is just to keep the compiler happy
}
