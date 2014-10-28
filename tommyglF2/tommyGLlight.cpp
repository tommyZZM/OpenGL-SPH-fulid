#include <windows.h>	
#include <stdio.h>
#include <math.h>	

#include <GL/gl.h>			
#include <GL/glu.h>			
#include <GL/glut.h>

#include "tommyGLlight.h"


tommyGLlight::tommyGLlight(void)
{
}

tommyGLlight::~tommyGLlight(void)
{
}

void tommyGLlight::tommyGLlightSTANDARD(GLfloat lightX,GLfloat lightY,GLfloat lightZ)
{
	GLfloat Ambient[] = { 0.6f, 0.6f, 0.6f, 1.0f };
	GLfloat Diffuse[] = { 0.8f, 0.8f, 0.8f, 0.66f } ;
	GLfloat Specular[]= { 0.6f, 0.6f, 0.6f, 0.66f } ;	
	glLightfv( GL_LIGHT0, GL_AMBIENT, Ambient);
	glLightfv( GL_LIGHT0, GL_DIFFUSE, Diffuse);
	glLightfv( GL_LIGHT0, GL_SPECULAR, Specular);
	GLfloat Position[] = { lightX, lightY, lightZ, 0.0f };
	glLightfv( GL_LIGHT0, GL_POSITION, Position);
	glEnable(GL_LIGHT0);
}

void tommyGLlight::tommyGLlightSTANDARD_setPosition(GLfloat lightX,GLfloat lightY,GLfloat lightZ)
{
	Position[4] = (lightX, lightY, lightZ, 0.0f);
	glLightfv( GL_LIGHT0, GL_POSITION, Position);
}

void tommyGLlight::tommyGLlightSTANDARD_on()
{
	glEnable(GL_LIGHT0);
}

void tommyGLlight::tommyGLlightSTANDARD_off()
{
	glDisable(GL_LIGHT0);
}

