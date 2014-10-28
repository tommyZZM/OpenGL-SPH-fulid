#include "tommyGLfulid_ele.h"


tommyGLfulid_ele::tommyGLfulid_ele(void)
{
}


tommyGLfulid_ele::~tommyGLfulid_ele(void)
{
	
}

void tommyGLfulid_ele::ele_init(float x,float y,float z)
{
	ele_pos=Vector3d(x,y,z);
	
	e_Pressure    = 0.0f;
	e_Density     = 0.0f;
	ef_Speed      = 0.0f;
	ef_Force      = 0.0f;

	ef_Speed      = Vector3d(0.0f,0.0f,0.0f);
	ef_last_Speed = ef_Speed;
	ef_Force      = Vector3d(0.0f,0.0f,0.0f);

	e_NeighborNum = 0;
	//ele_NeighborCount(e_NeighborNum,0);
}

void tommyGLfulid_ele::ele_draw()
{
	glPushMatrix();
	//glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
	//glDisable(GL_LIGHTING);
	glTranslatef (ele_pos.x(),ele_pos.y(),ele_pos.z());
	glColor3f(0.345,0.612,0.867);
	glutSolidSphere(0.128,4,4);
	glPopMatrix();
}

void tommyGLfulid_ele::ele_move(Vector3d Container_pos,GLfloat Container_size)
{
	ef_Speed += ef_Force;
	ele_pos  += ef_Speed;
	ele_area_control(ele_pos.x(),&ef_Speed.x(),Container_pos.x(),Container_size);
	ele_area_control(ele_pos.y(),&ef_Speed.y(),Container_pos.y(),Container_size);
	ele_area_control(ele_pos.z(),&ef_Speed.z(),Container_pos.z(),Container_size);
}

void tommyGLfulid_ele::ele_area_control(double pos,double* speed,GLfloat area,GLfloat size)
{
	if (pos < area-(size*0.9)/2)
	{
		//*pos += area-(size*0.9)/2 - *pos;
		*speed += area-(size*0.9)/2 - pos;
	}
	if (pos > area+(size*0.9)/2)
	{
		*speed += area+(size*0.9)/2 - pos;
	}
}