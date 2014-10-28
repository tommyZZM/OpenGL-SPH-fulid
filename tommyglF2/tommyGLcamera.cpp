#include <stdio.h>
#include <math.h>
#include <windows.h>			
#include <GL/gl.h>			
#include <GL/glu.h>			
#include <GL/glut.h>

#include "tommyGLcamera.h"


tommyGLcamera::tommyGLcamera(void)
{
}


tommyGLcamera::~tommyGLcamera(void)
{
}


void tommyGLcamera::tommyGLcameraSTANDARD(GLfloat cameraX,GLfloat cameraY,GLfloat cameraZ,
	GLfloat targetX,GLfloat targetY,GLfloat targetZ,GLfloat RotateX,GLfloat RotateY,GLfloat cameraScale)
{
	gluLookAt(cameraX,cameraY,cameraZ,targetX,targetY,targetZ,0.0,0.0,1.0);
	glRotatef(RotateX, 0.0f, 1.0f, 0.0f);
	glRotatef(RotateY, 0.0f, 0.0f, 1.0f);
	glScalef(cameraScale,cameraScale,cameraScale);
}
