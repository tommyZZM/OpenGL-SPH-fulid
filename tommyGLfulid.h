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
class tommyGLfulid //流体类..
{
public:
	tommyGLfulid(void);
	~tommyGLfulid(void);

	void PlaceContainer(GLfloat box_size);           //设置方体容器
	void DrawBoxContainer(GLfloat x,GLfloat y);      //绘制方体容器
	bool VolumeBoxContainer(GLfloat a,int x1_or_y2); //方体容器de体积
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
	void Compute_fulid();                  //囧囧的流体运算...
	void CFulid_Pressure();
	void CFulid_Force();

	int fulid_ele_num;
	tommyGLfulid_ele * _fulid_ele;         //数组of每个流体元

	//float f_g;                           //重力系数
	float f_Mass;                          //质量系数
	float f_SmoothRange;                   //光滑核半径
	float f_Sh2;                           //光滑核半径的平方
	float f_Viscosity;                     //粘稠度
	float f_DENSITY;                       //平静时的压力

	double** fef_dists;                    //二维数组储存流体元之间de距离

};

