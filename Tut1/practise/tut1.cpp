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
void drawScene() 
{
	 glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	 glMatrixMode(GL_MODELVIEW);
	 glLoadIdentity();
	 glBegin(GL_QUADS);//Begin Quadilateral Coordinates
	 glVertex3f(-0.7f, -1.5f, -5.0f);
    glVertex3f(0.7f, -1.5f, -5.0f);
    glVertex3f(0.4f, -0.5f, -5.0f);
    glVertex3f(-0.4f, -0.5f, -5.0f);
    
    glEnd(); //end those
    glBegin(GL_TRIANGLES); //Begin triangle coordinates
    
    //Pentagon
    glVertex3f(0.5f, 0.5f, -7.0f);
    glVertex3f(1.5f, 0.5f, -7.0f);
    glVertex3f(0.5f, 1.0f, -7.0f);
    
    glVertex3f(0.5f, 1.0f, -7.0f);
    glVertex3f(1.5f, 1.0f, -7.0f);
    glVertex3f(1.5f, 0.5f, -7.0f);
    
    
    	glVertex3f(0.5f, 1.0f, -7.0f);
    glVertex3f(1.5f, 1.0f, -7.0f);
    glVertex3f(1.0f, 1.5f, -7.0f);	
    glEnd();

    glBegin(GL_TRIANGLES);
    	glVertex3f(0.7f,0.3f,-5.0f);
    	glVertex3f(0.5f,-0.1f,-5.0f);
    	glVertex3f(1.5f,-0.1f,-5.0f);

    	glVertex3f(1.5f,-0.1f,-5.0f);
    	glVertex3f(1.3f,0.3f,-5.0f);
    	glVertex3f(0.7f,0.3f,-5.0f);
    glEnd();

     glutSwapBuffers();
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
    glutMainLoop(); //Start the main loop.  glutMainLoop doesn't return.
    return 0; //This line is never reached
	}