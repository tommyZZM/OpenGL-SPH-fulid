//����(tommy��)������Openglʵ�鴰��ģ��02��~~(GDUT_3111000704)
//INCUBETA OpenGL Laboratory Type2 [version 2013.06.build 008+]
//ALL Rights Reserve! Ȩ������ 2013
//�����о�ʹ��.

#include <windows.h>	
#include <stdio.h>
#include <math.h>	
#include <io.h>
#include <fcntl.h>

#include <GL/gl.h>			
#include <GL/glu.h>			
#include <GL/glut.h>
#include "tommyGLtext.h"
#include "tommyGLcamera.h"
#include "tommyGLdisplay.h"
#include "tommyGLlight.h"

#define WINDOW_TITLE "INCUBETA OpenGL Laboratory Type2 beta"
#define WINDOW_WIDTH 900
#define WINDOW_HEIGHT 640

#define CONSOLE_TITLE "INCUBETA OpenGL Laboratory Type2 ����̨"

#define LAB_type "INCUBETA OpenGL Laboratory Type2 [v.2013.06.build 008+]"
#define LAB_copyright "GDUT Digital Media Major ~tommy(3111000704) 2013- ALL Rights Reserve!"
#define LAB_TEST_TITLE "[SPH�����㷨��̽ 20130630]"//[test Title + code +date]

#define WM_MOUSEHWHEEL 0x020a

//��������Զ���ı���

//�ַ�
//tommyGLtext testText;
tommyGLtext tommyGL_LAB_INF;
tommyGLtext tommyGL_LAB_Control;//���Ʒ���
tommyGLtext FPS_INF;

tommyGLtext tommyGL_LAB_Prompt;//���Ʒ���

/*tommyGLtext data_INF;*/

// char controlBar_text[255];
// char* controlBar_l;

char fpsinfo[255];
//char traceinfo[255];

//��ʾ����
tommyGLdisplay testSence;
tommyGLlight testLight;

void displaymode(int* selectmode);
void showConsole(bool Console);
void showData(bool Data);
bool _showConsole;			     //F1��ʾ����̨
bool _showdatalisten;		     //F4��ʾ��������
bool _showConsole_datalisten;	 //F4��ʾ����̨��������
int  _displaymode;			 //F2��ʾģʽ
int  _displaymode_tmp;	     //F2��ʾģʽ
bool _displaylight;		     //F3��ʾ�ƹ�

bool _data;		             //�����Ƿ�����

//��Ҫ���������Լ�����������
/* game console*/
int tommy_Init(void);
int tommy_Shutdown(void);
int tommy_Main(void);
/*void tommy_FrameRefesh(int value);*/
static void updateView(int state, int ox, int oy, int nx, int ny);
void updateData();//ˢ������
void display();
void reshape_helptest(float width,float height);
void draw_helptext();

/*ʵ�����ר�����껺��*/
int tmp_x;
int tmp_y;
int tmp_z;

/*draw information*/
static int dvel = 0;
static int dhelp = 1;

/*window*/
static int win_id;
static int win_x, win_y;
static int mouse_down[3];
static int omx, omy, mx, my;

//��̬��ô��ڴ�С
float win_height;
float win_width;

static float alpha[8];
static float ex = 2.718282;

tommyGLcamera testCamera;
GLfloat cameraR[2];//��¼��ͷ�������ҵĳ���
GLfloat cameraZoom;
int cameraZoomINT = 0;
enum CAMERAPOSE { 
	cameraROTATE = 1,		    /*��ͷ[��ת]ӳ��*/
	cameraZOOM,                  /*��ͷ[����]ӳ��*/
	scenesCONTROL 
};

HDC hDC;				//hDC��DC�ľ��,API�е�һ������ָ�����������.
HPALETTE hPalette = 0;			/* custom palette (if needed) *///������

//��������Զ���ı���02

//��ʱ��
enum TIMER { 
	TIMER_SEC = 1,		    //һ��
	TIMER_quarter_SEC,      //����
	TIMER_25MSEC,           //25����
	TIMER_MIN               //һ����
};