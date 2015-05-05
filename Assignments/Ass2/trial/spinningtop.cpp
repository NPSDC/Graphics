#define GLM_FORCE_RADIANS
#include <stdio.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include <GL/gl.h>
#include <GL/glu.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <math.h>
#include "imageloader.h"
#include "text2D.hpp"
#include <time.h>

#define PI 3.14156

using namespace std;


static const int no_of_points = 360;
static const int size = 60*59;

class Target
{
	public:
		int l,w,l1,w1,l2,w2;
		GLfloat vertices[18],vertices1[18],vertices2[18];
		unsigned int vao[3],vbo;
		float x,y,z;

		Target()
		{
			l = 5.0f;
			w = 4.0f;
			l1 = 9.0f;
			w1 = 8.0f;
			l2 = 6.0f;
			w2 = 5.0f;
			x = 54.f;
			y = 0.5f;
			z = 1.f;

			vertices[0] = -l/2.0; vertices[1] = -w/2.0; vertices[2] = 0.f;
			vertices[3] = -l/2.0; vertices[4] = w/2.0; vertices[5] = 0.f;
			vertices[6] = l/2.0; vertices[7] = -w/2.0; vertices[8] = 0.f;

			vertices[9] = -l/2.0; vertices[10] = w/2.0; vertices[11] = 0.f;
			vertices[12] = l/2.0; vertices[13] = w/2.0; vertices[14] = 0.f;
			vertices[15] = l/2.0; vertices[16] = -w/2.0; vertices[17] = 0.f;

			
			vertices2[0] = -l2/2.0; vertices2[1] = -w2/2.0; vertices2[2] = -0.1f;
			vertices2[3] = -l2/2.0; vertices2[4] = w2/2.0; vertices2[5] = -0.1f;
			vertices2[6] = l2/2.0; vertices2[7] = -w2/2.0; vertices2[8] = -0.1f;

			vertices2[9] = -l2/2.0; vertices2[10] = w2/2.0; vertices2[11] = -0.1f;
			vertices2[12] = l2/2.0; vertices2[13] = w2/2.0; vertices2[14] = -0.1f;
			vertices2[15] = l2/2.0; vertices2[16] = -w2/2.0; vertices2[17] = -0.1f;


			vertices1[0] = -l1/2.0; vertices1[1] = -w1/2.0; vertices1[2] = -0.2f;
			vertices1[3] = -l1/2.0; vertices1[4] = w1/2.0; vertices1[5] = -0.2f;
			vertices1[6] = l1/2.0; vertices1[7] = -w1/2.0; vertices1[8] = -0.2f;

			vertices1[9] = -l1/2.0; vertices1[10] = w1/2.0; vertices1[11] = -0.2f;
			vertices1[12] = l1/2.0; vertices1[13] = w1/2.0; vertices1[14] = -0.2f;
			vertices1[15] = l1/2.0; vertices1[16] = -w1/2.0; vertices1[17] = -0.2f;			
		}

		void init()
		{
			glGenVertexArrays(3 , &vao[0]);

			glBindVertexArray(vao[0]);
			glGenBuffers(1, &vbo);

			glBindBuffer(GL_ARRAY_BUFFER, vbo);
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
			glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, 0); 
			glEnableVertexAttribArray(0);


			glBindVertexArray(vao[1]);
			glGenBuffers(1, &vbo);

			glBindBuffer(GL_ARRAY_BUFFER, vbo);
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
			glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, 0); 
			glEnableVertexAttribArray(0);


			glBindVertexArray(vao[2]);
			glGenBuffers(1, &vbo);

			glBindBuffer(GL_ARRAY_BUFFER, vbo);
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);
			glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, 0); 
			glEnableVertexAttribArray(0);
		}
		void draw()
		{
			glBindVertexArray(vao[0]);
			glVertexAttrib3f(1,1,0,0);
			glDrawArrays(GL_TRIANGLES,0,18);

			glBindVertexArray(vao[1]);
			glVertexAttrib3f(1,1,1,1);
			glDrawArrays(GL_TRIANGLES,0,18);

			glBindVertexArray(vao[2]);
			glVertexAttrib3f(1,1,0,0);
			glDrawArrays(GL_TRIANGLES,0,18);
		}
};

class Top
{
public:
		float rad,h1,h2,h3,x,y,z;
		//int no_of_points;
		GLfloat verticesCone1[no_of_points*3],verticesCone2[no_of_points*3],verticesCone3[no_of_points*3];
		GLfloat colorCone1[no_of_points*3],colorCone2[no_of_points*3],colorCone3[no_of_points*3];
		unsigned int vao[3],vbo[2];

	Top(void)
	{
		rad = 1.f;
		h2 = 0;
		h3 = h2 + 2;
		h1 = h2 + 4;
		x = 39;
		z = 59;
		y = -2.960784;
		
		//higher cone
		verticesCone1[0] = 0.0f;
		verticesCone1[1] = h1;
		verticesCone1[2] = 0.0f;
		colorCone1[0] = 1.0f;
		colorCone1[1] = 1.0f;
		colorCone1[2] = 1.0f;

		for(int i = 1; i < no_of_points; i++)
		{
			verticesCone1[3*i] = rad*cos(i*PI/180);
			verticesCone1[3*i + 1] = h3;
			verticesCone1[3*i + 2] = rad*sin(i*PI/180);
			colorCone1[3*i] = 0.0f;
			colorCone1[3*i + 1] = 0.0f;
			colorCone1[3*i + 2] = 0.0f;
		}


		//lower cone
		verticesCone2[0] = 0.0f;
		verticesCone2[1] = h2;
		verticesCone2[2] = 0.0f;
		colorCone2[0] = 0.0f;
		colorCone2[1] = 0.0f;
		colorCone2[2] = 0.0f;
		for(int i = 1; i < no_of_points; i++)
		{
			colorCone2[3*i] = 0.0f;
			colorCone2[3*i + 1] = 0.0f;
			colorCone2[3*i + 2] = 0.0f;
			verticesCone2[3*i] = rad*cos(i*PI/180);
			verticesCone2[3*i + 1] = h3;
			verticesCone2[3*i + 2] = rad*sin(i*PI/180);
		}
		colorCone2[3] = 1.0f;
		colorCone2[4] = 1.0f;
		colorCone2[5] = 1.0f;
		
		//middle circle
		verticesCone3[0] = 0.0f;
		verticesCone3[1] = h3;
		verticesCone3[2] = 0.0f;
		colorCone3[0] = 1.0f;
		colorCone3[1] = 1.0f;
		colorCone3[2] = 1.0f;
		for(int i = 1; i < no_of_points; i++)
		{
			verticesCone3[3*i] = rad*2*cos(i*PI/180);
			verticesCone3[3*i + 1] = h3;
			verticesCone3[3*i + 2] = rad*2*sin(i*PI/180);
			colorCone3[3*i] = 0.0f;
			colorCone3[3*i + 1] = 0.0f;
			colorCone3[3*i + 2] = 0.0f;
		}
		colorCone3[3] = 1.0f;
		colorCone3[4] = 1.0f;
		colorCone3[5] = 1.0f;
		

	}
	void seth1(float h)
	{
		h1 = h;
	}
	void seth2(float h)
	{
		h2 = h;
	}
	void seth3(float h)
	{
		h3 = h;
	}
	float geth1()
	{
		return h1;
	}
	float geth2()
	{
		return h2;
	}
	float geth3()
	{
		return h3;
	}
	
	void init()
	{
		glGenVertexArrays(3, &vao[0]);
		
		glBindVertexArray(vao[0]);
		glGenBuffers(2, &vbo[0]);

		glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(verticesCone1), verticesCone1, GL_STATIC_DRAW);
		glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, 0); 
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(colorCone1), colorCone1, GL_STATIC_DRAW);
		glVertexAttribPointer((GLuint)1, 3, GL_FLOAT, GL_FALSE, 0, 0); 
		glEnableVertexAttribArray(1);



		glBindVertexArray(vao[1]);
		glGenBuffers(2, &vbo[0]);

		glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(verticesCone2), verticesCone2, GL_STATIC_DRAW);
		glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, 0); 
		glEnableVertexAttribArray(0);		

		glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(colorCone2), colorCone2, GL_STATIC_DRAW);
		glVertexAttribPointer((GLuint)1, 3, GL_FLOAT, GL_FALSE, 0, 0); 
		glEnableVertexAttribArray(1);



		glBindVertexArray(vao[2]);
		glGenBuffers(2, &vbo[0]);

		glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(verticesCone3), verticesCone3, GL_STATIC_DRAW);
		glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, 0); 
		glEnableVertexAttribArray(0);		

		glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(colorCone3), colorCone3, GL_STATIC_DRAW);
		glVertexAttribPointer((GLuint)1, 3, GL_FLOAT, GL_FALSE, 0, 0); 
		glEnableVertexAttribArray(1);
	}

	void draw()
	{
		glBindVertexArray(vao[0]);
		glDrawArrays(GL_TRIANGLE_FAN, 0, no_of_points);

		glBindVertexArray(vao[1]);
		glDrawArrays(GL_TRIANGLE_FAN, 0, no_of_points);

		glBindVertexArray(vao[2]);
		glDrawArrays(GL_TRIANGLE_FAN, 0, no_of_points);



	}
	
};

class Terrain
{
	public:
		int w,l,count,count2;
		GLfloat *vertices, **height;
		GLfloat color[size*6];
		unsigned int vao, vbo[2];
		float weight;
		void setHeight(int x, int y, float h) 
		{
			vertices[count++] = x;
			vertices[count++] = h;
			vertices[count++] = y;	
 	    }
 	   float getHeight(int r, int c) 
 	   {
 	   	  return height[r][c];
 	   }
       int getWidth() 
       {
        return w; 
       }
       int getLength() 
       { 
       	return l; 
       }
       void setColor(float h) 
        {        	      	
			color[count2++] = 0.5 + h/weight; 
			color[count2++] = 0.5 + h/weight;
			color[count2++] = abs(10*h)/weight;
        }
    	Terrain()
        {
        	count = 0;
        	count2 = 0;
        	weight = 10.0f;
        	Image* image = loadBMP("heightmap.bmp");
			l = image->height;
			w = image->width;
			height = new float*[l];
			for(int i=0;i<l;i++)
				height[i] = new float[w];

			float h;
			for(int i=0;i<l;i++) //reading the data into an array
			{
				for(int j=0;j<w;j++)
				{
					unsigned char color = (unsigned char)image->pixels[3 * (i * image->width + j)];
					h = weight * ((color / 255.0f) - 0.5f); // -weight/2.0 to +weight/2.0
					height[i][j] = h;  //stores the height at x, y
				}
			}
			vertices = new GLfloat[6*l*w];
			//color = new GLfloat[6*l*w];	
			for(int y = 0; y < l-1; y++) 
            {
            	if(y%2 == 0) {
            		for(int x=0; x < w; x++)
            		{
            			h = (height[y][x]);	
                   		setHeight(x, y, h);
                  		setColor(h); 		
                  		//printf("%f\n", h);
	        			h = (height[y+1][x]);	
                   		setHeight(x, y+1, h);                   		
                   		setColor(h);
            		}
            	}
            	else 
            	 {
            		for(int x= w-1; x >= 0; x--)
            		{
            			h = (height[y][x]);	
                   		setHeight(x, y, h);                   		
                   		setColor(h);
            			h = (height[y+1][x]);	
                   		setHeight(x, y+1, h);                   		
                   		setColor(h);
            		}
            	}
            	
             }
             delete image;
        }

        

        void init()
        {
        	glGenVertexArrays(1, &vao);

			glBindVertexArray(vao);
			glGenBuffers(2, &vbo[0]);

			//vbo for terrain
			glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
			glBufferData(GL_ARRAY_BUFFER, sizeof(float)*2*w*l*3, vertices, GL_STATIC_DRAW);
			glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, 0); 
			glEnableVertexAttribArray(0);

			glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
			glBufferData(GL_ARRAY_BUFFER, sizeof(color), color, GL_STATIC_DRAW);
			glVertexAttribPointer((GLuint)1, 3, GL_FLOAT, GL_FALSE, 0, 0); 
			glEnableVertexAttribArray(1);
        }
        void draw()
		{
			//for(int i=0;i<count;i++)
        	//	printf("%f %f %f\n",color[3*i],color[3*i + 1],color[3*i + 2] );

			glBindVertexArray(vao);	
			
			//glVertexAttrib3f(1,0.5,0.5,0.5);
			glDrawArrays(GL_TRIANGLE_STRIP, 0, count/3);	// draw first object
		}

       
};

class Vec
{
	public:
		glm::vec3 Eyes;
		glm::vec3 Pos;
		glm::vec3 Up;
	 Vec()
	 {
	 	Eyes[0] = 0.f;
	 	Eyes[1] = 40.f;
	 	Eyes[2] = 71.f;

	 	Pos[0] = 0.f;
	 	Pos[1] = 0.f;
	 	Pos[2] = -27.f;

	 	Up[0] = 0.f;
	 	Up[1] = 1.0f;
	 	Up[2] = 0.f;
	 }


};

struct GLMatrices {
	glm::mat4 projection;
	glm::mat4 model;
	glm::mat4 view;
	GLuint MatrixID;
} Matrices;


float camera_rotation_angle = 0;
int programID;
float Trotation = 0.f;
float toprotation = 0.f;
Terrain T = Terrain();
Top top = Top();
Target tar = Target();
Vec obj = Vec();
int flag = 0;
int flagT = 0;
int flagF = 0;
int Score = 10;
int speed = 1;
int isDragging = 0;
int xDragStart;
int zDragStart;
float deltaX = 0,deltaY = 0;

void reshape(int w, int h)
{
	GLfloat fov = 45.0f;
	glViewport(0,0,(GLsizei)w,(GLsizei)h);
	Matrices.projection = glm::perspective (fov, (GLfloat) w / (GLfloat) h, 0.1f, 500.0f);
}


/* Function to load Shaders - Use it as it is */
GLuint loadShaders(const char * vertex_file_path,const char * fragment_file_path) {

	// Create the shaders
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	// Read the Vertex Shader code from the file
	std::string VertexShaderCode;
	std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
	if(VertexShaderStream.is_open())
	{
		std::string Line = "";
		while(getline(VertexShaderStream, Line))
			VertexShaderCode += "\n" + Line;
		VertexShaderStream.close();
	}

	// Read the Fragment Shader code from the file
	std::string FragmentShaderCode;
	std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
	if(FragmentShaderStream.is_open()){
		std::string Line = "";
		while(getline(FragmentShaderStream, Line))
			FragmentShaderCode += "\n" + Line;
		FragmentShaderStream.close();
	}

	GLint Result = GL_FALSE;
	int InfoLogLength;

	// Compile Vertex Shader
	printf("Compiling shader : %s\n", vertex_file_path);
	char const * VertexSourcePointer = VertexShaderCode.c_str();
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer , NULL);
	glCompileShader(VertexShaderID);

	// Check Vertex Shader
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	std::vector<char> VertexShaderErrorMessage(InfoLogLength);
	glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
	fprintf(stdout, "%s\n", &VertexShaderErrorMessage[0]);

	// Compile Fragment Shader
	printf("Compiling shader : %s\n", fragment_file_path);
	char const * FragmentSourcePointer = FragmentShaderCode.c_str();
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer , NULL);
	glCompileShader(FragmentShaderID);

	// Check Fragment Shader
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	std::vector<char> FragmentShaderErrorMessage(InfoLogLength);
	glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
	fprintf(stdout, "%s\n", &FragmentShaderErrorMessage[0]);

	// Link the program
	fprintf(stdout, "Linking program\n");
	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);

	// Check the program
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	std::vector<char> ProgramErrorMessage( max(InfoLogLength, int(1)) );
	glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
	fprintf(stdout, "%s\n", &ProgramErrorMessage[0]);

	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);

	return ProgramID;
}

void init(void)
{
	//top.init();
	//gametarget.init();
	T.init();
	top.init();
	tar.init();
	initText2D("Holstein.DDS");
	programID = loadShaders( "VertexShader.vert", "FragmentShader.frag" );
	Matrices.MatrixID = glGetUniformLocation(programID, "MVP");

	reshape(800, 800);
	
	glClearColor (0.0f, 0.0f, 0.4f, 0.0f);
	glClearDepth (1.0f);

	glEnable (GL_DEPTH_TEST);
	glDepthFunc (GL_LESS);
}

void SetEye(char key,Vec &obj)
{
	switch (key)
	{
		case 'p':obj.Eyes[0] = 0;
				 obj.Eyes[1] = 40;
				 obj.Eyes[2] = 71;
				 obj.Pos[0] = 0;
				 obj.Pos[1] = 0;
				 obj.Pos[2] = -27;
				 obj.Up[0] = 0.f;
	 			 obj.Up[1] = 1.0f;
	 			 obj.Up[2] = 0.f;
				 break;

		case 't':obj.Eyes[0] = top.x - T.getLength()/2 ; //top
				 obj.Eyes[1] = top.y + top.h1 ;
				 obj.Eyes[2] = top.z - T.getWidth()/2;
				 obj.Pos[0] = tar.x - T.getLength()/2;
				 obj.Pos[1] = tar.y ;
				 obj.Pos[2] = tar.z - T.getWidth()/2;
				 obj.Up[0] = 0.f;
	 			 obj.Up[1] = 1.0f;
	 			 obj.Up[2] = 0.f;
	 			 break;

		case 'f':obj.Pos[0] = tar.x - T.getLength()/2; //follow
				 obj.Pos[1] = tar.y ;
				 obj.Pos[2] = tar.z - T.getWidth()/2;
				 float dist, cosTheta, sinTheta;
				 dist = (tar.z - top.z)*(tar.z - top.z) + (tar.x - top.x)*(tar.x - top.x);
				 dist = glm::sqrt(dist);

				 if(dist > 0)
				 {
					 cosTheta = (tar.x - top.x)/dist;
					 sinTheta = (-tar.z + top.z)/dist;
				 }
				 else
				 {
				 	sinTheta = 1;
				 	cosTheta = 0;
				 }				 
				 obj.Eyes[2] = top.z -T.getWidth()/2 + 7*top.rad*sinTheta ;
				 obj.Eyes[1] = top.y + top.h1;
				 obj.Eyes[0] = top.x - T.getLength()/2 - 7*top.rad*cosTheta; 				 		
				 break;

		case 'o':obj.Pos[0] = 0;
				 obj.Pos[1] = 0;
				 obj.Pos[2] = 0;
				 obj.Eyes[0] = 0;
				 obj.Eyes[1] = 80;
				 obj.Eyes[2] = 0;
				 obj.Up[0] = 0.f;
	 			 obj.Up[1] = 0.0f;
	 			 obj.Up[2] = -1.f;
				 break;

		case 'h':obj.Pos[0] = 0 + deltaX;
				 obj.Pos[1] = 0 + deltaY;
				 obj.Pos[2] = -27;
				 obj.Up[0] = 0.f;
	 			 obj.Up[1] = 1.0f;
	 			 obj.Up[2] = 0.f;
				 break;

		default : break;
	}
}

void keyboardDown (unsigned char key, int x, int y)
{
	switch (key) {
		case 'Q':
		case 'q':
		case 27: //ESC
			exit (0);
			break;
		case ' ':
			flag = 1;
			break;
		case 'p':SetEye('p',obj);  //Player View
			    flagT = 0;
			    flagF = 0;
			    break;
		case 't':SetEye('t',obj); //top view
				flagT = 1;
				flagF = 0;
				break;

		case 'f':SetEye('f',obj); //front view
				 flagF = 1;
				 flagT = 0;
				break;
		case 'o':SetEye('o',obj); //overview
				flagT = 0;
			    flagF = 0;
			    break;

		default:
			break;
	}

}
void pressSpecialKey(int key, int xx, int yy)
{
	switch (key) 
	{
		case GLUT_KEY_LEFT:
			if(flag == 0 && top.x > 1)
			//	printf("yes\n");
			top.x -= 1;
			break;
		case GLUT_KEY_RIGHT:
			if(flag == 0 && top.x < 59)
			top.x += 1;
			break;
	}
	
}

int genrandom()
{
	int num = rand()%54;
	return num;
}

void checkCollison()
{
	float w = tar.w1;
	if((top.z + top.rad) <= 0.f)
	{
		if((top.rad + top.x >= tar.x - w/2) &&  (top.rad + top.x <= tar.x + w/2))
		{
			Score += 10;
			int a;
			a = genrandom();
			while(1)
			{
				if((a >=18 && a <= 45) || a<2)
				{	
					//a += 27;
					//a %= 54;
					a = genrandom();
				}
				else
					break;
			}
			tar.x = a;	
		}
		
		top = Top();
		top.init();
		flag = 0;
	}	
}

void drawScore()
{
	unsigned int vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);	
	char text[256];
	sprintf(text,"Score: %d", Score);
	printText2D(text,0,2,25);
}

void draw(void)
{
	// clear the screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(programID);

 	top.y = T.getHeight((int)top.z , top.x );

 	 if(flagT == 1)
		SetEye('t',obj);

	if(flagF == 1)
		SetEye('f',obj);
	//camera
	//printf("Eye %f %f %f\n",obj.Eyes[0],obj.Eyes[1],obj.Eyes[2] );
	glm::vec3 eye ( obj.Eyes[0],obj.Eyes[1],obj.Eyes[2] );
	//	glm::vec3 eye ( 0, 0, -4.5);
	glm::vec3 target (obj.Pos[0], obj.Pos[1], obj.Pos[2]);
	glm::vec3 up (obj.Up[0], obj.Up[1], obj.Up[2]); // lies in perpendicular plane to  the vector formed by eye and target
	//if(up[0] == (target[0]-eye[0]) || up[2] == (target[2]-eye[2]))
	//	printf("Yes\n");
	Matrices.view = glm::lookAt( eye, target, up );
 	//camera ends

	// Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
	glm::mat4 VP = Matrices.projection * Matrices.view;
	glm::mat4 MVP;  // MVP = Projection * View * Model

	// transformation on target
	Matrices.model = glm::mat4(1.0f); // load identity matrix
	glm::mat4 targetTranslation = glm::translate (glm::vec3(-T.getWidth()/2, -0.0f, -T.getLength()/2) );
	Matrices.model *= targetTranslation;
	targetTranslation = glm::translate(glm::vec3(tar.x,tar.y,tar.z));
	Matrices.model *= targetTranslation;

	MVP = VP * Matrices.model; // MVP = p * V * M	
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);

		tar.draw();

	// transformation on terrain
	Matrices.model = glm::mat4(1.0f); // load identity matrix
	glm::mat4 translateTerrain = glm::translate (glm::vec3(-T.getWidth()/2, -0.0f, -T.getLength()/2) ); 
	glm::mat4 rotateTerrain = glm::rotate (Trotation, glm::vec3(0, 1, 0) ); 
    Matrices.model *= rotateTerrain* translateTerrain;
	MVP = VP * Matrices.model; // MVP = p * V * M
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
	T.draw();
		
	Matrices.model = glm::mat4(1.0f);

	glm::mat4 translateTop = glm::translate (glm::vec3(-T.getWidth()/2, -0.0f, -T.getLength()/2) );
	Matrices.model *= translateTop;
	translateTop = glm::translate (glm::vec3(top.x, top.y, top.z)); // glTranslatef
	glm::mat4 rotateTop = glm::rotate (toprotation, glm::vec3(0, 1, 0) ); 
    Matrices.model *= translateTop * rotateTop; // p * V * M;
	MVP = VP * Matrices.model; 
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    top.draw();

	Matrices.model = glm::mat4(1.0f); // load identity matrix    
	MVP = VP * Matrices.model; // MVP = p * V * M	
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
		drawScore();


	glBindVertexArray(0);
	glutSwapBuffers();

	camera_rotation_angle;// = 180;
	//Trotation++;
	toprotation+=5;	

	if(flag == 1 && top.z + top.rad > 0)
		top.z -= speed;	
		
	checkCollison();
	
  
}

int main (int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitContextVersion (3, 3); // Init GL 3.3
	glutInitContextFlags (GLUT_CORE_PROFILE); // Use Core profile - older functions are deprecated
	glutInitWindowSize(800,800);
	glutCreateWindow("SpinningTop");
	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		cout << "glewInit failed, aborting." << endl; // Problem: glewInit failed, something is seriously wrong.
		exit (1);
	}
	cout << "Status: Using GLEW " << glewGetString(GLEW_VERSION) << endl;
	cout << "OpenGL version " << glGetString(GL_VERSION) << " supported" << endl;

	glutKeyboardFunc (keyboardDown);

	glutDisplayFunc(draw);
	glutIdleFunc(draw);
	glutReshapeFunc(reshape);	
	glutSpecialFunc(pressSpecialKey);
	/*glutMouseFunc(mouseButton); 
	glutMotionFunc(mouseMove); */
	init();
	glutMainLoop();

	return 0;
}