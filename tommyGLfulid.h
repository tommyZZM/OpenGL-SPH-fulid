#include <windows.h>	
#include <stdio.h>
#include <math.h>	
#include <vector>

#include <GL/gl.h>			
#include <GL/glu.h>			
#include <GL/glut.h>

#include "tommyGLfulid_ele.h"
#include "tommyglF2/Plug/tommyVector3.h"

#define PI       3.14168
#define gasK     1.00
#define PRESS    0.52
#define GRAVITY  0.069

using namespace std;

#pragma once
class tommyGLfulid //������..
{
public:
	tommyGLfulid(void);
	~tommyGLfulid(void);

	void PlaceContainer(GLfloat box_size);           //���÷�������
	void DrawBoxContainer(GLfloat x,GLfloat y);      //���Ʒ�������
	bool VolumeBoxContainer(GLfloat a,int x1_or_y2); //��������de���
	void Compute_box();
	Vector3d _box_pos;
	Vector3d _box_last_pos;
	Vector3d _box_Speed;
	Vector3d _box_last_Speed;
    //#define  _box_Speed_MAX 0.66f
	Vector3d _box_Force;
	GLfloat _box_size;
	

	int _fulidsize;
	void init_fulid(int fulid_size);
	void Draw_fulid();
	void Compute_fulid();                  //������������...
	void CFulid_Pressure();
	void CFulid_Force();

	int fulid_ele_num;
	tommyGLfulid_ele * _fulid_ele;         //����ofÿ������Ԫ

	//float f_g;                           //����ϵ��
	float f_Mass;                          //����ϵ��
	float f_SmoothRange;                   //�⻬�˰뾶
	float f_Sh2;                           //�⻬�˰뾶��ƽ��
	float f_Viscosity;                     //ճ���
	float f_DENSITY;                       //ƽ��ʱ��ѹ��

	double** fef_dists;                    //��ά���鴢������Ԫ֮��de����

};

