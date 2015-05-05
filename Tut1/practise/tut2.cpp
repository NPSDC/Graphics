#include <iostream>
#include <stdlib.h>
#include <GL/glut.h>
using namespace std;
	
void handleKeypress(unsigned char key,int x,int y)
{
	switch(key)
	{
		case 27:
			exit(0);
	}
}
void initRendering()
{
		glEnable(GL_DEPTH_TEST);
}

void handleResize(int w, int h) {
    //Tell OpenGL how to convert from coordinates to pixel values
    glViewport(0, 0, w, h);
    
    glMatrixMode(GL_PROJECTION); //Switch to setting the camera perspective
    
    //Set the camera perspective
    glLoadIdentity(); //Reset the camera
    gluPerspective(45.0,                  //The camera angle
                   (double)w / (double)h, //The width-to-height ratio
                   1.0,                   //The near z clipping coordinate
                   200.0);                //The far z clipping coordinate
}
float _angle=30.0f;
float _angle2=30.0f;
int _red=1;
int _green=2;
int _blue=0;
void drawScene() 
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -5.0f);
      //glRotatef(_angle2,0.1f,0.0f,0.0f);
    //glScalef(0.5f,0.5f,0.5f);
    
    glPushMatrix(); //Save the transformations performed thus far
    glTranslatef(0.0f, -1.0f, 0.0f); //Move to the center of the trapezoid
     glBegin(GL_QUADS);
    glColor3f(_red, _green, _blue);
    //Trapezoid
    glVertex3f(-0.7f, -0.5f, 0.0f);
    glVertex3f(0.7f, -0.5f, 0.0f);
    glVertex3f(0.4f, 0.5f, 0.0f);
    glVertex3f(-0.4f, 0.5f, 0.0f);
    
    glEnd();    
    glPopMatrix(); 

    glPushMatrix(); //Save the current state of transformations
    glTranslatef(1.0f, 1.0f, 0.0f); //Move to the center of the pentagon
    glRotatef(_angle, 0.0f, 1.0f, 0.0f); //Rotate about the y-axis
    glScalef(0.7f, 0.7f, 0.7f); //Scale by 0.7 in the x, y, and z directions
      glBegin(GL_TRIANGLES);
    
    //Pentagon
       glColor3f(0.0f, 0.75f, 0.0f);
    glVertex3f(-0.5f, -0.5f, 0.0f);
    glVertex3f(0.5f, -0.5f, 0.0f);
    glVertex3f(-0.5f, 0.0f, 0.0f);
    
    glVertex3f(-0.5f, 0.0f, 0.0f);
    glVertex3f(0.5f, -0.5f, 0.0f);
    glVertex3f(0.5f, 0.0f, 0.0f);
    
    glVertex3f(-0.5f, 0.0f, 0.0f);
    glVertex3f(0.5f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.5f, 0.0f);
    glEnd();
    glPopMatrix();
    
     glColor3f(0.0f, 0.65f, 0.65f);
    glBegin(GL_TRIANGLES);
    
    //Triangle
    glVertex3f(3.5f, -0.5f, 0.0f);
    glVertex3f(0.1f, 0.4f, 0.0f);
    glVertex3f(2.5f, -0.5f, 0.0f);
    
    glEnd();


    glutSwapBuffers();
}
/*void updaterr(int value)
{
  _angle+=2.0f;
  _angle2+=5.0f;
  if(_angle > 360)
  {
    _angle-=360;
  }
  if(_angle2>360)
    _angle2-=360;
  glutPostRedisplay();
  glutTimerFunc(25,updaterr,0);
}*/
void updatecolor(int value)
{
  _red+=1;
  _green+=1;
  _blue+=1;
  _red%=3;
  _green%=3;
  _blue%=3;
  _red/=2;
  _green/=2;
  _blue/=2;
  glutPostRedisplay();
  glutTimerFunc(1000,updatecolor,0);
}
int main(int argc, char** argv) {
  
    //Initialize GLUT //Initialize GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(400, 400); //Set the window size
    
    //Create the window
    glutCreateWindow("Basic Shapes - videotutorialsrock.com");
    initRendering(); //Initialize rendering
  //  glutTimerFunc(25,updaterr,0);
       glutTimerFunc(1000,updatecolor,0);   
     glutDisplayFunc(drawScene);
    glutKeyboardFunc(handleKeypress);
    glutReshapeFunc(handleResize);
 
     glutMainLoop(); //Start the main loop.  glutMainLoop doesn't return.
    return 0; //This line is never reached
  }