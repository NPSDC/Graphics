#include <iostream>
#include <cmath>
#include <GL/glut.h>
using namespace std;

#define PI 3.141592653589
#define DEG2RAD(deg) (deg * PI / 180)

// Function Declarations
void drawScene();
void update(int value);
void drawBox(float len);
void drawBall(float rad);
void drawTriangle();
void initRendering();
void handleResize(int w, int h);
void handleKeypress1(unsigned char key, int x, int y);
void handleKeypress2(int key, int x, int y);
void handleMouseclick(int button, int state, int x, int y);

void drawMiddleCircles(){
float rad = 2.0f, r = 0.0f, g = 0.0f, b = 0.0f; //r=1.0f;g=0.0f;b=0.0f;
float x = 0.0f, y = 0.0f, z = 0.0f;
glLineWidth(1.0f);
glColor3f(r, g, b);
glBegin(GL_LINE_LOOP);
for (int i = 0; i<360; i++) {
glVertex2f(rad * cos(DEG2RAD(i)), rad * sin(DEG2RAD(i)));
}
glEnd();
glLineWidth(5.0f);
rad = 2.1f;
glColor3f(r, g, b);
glBegin(GL_LINE_LOOP);
for (int i = 0; i<360; i++) {
glVertex2f(rad * cos(DEG2RAD(i)), rad * sin(DEG2RAD(i)));
}
glEnd();
glLineWidth(1.0f);
}
void drawCenterCircles(){
float rad = 0.35f, r = 1.0f, g = 0.0f, b = 0.0f;
float x = 0.0f, y = 0.0f, z = 0.0f;
glColor3f(r, g, b);
glBegin(GL_LINE_LOOP);
for (int i = 0; i<360; i++) {
glVertex2f(rad * cos(DEG2RAD(i)), rad * sin(DEG2RAD(i)));
}
glEnd();
//drawFilledBall(rad,r,g,b,x,y,z);
}
void drawCenterDesigns(){
int i;
float x1; float x2; float x3;
float y1; float y2; float y3;
float r = 1.0f;
float g = 0.0f;
float b = 0.0f;
// white triangles
r = 1.0f; g = 0.0f; b = 0.0f;
x1 = 0.17863f; x2 = 0.8f; x3 = 0.19;
y1 = 0.0f; y2 = 0.0; y3 = 0.15;
glPushMatrix();
for (i = 0; i<4; i++){
drawTriangle(x1, y1, x2, y2, x3, y3, r, g, b);
glRotatef(90.0, 0.0, 0.0, 1.0);
}
glPopMatrix();
r = 1.0f; g = 1.0f; b = 1.0f;
x1 = 0.17863f; x2 = 0.8f; x3 = 0.19;
y1 = 0.0f; y2 = 0.0; y3 = -0.15;
glPushMatrix();
for (i = 0; i<4; i++){
drawTriangle(x1, y1, x2, y2, x3, y3, r, g, b);
glRotatef(90.0, 0.0, 0.0, 1.0);
}
glPopMatrix();
r = 0.0f; g = 0.0f; b = 0.0f;
x1 = 0.10606f; x2 = 0.56568f; x3 = 0.0;
y1 = 0.10606f; y2 = 0.56568f; y3 = 0.17863;
glPushMatrix();
for (i = 0; i<4; i++){
drawTriangle(x1, y1, x2, y2, x3, y3, r, g, b);
glRotatef(90.0, 0.0, 0.0, 1.0);
}
glPopMatrix();
r = 1.0f; g = 1.0f; b = 1.0f;
x1 = 0.10606f; x2 = 0.56568f; x3 = 0.10606f;
y1 = 0.10606f; y2 = 0.56568f; y3 = -0.10606f;
glPushMatrix();
for (i = 0; i<4; i++){
drawTriangle(x1, y1, x2, y2, x3, y3, r, g, b);
glRotatef(90.0, 0.0, 0.0, 1.0);
}
glPopMatrix();
}
void drawTriangle(float x1, float y1, float x2, float y2, float x3, float y3, float r, float g, float b) {
glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
glBegin(GL_TRIANGLES);
glColor3f(r, g, b);
glVertex3f(x1, y1, 0.0f);
glColor3f(r, g, b);
glVertex3f(x2, y2, 0.0f);
glColor3f(r, g, b);
glVertex3f(x3, y3, 0.0f);
glEnd();
}

// Global Variables
float ball_x = 1.0f;
float ball_y = 0.0f;
float ball_velx = 0.08f;
float ball_vely = 0.02f;
float ball2_x = 0.5f;
float ball2_y = 0.5f;
float ball2_velx = 0.01f;
float ball2_vely = 0.02f;
float ball_rad = 0.2f;
float box_len = 4.0f;
float tri_x = 0.0f;
float tri_y = 0.0f;
float theta = 0.0f; 


int main(int argc, char **argv) {

    // Initialize GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    int w = glutGet(GLUT_SCREEN_WIDTH);
    int h = glutGet(GLUT_SCREEN_HEIGHT);
    int windowWidth = w * 2 / 3;
    int windowHeight = h * 2 / 3;

    glutInitWindowSize(windowWidth, windowHeight);
    glutInitWindowPosition((w - windowWidth) / 2, (h - windowHeight) / 2);

    glutCreateWindow("CSE251_sampleCode");  // Setup the window
    initRendering();

    // Register callbacks
    glutDisplayFunc(drawScene);
    glutIdleFunc(drawScene);
    glutKeyboardFunc(handleKeypress1);
    glutSpecialFunc(handleKeypress2);
    glutMouseFunc(handleMouseclick);
    glutReshapeFunc(handleResize);
    glutTimerFunc(10, update, 0);

    glutMainLoop();
    return 0;
}

// Function to draw objects on the screen
void drawScene() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();

    // Draw Box
    glTranslatef(0.0f, 0.0f, -10.0f);
    glColor3f(1.0f, 0.0f, 0.0f);

    drawCenterCircles();
    drawMiddleCircles();
    drawCenterDesigns();
    drawBox(box_len);
    //glPopMatrix();
    // Draw Ball
    glPushMatrix();
    glTranslatef(ball_x, ball_y, 0.0f);
    glColor3f(0.0f, 1.0f, 0.0f);
    drawBall(ball_rad);
    glPopMatrix();
    
    // Draw Ball2
    glPushMatrix();
    glTranslatef(ball2_x, ball2_y, 0.0f);
    glColor3f(0.0f, 1.0f, 0.0f);
    drawBall(ball_rad);
    glPopMatrix();


    // Draw Triangle
    glPushMatrix();
    glTranslatef(tri_x, tri_y, 0.0f);
    glRotatef(theta, 0.0f, 0.0f, 1.0f);
    glScalef(0.5f, 0.5f, 0.5f);
    drawTriangle();
    glPopMatrix();

    //glPopMatrix();
    glutSwapBuffers();
}

// Function to handle all calculations in the scene
// updated evry 10 milliseconds
void update(int value) {
   float dist; 
    // Handle ball collisions with box
    if(ball_x + ball_rad > box_len/2 || ball_x - ball_rad < -box_len/2)
        ball_velx *= -1;
    if(ball_y + ball_rad > box_len/2 || ball_y - ball_rad < -box_len/2)
        ball_vely *= -1;
    
    if(ball2_x + ball_rad > box_len/2 || ball2_x - ball_rad < -box_len/2)
        ball2_velx *= -1;
    if(ball2_y + ball_rad > box_len/2 || ball2_y - ball_rad < -box_len/2)
        ball2_vely *= -1;
    
    dist=sqrt(pow((ball_x-ball2_x),2)+pow((ball_y-ball2_y),2));
    if(dist<=2*ball_rad)
    {
	    ball_velx*=-1;
	    ball_vely*=-1;
	    ball2_velx*=-1;
	    ball2_vely*=-1;
    }
    // Update position of ball
    ball_x += ball_velx;
    ball_y += ball_vely;
    ball2_x += ball2_velx;
    ball2_y += ball2_vely;

    glutTimerFunc(10, update, 0);
}

void drawBox(float len) {
   
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glBegin(GL_QUADS);
    glVertex2f(-len / 2, -len / 2);
    glVertex2f(len / 2, -len / 2);
    glVertex2f(len / 2, len / 2);
    glVertex2f(-len / 2, len / 2);
    glEnd();
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void drawBall(float rad) {
    
   glBegin(GL_TRIANGLE_FAN);
   for(int i=0 ; i<360 ; i++) {
       glVertex2f(rad * cos(DEG2RAD(i)), rad * sin(DEG2RAD(i)));
   }
   glEnd();
}

void drawTriangle() {

    glBegin(GL_TRIANGLES);
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 1.0f, 0.0f);
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, 0.0f);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, 0.0f);
    glEnd();
}

// Initializing some openGL 3D rendering options
void initRendering() {

    glEnable(GL_DEPTH_TEST);        // Enable objects to be drawn ahead/behind one another
    glEnable(GL_COLOR_MATERIAL);    // Enable coloring
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);   // Setting a background color
}

// Function called when the window is resized
void handleResize(int w, int h) {

    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (float)w / (float)h, 0.1f, 200.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void handleKeypress1(unsigned char key, int x, int y) {

    if (key == 27) {
        exit(0);     // escape key is pressed
    }
}

void handleKeypress2(int key, int x, int y) {

    if (key == GLUT_KEY_LEFT)
        tri_x -= 0.1;
    if (key == GLUT_KEY_RIGHT)
        tri_x += 0.1;
    if (key == GLUT_KEY_UP)
        tri_y += 0.1;
    if (key == GLUT_KEY_DOWN)
        tri_y -= 0.1;
}

void handleMouseclick(int button, int state, int x, int y) {

    if (state == GLUT_DOWN)
    {
        if (button == GLUT_LEFT_BUTTON)
            theta += 15;
        else if (button == GLUT_RIGHT_BUTTON)
            theta -= 15;
    }
}
