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
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_NORMALIZE);
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
float _angle=-70.0f;
void drawScene() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  
  glTranslatef(0.0f, 0.0f, -8.0f);

  //Add ambient light
  GLfloat ambientColor[] = {0.2f, 0.2f, 0.2f, 1.0f}; //Color (0.2, 0.2, 0.2)
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);

   //Add positioned light
   /* GLfloat lightColor0[] = {0.5f, 0.5f, 0.5f, 1.0f}; //Color (0.5, 0.5, 0.5)
    GLfloat lightPos0[] = {4.0f, 0.0f, 8.0f, 1.0f}; //Positioned at (4, 0, 8)
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);*/
    //Add directed light
    GLfloat lightColor1[] = {0.5f, 0.2f, 0.2f, 1.0f}; //Color (0.5, 0.2, 0.2)
    //Coming from the direction (-1, 0.5, 0.5)
    GLfloat lightPos1[] = {-1.0f, 0.5f, 0.5f, 0.0f};
    glLightfv(GL_LIGHT1, GL_DIFFUSE, lightColor1);
    glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);

    glRotatef(_angle, 0.0f, 1.0f, 0.0f);
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
     //Front
    glNormal3f(0.0f, 0.0f, 1.0f);
    glVertex3f(-1.5f, -1.0f, 1.5f);
    glVertex3f(1.5f, -1.0f, 1.5f);
    glVertex3f(1.5f, 1.0f, 1.5f);
    glVertex3f(-1.5f, 1.0f, 1.5f);

    //Right
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(1.5f, -1.0f, -1.5f);
    glVertex3f(1.5f, 1.0f, -1.5f);
    glVertex3f(1.5f, 1.0f, 1.5f);
    glVertex3f(1.5f, -1.0f, 1.5f);
    
    //Back
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(-1.5f, -1.0f, -1.5f);
    glVertex3f(-1.5f, 1.0f, -1.5f);
    glVertex3f(1.5f, 1.0f, -1.5f);
    glVertex3f(1.5f, -1.0f, -1.5f);
    
    //Left
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(-1.5f, -1.0f, -1.5f);
    glVertex3f(-1.5f, -1.0f, 1.5f);
    glVertex3f(-1.5f, 1.0f, 1.5f);
    glVertex3f(-1.5f, 1.0f, -1.5f);
    
    glEnd();

     glutSwapBuffers();
   }
   void update(int value) {
  _angle += 1.5f;
  if (_angle > 360) {
    _angle -= 360;
  }
  
  glutPostRedisplay();
  glutTimerFunc(25, update, 0);
}
   int main(int argc, char** argv) {
  
    //Initialize GLUT //Initialize GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(400, 400); //Set the window size
    
    //Create the window
    glutCreateWindow("Basic Shapes - videotutorialsrock.com");
    initRendering(); //Initialize rendering
    glutDisplayFunc(drawScene);
    glutKeyboardFunc(handleKeypress);
    glutReshapeFunc(handleResize);
    glutTimerFunc(25, update, 0);  
     glutMainLoop(); //Start the main loop.  glutMainLoop doesn't return.
    return 0; //This line is never reached
  }