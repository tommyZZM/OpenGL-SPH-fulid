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

	Vector3d ele_pos, ele_last_pos; //����Ԫ��λ������

	float e_Density;                       //�ܶ�
	float e_Pressure;                      //ѹ��

	Vector3d ef_Speed, ef_last_Speed;            //�ٶ�
	Vector3d ef_Speed_max;                       //����ٶ�
	Vector3d ef_Speed_min;                       //��С�ٶ�
	Vector3d ef_Force;                           //����

	static float b_Stiffness;                           //�߽�ն�
	static float b_Dampening;                           //�߽�˥����

	int e_NeighborNum;                           //�ھӤ���Ŀ
	int *e_Neighbor;                             //�ھ�
	//void ele_NeighborPush(int num,int neighbor); //�����ھӵ�����
	//void ele_NeighborPop();                      //�ͷŴ���ռ�

	void ele_init(float x,float y,float z);
	void ele_draw();
	void ele_move(Vector3d Container_pos,GLfloat Container_size);
	void ele_area_control(double pos,double* speed,GLfloat area,GLfloat size);
};

