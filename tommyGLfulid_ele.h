#include <windows.h>	
#include <stdio.h>
#include <math.h>	
#include <vector>

#include <GL/gl.h>			
#include <GL/glu.h>			
#include <GL/glut.h>

#include "tommyglF2/Plug/tommyVector3.h"
using namespace std;

#pragma once
class tommyGLfulid_ele
{
public:
	tommyGLfulid_ele(void);
	~tommyGLfulid_ele(void);

	Vector3d ele_pos, ele_last_pos; //流体元的位置向量

	float e_Density;                       //密度
	float e_Pressure;                      //压力

	Vector3d ef_Speed, ef_last_Speed;            //速度
	Vector3d ef_Speed_max;                       //最大速度
	Vector3d ef_Speed_min;                       //最小速度
	Vector3d ef_Force;                           //受力

	static float b_Stiffness;                           //边界刚度
	static float b_Dampening;                           //边界衰减率

	int e_NeighborNum;                           //邻居の数目
	int *e_Neighbor;                             //邻居
	//void ele_NeighborPush(int num,int neighbor); //储存邻居的引索
	//void ele_NeighborPop();                      //释放储存空间

	void ele_init(float x,float y,float z);
	void ele_draw();
	void ele_move(Vector3d Container_pos,GLfloat Container_size);
	void ele_area_control(double pos,double* speed,GLfloat area,GLfloat size);
};

