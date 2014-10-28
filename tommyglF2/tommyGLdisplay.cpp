//��ʾ��
#include "tommyGLdisplay.h"


tommyGLdisplay::tommyGLdisplay(void)
{
}


tommyGLdisplay::~tommyGLdisplay(void)
{
}

//������ʼ��
void tommyGLdisplay::init_display(void)
{
	area0_length = 10.0f;
	area0_width  = 10.0f;
	//code
	bottole_x = 0.0f;
	bottole_y = 0.0f;
	bottole_size = 6.86f;
	test_fulid.PlaceContainer(bottole_size);
	test_fulid.init_fulid(8);
	data_INF.tommyGL_FreeType_load(΢���ź�,13,13);
}

//��������
void tommyGLdisplay::main_display(void)
{
	//code
	area0_Limit(&bottole_x,area0_length - (bottole_size/2));
	area0_Limit(&bottole_y,area0_width - (bottole_size/2));
	test_fulid.DrawBoxContainer(bottole_x,bottole_y);
	test_fulid.Draw_fulid();
	//data_update();

	//glColor3f(1.0,1.0,1.0);
	//glutSolidTeapot(5.0);//�����ò��//glLineWidth(2.3);//glutWireCube(5.0);//�����÷���
	draw_area0(area0_length,area0_width,-(bottole_size/2));
}

void tommyGLdisplay::area0_Limit(float *a,float area)
{
	if (*a >= area)
		*a = area;
	else if (*a < -area)
		*a = -area;
}

void tommyGLdisplay::draw_area0(GLfloat length,GLfloat width,GLfloat position_z)
{
	glPushMatrix();
	glDisable(GL_LIGHTING);//�رյƹ�...
	glLineWidth(1.2);
	glBegin(GL_LINE_LOOP);
	glColor3f(0.98,0.46,0.26);
	glVertex3f(-length, -width, position_z);
	glVertex3f(-length, width, position_z);
	glVertex3f(length, width, position_z);
	glVertex3f(length, -width, position_z);
	glEnd();
	glPopMatrix();
}


//���ݼ���
void tommyGLdisplay::data_update(void)
{
	//bottole_speed = test_fulid._box_Speed.length();//��ú����ٶ�
	test_fulid.Compute_fulid();
	test_fulid.Compute_box();
}

void tommyGLdisplay::data_trace(void)//�������
{
	cout<<"����ֵ:"<<test_fulid._box_Force.length()<<"\n";
}

//������ʾ����
void tommyGLdisplay::text_reshape(float width,float height)//����reshape
{
	data_INF.tommyGLTextInt(1.0,1.0,1.0,width,height);
}

void tommyGLdisplay::text_display(void)//������ʾ
{
	//code
	data_INF.tommyGL_FreeType("--------------------------------",5,30);
	sprintf(traceinfo,"����Ԫ����: %d",test_fulid.fulid_ele_num);
	data_INF.tommyGL_FreeType(traceinfo,5,46);
	sprintf(traceinfo,"�⻬�˰뾶: %.2f",test_fulid.f_SmoothRange);
	data_INF.tommyGL_FreeType(traceinfo,5,65);
	sprintf(traceinfo,"�������: %.1f",bottole_size);
	data_INF.tommyGL_FreeType(traceinfo,5,84);
	//cout<<"��������:"<<test_fulid._box_Force.length()<<"\n";
}
