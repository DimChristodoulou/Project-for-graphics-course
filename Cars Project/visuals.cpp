#include <stdio.h>     // - Just for some ASCII messages
#include <stdlib.h>
#include <string.h>
#include "gl/glut.h"   // - An interface and windows 
#include "visuals.h"   // Header file for our OpenGL functions
#include <math.h>
#include <iostream>
#include <fstream>
using namespace std;

model md;

void ReadFile(model* md);
void DisplayModel(model md);

void Render()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // Clean up the colour of the window
														 // and the depth buffer
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glColor3f(1.0, 0.5, 0.2);							   // Set drawing colour = orange

	ReadFile(&md);
	DisplayModel(md);
	//printf("%d\n", md.vertices);
	//glutSolidTeapot(20.0);							   // Draw a built-in primitive
	//glutWireTeapot(20.0);
	//glutSolidSphere(20.0,30,24);

	glutSwapBuffers();             // All drawing commands applied to the 
								   // hidden buffer, so now, bring forward
								   // the hidden buffer and hide the visible one
}

//-----------------------------------------------------------

void Resize(int w, int h)
{ // w and h are window sizes returned by glut
  // define the visible area of the window ( in pixels )

	if (h == 0) h = 1;
	glViewport(0, 0, w, h);
	//glViewport(100,100,400,400);

	// Setup viewing volume
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();


	//         L,      R,      B,     T,     N,      F
	glOrtho(-50.0f, 50.0f, -50.0f, 50.0f, 100.0f, -100.0f);


}


void Setup()  // DON'T TOUCH IT 
{
	//Parameter handling
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);

	// polygon rendering mode
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	//Set up light source
	GLfloat light_position[] = { 0.0, 30.0,-50.0,0.0 };

	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	// Black background
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

}

void ReadFile(model* md)
{
	ifstream obj_file("clk.obj");                   // Open the file for reading OBJINFO.TXT

	if (obj_file.fail())
		exit(1);

	char identifier;
	obj_file >> md->vertices;                               // Get the number of vertices
	obj_file >> identifier;
	int i = 0;
	while (identifier == 'v') {                        // Get the vertex coordinates

		obj_file >> md->obj_points[i].x;
		obj_file >> md->obj_points[i].y;
		obj_file >> md->obj_points[i].z;
		i++;
		obj_file >> identifier;
	}

	obj_file >> md->faces;									// Get the number of faces
	obj_file >> identifier;
	i = 0;
	while (identifier == 'f') {                        // Get the face structure

		obj_file >> md->obj_faces[i].vtx[0];
		obj_file >> md->obj_faces[i].vtx[1];
		obj_file >> md->obj_faces[i].vtx[2];
		i++;
		obj_file >> identifier;
	}
	//printf("hello\n");
	obj_file.close();
}

void DisplayModel(model md)
{

	glPushMatrix();
	glBegin(GL_TRIANGLES);

	for (int i = 0; i < md.faces; i++)
	{
		glVertex3f(md.obj_points[md.obj_faces[i].vtx[0] - 1].x, md.obj_points[md.obj_faces[i].vtx[0] - 1].y, md.obj_points[md.obj_faces[i].vtx[0] - 1].z);
		glVertex3f(md.obj_points[md.obj_faces[i].vtx[1] - 1].x, md.obj_points[md.obj_faces[i].vtx[1] - 1].y, md.obj_points[md.obj_faces[i].vtx[1] - 1].z);
		glVertex3f(md.obj_points[md.obj_faces[i].vtx[2] - 1].x, md.obj_points[md.obj_faces[i].vtx[2] - 1].y, md.obj_points[md.obj_faces[i].vtx[2] - 1].z);
	}

	glEnd();
	glPopMatrix();

}