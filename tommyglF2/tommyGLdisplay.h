#include <windows.h>	
#include <stdio.h>
#include <math.h>	
#include <vector>

#include <GL/gl.h>			
#include <GL/glu.h>			
#include <GL/glut.h>

#include "tommyGLtext.h"
#include "../tommyGLfulid.h"

using namespace std;

#pragma once
class tommyGLdisplay//display头文件
{
public:
	tommyGLdisplay(void);
	~tommyGLdisplay(void);
	void init_display(void);
	void main_display(void);
	void data_update(void);

	void text_display(void);
	void text_reshape(float width,float height);
	char traceinfo[255];

	void data_trace(void);

	tommyGLfulid test_fulid;
	GLfloat bottole_x;
	GLfloat bottole_y;
	GLfloat bottole_size;
	float bottole_speed;

	void area0_Limit(float *a,float area);//场景区域限制

private:
	tommyGLtext data_INF;
	GLfloat area0_length;
	GLfloat area0_width;
	void draw_area0(GLfloat length,GLfloat width,GLfloat position_z);//绘制场景区域
};

