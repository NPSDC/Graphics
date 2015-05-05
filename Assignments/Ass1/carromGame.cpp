#include <iostream>
#include <stdio.h>
#include <cmath>
#include <GL/glut.h>
#include <sys/time.h>
using namespace std;

#define PI 3.141592653589
#define DEG2RAD(deg) (deg * PI / 180)

class Shape
{
	protected:
		float color[3];
	public:
	void setColor(float r,float g,float b) //sets the color matrix to that color and colors the shape with that color
	{
		color[0]=r;
		color[1]=g;
		color[2]=b;
		glColor3f(r,g,b);
	}
	float * getColor()
	{
		return color;
	}
};
class Box:public Shape
{
	private:
		float length;
		float height;
		float maxheight;

	public:
		Box(float len=5.0f,float hei=5.0f,float max=5.0f)
		{
			length = len;
			height = hei;
			maxheight = max;
		}
		float getLength()
		{
			return length;
		}
		void setHeight(float h)
		{
			height = h;
		}
		float getHeight()
		{
			return height;
		}
		float getMaxHeight()
		{
			return maxheight;
		}
		void setMaxHeight(float max)
		{
			maxheight = max;
		}
		void drawBox() //draws the box and the parameters specify the color inside of box will have
		{   
		    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		    glBegin(GL_QUADS);
		    glVertex2f(-length / 2, -length / 2);
		    glVertex2f(length / 2, -length / 2);
		    glVertex2f(length / 2, length / 2);
		    glVertex2f(-length / 2, length / 2);
		    glEnd();
		   // glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
		void drawBox(float x,float y)
		{
			glPushMatrix();
			glTranslatef(x,y,0.0f);
			glBegin(GL_QUADS);			
		    glVertex2f(0.0f, 0.0f);
		    glVertex2f(0.0f , height );
		    glVertex2f(length , height );
		    glVertex2f(length , 0.0f);
			glEnd();
			glPopMatrix();
		}
};
class Line:public Shape
{
	private:
		float length;
		float width;
		float breadth;

	public:

		Line(float len=10.0f,float width=1.0f,float b = 5.0f)
		{
			length = len;
			width = 1.0f;
			breadth = b;
		}
		void set_width(float wid)
		{
			width=wid;
		}
		
		void drawRect()
		{
			glLineWidth(width);
			glBegin(GL_LINE_STRIP);			
		    glVertex2f(-length / 2, -breadth / 2);
		    glVertex2f(length / 2, -breadth / 2);
		    glVertex2f(length / 2, breadth / 2);
		    glVertex2f(-length / 2, breadth / 2);
		    glVertex2f(-length / 2, -breadth / 2);
		    glEnd();
		}

		void drawLine()
		{
			glLineWidth(width);
			glBegin(GL_LINE_STRIP);			
		    glVertex2f(-length / 2 +0.3f, -length / 2);
		    glVertex2f(length / 2 -0.3f, -length / 2);
		    glEnd();
		}
		void drawLine(float theta,float x,float y)
		{
			glPushMatrix();
			glTranslatef(x,y,0.0f);
			glRotatef(theta,0.0f,0.0f,-1.0f);
			glColor3f(color[0],color[1],color[2]);
			glBegin(GL_LINE_STRIP);
			glVertex2f(0.0f,0.0f);
			glVertex2f(0.0f,0.30f);
			glEnd();
			glBegin(GL_TRIANGLES);
			glVertex2f(0.0f,0.32f);
			glVertex2f(0.03f,0.28f);
			glVertex2f(-0.04f,0.28f);
			glEnd();
			glPopMatrix();
		}
};

class Ball:public Shape
{
	private:
		float radius,x,y,angle,velx,vely,mass;
		int state;
		char type;
	public:
		Ball(float rad=1,float x1=0,float y1=0,float ang=360,float m=1,int state=0,char type='C')
		{
			radius=rad;
			x=x1;
			y=y1;
			angle=ang;
			velx=0;
			vely=0;
			state=0;
			mass=m;
		}
		void setType(char t)
		{
			type=t;
		}
		char getType()
		{
			return type;
		}
		void setState(int st)
		{
			state=st;
		}
		int getState()
		{
			return state;
		}
		void setRadius(float r)
		{
			radius = r;
		}
		float getRadius()
		{
			return radius;
		}
		float getX()
		{
			return x;
		}
		float getY()
		{
			return y;
		}
		float getVx()
		{
			return velx;
		}
		float getVy()
		{
			return vely;
		}
		float getMass()
		{
			return mass;
		}
		void setMass(float ma)
		{
			mass=ma;
		}
		void setX(float x1)
		{
			x=x1;
		}
		void setY(float y1)
		{
			y=y1;
		}
		void setvx(float vx)
		{
			velx=vx;
		}
		void setvy(float vy)
		{
			vely=vy;
		}
		void setstate(int st)
		{
			state=st;
		}
		void drawBall_line(float width)
		{	
			glPushMatrix();
			glTranslatef(x,y,0.0f);
			glPointSize(width);
			glBegin(GL_POINTS);//draws the unfilled circle
			
			for(int i=0 ; i<angle ; i++) 
		       glVertex2f(radius * cos(i*PI/180), radius * sin(i*PI/180));

			glEnd();
			glPopMatrix();		   
		}

		void drawBall_fill()//draws the filled circle
		{
			glPushMatrix();
			glTranslatef(x,y,0.0f);
			glBegin(GL_TRIANGLE_FAN);
			glColor3f(color[0],color[1],color[2]);
		   for(int i=0 ; i<360 ; i++) 
		   {
		   	     glVertex2f(radius * cos(DEG2RAD(i)), radius * sin(DEG2RAD(i)));
		   }
		   glEnd();
		   glPopMatrix();
		}
};

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
void checkWall(Ball &obj,Box &box);
void checkCorner(Ball &obj,Ball corners[]);
void checkCollision(Ball &obj1,Ball &obj2);
void friction(Ball &obj);
void setStriker();
void renderBitmapString(float x,float y,void *font,const char *string);
void displayScore(float x,float y,void *front,char *scoreDisp);
void drag(int x,int y);
void left();
void right();
void UpAndDown(int movement,float maxV,float minV);

float _angle = 0;
float velStriker = 0;
float ang = 0;
int score = 30;
int old_x;
int old_y;
char scoreDisp[5];
int STATE_LEFT = 0;
int STATE_MIDDLE = 0;
int STATE_RIGHT = 0;
int count_lu = 0;
int count_lb = 0;
int count_ru = 0;
int count_rb = 0;
double ti;
char *sc = "Score";

Box box1(6.5f);
Box box2(5.5f);
Box box3(0.5f,0.0f);

Line line2(5.5f,2.0f,5.5f);
Line line1(6.5f,2.0f,6.5f);
Line line3(4.0f);
Line line4;
Line line5(0.5,2,5);

Ball ball1(0.65f),ball2(0.125f,-1.64f,-1.875f,360.0f),ball3(0.2f,0.0f,0.0f,270);
Ball Striker(0.18f,0.0f,-1.875f);
Ball Coin[9];
Ball corners[4];




int main(int argc, char **argv)
{
	glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    int w = glutGet(GLUT_SCREEN_WIDTH);
    int h = glutGet(GLUT_SCREEN_HEIGHT);
    int windowWidth = w * 3 / 4;
    int windowHeight = h * 3 / 4;
    line4.setColor(0.0f,0.0f,0.0f);
    Striker.setMass(2);
    Striker.setType('S');
    float theta=0.0f;

    scoreDisp[3] = '\0';
    //printf("%d %d\n",windowWidth,windowHeight);
    glutInitWindowSize(windowWidth, windowHeight);
    glutInitWindowPosition((w - windowWidth) / 2, (h - windowHeight) / 2);
    glutCreateWindow("Carrom");  // Setup the window
    initRendering();

    struct timeval tim;  
	    gettimeofday(&tim, NULL);  
    	ti=tim.tv_sec;

    for(int i=0;i<8;i++)//Initialsing white coins
    {
    	Coin[i]=Ball(0.12f,0.5*cos(theta*PI/180),0.50*sin(theta*PI/180));
    	if(i & 1)
    	{
    		Coin[i].setColor((1.0f/255)*227,(1.0f/255)*207,(1.0f/255)*87);
    		Coin[i].setType('W');
    	}
    	else
    	{
    		Coin[i].setColor((1.0f/255)*0,(1.0f/255)*0,(1.0f/255)*0);
    		Coin[i].setType('B');
    	}
    	theta+=45;
    }
    Coin[8] = Ball(0.12f,0.0f,0.0f);
    Coin[8].setColor(1.0f,0.0f,0.0f);
    Coin[8].setType('R');

    // Register callbacks
    glutDisplayFunc(drawScene);
    glutIdleFunc(drawScene);
    glutKeyboardFunc(handleKeypress1);
    glutSpecialFunc(handleKeypress2);
    glutMouseFunc(handleMouseclick);
    glutMotionFunc(drag);
    glutReshapeFunc(handleResize);
    

    glutTimerFunc(10, update, 0);

    glutMainLoop();
    return 0;
}

void displayScore(float x,float y,void *font,char *scoreDisp)
{
	//This function displays the score by transforming the number into character array
	int tempscore = score;
	int i=3;

	if(tempscore < 0)
		tempscore *= -1;		
	
	while(tempscore > 0)
	{
		scoreDisp[i] = tempscore%10 + 48;
		tempscore /= 10;
		i--;
	}
	if(tempscore == 0 )
	{
		for(int j=i;j>=0;j--)	
			scoreDisp[j] = ' ';
	}
	if(scoreDisp[3] == ' ')
		scoreDisp[i] = '0';

	if(score < 0)
	{
		if(scoreDisp[2] == ' ')
			scoreDisp[2] = '-';			
		else if(scoreDisp[1] == ' ')
			scoreDisp[1] = '-';
		else
			scoreDisp[0] = '-';		
	}

    glColor3f(1.0f,0.0f,1.0f);
    glRasterPos2f(x,y);

    for(int i=0;i<4;i++)
    {	
    	if(scoreDisp[i] == ' ')
    		continue;
    	glutBitmapCharacter(font , scoreDisp[i]);
	}
	
}
void drawScene()
{
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity(); 	
   
    glPushMatrix();


  	glTranslatef(0.0f,0.0f,-8.0f);
  		glColor3f((1.0f/255)*255,(1.0f/255)*215,(1.0f/255)*0);
  	glRasterPos2f(-4.1f,-1.7f);
	  
  	for(int i=0;i<5;i++)
  	{	
  		
  		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,sc[i]);
  	}
    displayScore(-4.0f,-2.0f,GLUT_BITMAP_TIMES_ROMAN_24,scoreDisp);
    
    float x=1.0,y=1.0;
    int k=0;

    for(int i=0;i<2;i++)//Initialising corners/pockets
    {
    	for(int j=0;j<2;j++)
    	{
    		corners[k]=Ball(0.2f,-2.62*x,-2.62*y);
    		corners[k].setColor((1.0f/255)*205,(1.0f/255)*205,(1.0f/255)*201);
    		k++;
    		y*=-1.0;
    	}
    	x*=-1.0;
    }
    
    

    box1.setColor((1.0f/255)*94,(1.0f/255)*38,(1.0f/255)*18);
    box1.drawBox();
    box2.setColor((1.0f/255)*255,(1.0f/255)*245,(1.0f/255)*230);
    box2.drawBox();

    if(box3.getHeight()<=1.5f)
    	box3.setColor((1.0f/255)*0,(1.0f/255)*139,(1.0f/255));

    else if(box3.getHeight()>=1.5f && box3.getHeight()<=3.9f)
    	box3.setColor((1.0f/255)*0,(1.0f/255)*0,(1.0f/255)*205);

    else
    	box3.setColor((1.0f/255)*105,(1.0f/255)*0,(1.0f/255)*0);

    box3.drawBox(4.0f,-3.28f);

    line1.setColor(0.0f,0.0f,0.0f);
    line1.drawRect();
    line1.set_width(1.5f);
    line2.setColor(0.0f,0.0f,0.0f);    
    line2.drawRect();
    line2.set_width(1.5f);
    line3.setColor((1.0f/255)*139,(1.0f/255)*69,(1.0f/255)*0);

    glPushMatrix();
    glTranslatef(4.25f,-0.78f,0.0f);
    line5.setColor(255.0f,255.0f,255.0f);
    line5.drawRect();
    glPopMatrix();

    for(int i=0;i<4;i++) //Creates two lines with two circles stacked b/w them place we hold the striker
    {
	    glPushMatrix();
	    glRotatef(_angle,0.0f,0.0f,1.0f);
		glPushMatrix();
	    ball2.setColor((1.0f/255)*205,(1.0f/255)*0,(1.0f/255)*0);
	    ball2.drawBall_fill();
	    ball2.setColor(0.0f,0.0f,0.0f);
	    ball2.drawBall_line(2.0f);
	    glTranslatef(3.27f,0.0f,0.0f);
	    ball2.setColor((1.0f/255)*205,(1.0f/255)*0,(1.0f/255)*0);
	    ball2.drawBall_fill();
	    ball2.setColor(0.0f,0.0f,0.0f);
	    ball2.drawBall_line(2.0f);
	    glPopMatrix();
	    line3.setColor(0.0f,0.0f,0.0f);
	    line3.set_width(2.0f);
	    line3.drawLine();
	    glTranslatef(0.0f,0.25f,0.0f);
	    line3.set_width(1.0f);
	    line3.drawLine();
	    glPopMatrix();
	    _angle+=90;
    }
   // _angle=45;
    ball1.setColor(0.0f,0.0f,0.0f);
    ball1.drawBall_line(1.5f);//Represents the central circle
    
    for(int i=0;i<4;i++)	//Sets the lines with the arrowed part and the 270 deg arc
    {
    	glColor3f(0.0f,0.0f,0.0f);
	    glPushMatrix();
	    glRotatef(45+_angle,0.0f,0.0f,1.0f);
	    glBegin(GL_LINE_STRIP);			
	    glVertex2f(0.0f, 1.0f);
	    glVertex2f(0.0f,3.0f);
	    glEnd();
	    glColor3f(0.0f,0.0f,0.0f);
	    glBegin(GL_TRIANGLES);
	    glVertex2f(0.0f,2.85f);
	    glVertex2f(0.05f,2.75f);
	    glVertex2f(-0.05f,2.75f);
	    glEnd();
	    glPopMatrix();
	    glPushMatrix();
	    glRotatef(_angle,0.0f,0.0f,1.0f);
	    glTranslatef(0.85f,-0.85f,0);
	    ball3.drawBall_line(1.5f);
	    glPopMatrix();
	    _angle+=90;
	}

	 for(int i=0;i<4;i++)  //Draws the pockets
	 {	
	 	corners[i].drawBall_fill();
	 	corners[i].setColor(0.0f,0.0f,0.0f);
	 	corners[i].drawBall_line(1.5);
	 }
	 	
	Striker.setColor((1.0f/255)*61,(1.0f/255)*89,(1.0f/255)*171);//Drawing the main striker
	Striker.drawBall_fill();

	for(int i=0;i<9;i++) //Fills
		Coin[i].drawBall_fill();

	if(Striker.getState() == 0)
		line4.drawLine(ang,Striker.getX(),Striker.getY());
	
    glPopMatrix();
    glutSwapBuffers();
}
void update(int value) 
{
    friction(Striker);
	for(int i=0;i<9;i++)
		friction(Coin[i]);	
	checkCorner(Striker,corners);
	for(int i=0;i<9;i++)
		checkCorner(Coin[i],corners);

	checkWall(Striker,box2);
	for(int i=0;i<9;i++)
		checkWall(Coin[i],box2);

	//for(int i=0;i<9;i++)
	//	checkCollision(Striker,Coin[i]);
	for(int i=-1;i<9;i++)
	{
		for(int j=-1;j<9;j++)
		{
			if(i!=j)
			{
				if(i == -1)
					checkCollision(Striker,Coin[j]);
				else if(j == -1)
				{
					checkCollision(Coin[i],Striker);

				}
				else
					checkCollision(Coin[i],Coin[j]);
			}
		}
		
	}

    	struct timeval tim;  
	    gettimeofday(&tim, NULL);  
    	double tf=tim.tv_sec;
		    if(tf-ti>=1)
		    {
		        ti=tim.tv_sec;
		        score--;
		    }
	
	//for(int )
	//printf("%d\n",Striker.getState());
	if(Striker.getState() == 1)
	{
		Striker.setX(Striker.getX() + Striker.getVx());
	    Striker.setY(Striker.getY() + Striker.getVy());
    }
    for(int i=0;i<9;i++)
    {
    	Coin[i].setX(Coin[i].getX() + Coin[i].getVx());
    	Coin[i].setY(Coin[i].getY() + Coin[i].getVy());
	}
    glutTimerFunc(10, update, 0);
}
void friction(Ball &obj) //Applies a constant kinetic friction
{
	
		float ug = -0.00019f;
		float vx = obj.getVx();
		float vy = obj.getVy();
		
		float v = sqrt(vx*vx + vy*vy);
		float cosTheta = vx/v;
		float sinTheta = vy/v;
		if(vx!= 0)
			vx += ug*cosTheta;			
		if(vy!= 0)
			vy += ug*sinTheta;
		if(vx*cosTheta >= 0)
			obj.setvx(vx);
		else
			obj.setvx(0);
		if(vy*sinTheta >= 0)
			obj.setvy(vy);
		else
			obj.setvy(0);
		if(vx==0 && vy==0)
		{
			if(obj.getType() == 'S' && obj.getState()==1)
			setStriker();
		}
	
	
}
void setStriker()  // Sets the striker to the striking postion depending on the free position
{	
	float r=0;
	float xDist,yDist;

	for(int i=0;i<9;i++)
	{
		if(Coin[i].getVx() != 0)
			return;
		if(Coin[i].getVy() != 0)
			return;
	}

	for(int i=0;i<9;i++)
	{
		xDist = Coin[i].getX() + 1.60f;
		yDist = Coin[i].getY() + 1.875f;
		if(xDist*xDist + yDist*yDist <= (Coin[i].getRadius() + Striker.getRadius()) * (Coin[i].getRadius() + Striker.getRadius()))
			r += 2*Striker.getRadius();
	}
	Striker.setX(-1.60f + r);
	Striker.setY(-1.875f);
	Striker.setvx(0.0f);
	Striker.setvy(0.0f);
	Striker.setState(0);
	velStriker = 0;
	ang = 0.0f;				
	box3.setHeight(0);
}
void checkCorner(Ball &obj,Ball corners[]) // Checks whether the ball object overlaps with the pocket and accordingly sets the score and position
{
	float r=corners[0].getRadius()*corners[0].getRadius();
	for(int i=0;i<4;i++)
	{
		if((obj.getX() - corners[i].getX())*(obj.getX() - corners[i].getX()) + (obj.getY() - corners[i].getY())*(obj.getY() - corners[i].getY()) <= r)
		{
			//printf("%d %f\n",i,corners[i].getX());
			if(obj.getType() == 'S')
			{
				//printf("%f\n",box3.getHeight() );
				setStriker();
				score -= 5;
				break;
			}
			else
			{
				if(obj.getType() == 'R')
					score += 50;
				else if(obj.getType() == 'W')
					score += 10;
				else
					score -=5;

				if(corners[i].getX() < 0)
				{
					if(corners[i].getY() < 0)
					{
						obj.setX(corners[i].getX() - (float)count_lb*0.3 - 1);
						count_lb++;
					//	printf("lb %d %f\n",count_lb,corners[i].getX());	
					}
					else
					{	
						obj.setX(corners[i].getX() - (float)count_lu*0.3 - 1);
						count_lu++;
					//	printf("lu %d %f\n",count_lu,corners[i].getX());
					}
				}
				else
				{
					if(corners[i].getY() < 0)
					{
						obj.setX(corners[i].getX() + (float)count_rb*0.3 + 1);
						count_rb++;	
					//	printf("rb %d %f\n",count_rb,corners[i].getX());

					}
					else
					{	
						obj.setX(corners[i].getX() + (float)count_ru*0.3 + 1);						
						count_ru++;
					//	printf("ru %d %f\n",count_ru,corners[i].getX());
					}
				}
				obj.setY(corners[i].getY() );
				obj.setvx(0.0f);
				obj.setvy(0.0f);
			}
		}
	}
}
void checkWall(Ball &obj,Box &box) //Checks whether the object is colliding with the wall or not and accordingly sets the required velocity
{
	if(obj.getX()+obj.getRadius()>(box2.getLength()/2) || obj.getX() - obj.getRadius() < (-box2.getLength()/2))
	{
		float a=obj.getVx();
		if(a*obj.getX() >0)
			a*=-1;
		obj.setvx(a);
	}
	if(obj.getY()+obj.getRadius()>(box2.getLength()/2) || obj.getY() - obj.getRadius() < (-box2.getLength()/2))
	{
		float a=obj.getVy();
		if(a*obj.getY() >0)
				a*=-1;
		obj.setvy(a);
	}
}

void checkCollision(Ball &obj1,Ball &obj2)
{
	float v1x,v1y,v2x,v2y,r1,r2,x1,y1,x2,y2,xDist,yDist,radDist,cosTheta,sinTheta,m1,m2;
	x1=obj1.getX();
	x2=obj2.getX();
	y2=obj2.getY();
	y1=obj1.getY();
	xDist = x2-x1;
	yDist = y2-y1;
	v1x = obj1.getVx();
	v1y = obj1.getVy();
	v2x = obj2.getVx();
	v2y = obj2.getVy();
	r1 = obj1.getRadius();
	r2 = obj2.getRadius();
	m1 = obj1.getMass();
	m2 = obj2.getMass();
	radDist = r1+r2;

	if((xDist*xDist + yDist*yDist) <= (radDist*radDist))
	{
		float u1T,u2T,u1N,u2N,v1N,v2N;
		float xVel = v2x - v1x;
		float yVel = v2y - v1y;
		sinTheta = (y2-y1)/(r1+r2);
		cosTheta = (x2-x1)/(r1+r2);
		u1T = (-v1x)*sinTheta + v1y*cosTheta;
		u1N = v1x*cosTheta + v1y*sinTheta;
		u2T = (-v2x)*sinTheta + v2y*cosTheta;
		u2N = v2x*cosTheta + v2y*sinTheta;
		v1N = (2*m2*u2N + m1*u1N -m2*u1N)/(m1+m2);
		v2N = (2*m1*u1N + m2*u2N -m1*u2N)/(m1+m2);
		v1x = v1N*cosTheta - u1T*sinTheta;
		v1y = v1N*sinTheta + u1T*cosTheta;
		v2x = v2N*cosTheta - u2T*sinTheta;
		v2y = v2N*sinTheta + u2T*cosTheta;
		if(xDist*xVel<=0)
		{
			obj1.setvx(v1x);
			obj2.setvx(v2x);
			x1+=v1x;
			y1+=v1y;
			x2+=v2x;			
			y2+=v2y;
			xDist = x2-x1;
			yDist = y2-y1;
		}

		if(yDist*yVel<=0)
		{
			obj1.setvy(v1y);
			obj2.setvy(v2y);
			x1+=v1x;
			y1+=v1y;
			x2+=v2x;			
			y2+=v2y;
			xDist = x2-x1;
			yDist = y2-y1;
		}
		

	}
}

void left() // called when Striker moves left either with left key or mouse
{
	float v = 0.05f;
	if(STATE_RIGHT == 1)
		v = 0.01f;
	int flag=0;
	if((Striker.getX()>-1.60))
    	{
    		float xDist,yDist;
    		float dist,temp;
    		for(int i=0;i<9;i++)
    		{
	    		xDist = Coin[i].getX() - Striker.getX();
				yDist = Coin[i].getY() - Striker.getY();
				dist =  (Coin[i].getRadius() + Striker.getRadius())*(Coin[i].getRadius() + Striker.getRadius()) + 0.05f;
    			if(xDist*xDist + yDist*yDist < dist)	
    			{
    				//printf("left %f \n",xDist*xDist + yDist*yDist);
    				temp =dist -(xDist*xDist + yDist*yDist);
    				xDist -= v;
    				if((dist-(xDist*xDist + yDist*yDist)) <= temp )
    				{
    					//printf("left below %f\n ",xDist*xDist + yDist*yDist);
    					flag = 1;    				
    					break;
    				}
    			}
    		}
    		if(flag==0 && (Striker.getX() - v) > -1.60)
    			Striker.setX(Striker.getX() - v) ;	        
    	}
}
void right() // called when Striker moves right either with right key or mouse
{
	float v = 0.05f;
	if(STATE_RIGHT == 1)
		v = 0.01f;
	int flag=0;
	if((Striker.getX()<1.60) && Striker.getState()==0)
	{
		float xDist,yDist,dist,temp;
		for(int i=0;i<9;i++)
		{
    		xDist = Coin[i].getX() - Striker.getX();
			yDist = Coin[i].getY() - Striker.getY();
			dist =  (Coin[i].getRadius()+Striker.getRadius())*(Coin[i].getRadius()+Striker.getRadius())+0.05f;
			if(xDist*xDist + yDist*yDist < dist)	
			{
				temp = dist -(xDist*xDist + yDist*yDist);
				//printf("right %f \n",xDist*xDist + yDist*yDist);
				xDist += v; 
				if((dist -(xDist*xDist + yDist*yDist)) <= temp )
    				{
    			//		printf("right below%f \n",xDist*xDist + yDist*yDist);
    					flag = 1;    				
    					break;
    				}
			}
		}
		if(flag==0 && (Striker.getX() + v) < 1.6)
			Striker.setX(Striker.getX() + v) ;
	}
}
void UpAndDown(int movement,float maxV,float minV) //called when Height has to be increased or decreased either through mouse or keyboard
{
	float Interval = maxV/minV;
	float smallestHeight = box3.getMaxHeight()/Interval;
	if(movement == 1)
		velStriker += minV;
	if(movement == 0)
		velStriker -= minV;
	float divisor = velStriker / minV;
	if(divisor == Interval)
		box3.setHeight(box3.getMaxHeight());
	else
			box3.setHeight(smallestHeight * divisor);
}
// Initializing some openGL 3D rendering options
void initRendering() {

    glEnable(GL_DEPTH_TEST);        // Enable objects to be drawn ahead/behind one another
    glEnable(GL_COLOR_MATERIAL);    // Enable coloring
    glClearColor((1.0f/255)*39,(1.0f/255)*1,(1.0f/255)*1,1.0f);   // Setting a background color
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

    if (key == 27) 	
        exit(0);     // escape key is pressed
     else if (key == ' ' && velStriker>0) // space bar
    {
    	 	Striker.setState(1);
    	
     }
     else if(key == 'c')
     {
     	if(Striker.getState() == 0 && ang<90)
     	{
     		ang+=10;
     		//printf("%f\n",ang);
     		Striker.setvx(velStriker*sin(ang*PI/180));
    		Striker.setvy(velStriker*cos(ang*PI/180));
    	}
     }
     else if(key == 'a')
     {
     	if(Striker.getState()==0 && ang>-90)
     	{
     		ang-=10;
     		Striker.setvx(velStriker*sin(ang*PI/180));
    		Striker.setvy(velStriker*cos(ang*PI/180));
    	}
     }
    
}

void handleKeypress2(int key, int x, int y) {
	
    if (key == GLUT_KEY_LEFT && Striker.getState()==0)
        left();	     	
    
    else if (key == GLUT_KEY_RIGHT)
    	right();
    	
    
    else if (key == GLUT_KEY_UP)
    {
    	if(velStriker<0.21f && Striker.getState()==0 && Striker.getY()==-1.875)
    	{
			UpAndDown(1,0.21f,0.03f);
    	   	Striker.setvx(velStriker*sin(ang*PI/180));
    		Striker.setvy(velStriker*cos(ang*PI/180));
    	}
    }
    
    else if (key == GLUT_KEY_DOWN)
    {
    	if(velStriker>0.0f && Striker.getState()==0 && Striker.getY()==-1.875)
    	{
    		UpAndDown(0,0.21f,0.03f);
    		Striker.setvx(velStriker*sin(ang*PI/180));
    		Striker.setvy(velStriker*cos(ang*PI/180));	
    	}
    }
    
}

void handleMouseclick(int button, int state, int x, int y) {

    if (state == GLUT_DOWN && Striker.getState()==0)
    {   	
       	old_x = x;
       	old_y = y;
       	GLint viewport[4];
		GLdouble modelview[16],projection[16];
		GLfloat wx=x,wy,wz;
		double x1,y1,z1;
       	if (button == GLUT_LEFT_BUTTON)
        {
        	STATE_LEFT = 1;
            glGetIntegerv(GL_VIEWPORT,viewport);
			y=viewport[3]-y;
			wy=y;
			glGetDoublev(GL_MODELVIEW_MATRIX,modelview);
			glGetDoublev(GL_PROJECTION_MATRIX,projection);
			glReadPixels(x,y,1,1,GL_DEPTH_COMPONENT,GL_FLOAT,&wz);
			gluUnProject(wx,wy,wz,modelview,projection,viewport,&x1,&y1,&z1);
			glutPostRedisplay();
			y1 *= 80;
			x1 *= 80;
			float x2 = Striker.getX();
			float y2 = Striker.getY();
			if(y2-y1 == 0.0f)
				ang = -1000.0f;
			else
			{
				ang =  atan((x2-x1)/(y2-y1));
				if(y1 < y2 && x1 > x2)
					ang = (ang*180/PI + 180)*PI/180;
				else if (y1 < y2 && x1 < x2)
					ang = (ang*180/PI + 180)*PI/180;
			}
        }
        else if (button == GLUT_RIGHT_BUTTON)
        	STATE_RIGHT = 1;
        else
        	STATE_MIDDLE = 1;
    }
	else if(state == GLUT_UP)
	{
		STATE_MIDDLE = STATE_RIGHT = 0;
		if(STATE_LEFT == 1 && velStriker>0)
		{

			Striker.setState(1);
			if(ang == -1000.0f)
			{
				Striker.setvx(velStriker);
				Striker.setvy(0.0f);
			}
			else
			{
			
				Striker.setvx(velStriker*sin(ang));
				Striker.setvy(velStriker*cos(ang));
			}
		}
		STATE_LEFT = 0;
	}
	

}
void drag(int x,int y)
{
	if(STATE_RIGHT == 1)
	{	
		if(x - old_x > 0)
			right();
			
		else if(x-old_x<0)
			left();
		old_x=x;
		old_y=y;
	}
	else if(STATE_MIDDLE == 1)
	{
		if(y - old_y < 0)
		{
			if(velStriker<0.21f && Striker.getState()==0 && Striker.getY()==-1.875)
	    		UpAndDown(1,0.21f,0.001f);
		}
		else if(y - old_y > 0)
		{
			if(velStriker>0.0f && Striker.getState()==0 && Striker.getY()==-1.875)
	    		UpAndDown(0,0.21f,0.001f);   	   			    			    	
		}
		old_x = x;
    	old_y = y;
	}
	
}

