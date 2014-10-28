//这是(tommy的)孵化机Opengl实验窗口模板02型~~(GDUT_3111000704)
//INCUBETA OpenGL Laboratory Type2 [version 2013.06.build 008+]
//ALL Rights Reserve! 权利保留 2013
//仅供研究使用.

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

#define CONSOLE_TITLE "INCUBETA OpenGL Laboratory Type2 控制台"

#define LAB_type "INCUBETA OpenGL Laboratory Type2 [v.2013.06.build 008+]"
#define LAB_copyright "GDUT Digital Media Major ~tommy(3111000704) 2013- ALL Rights Reserve!"
#define LAB_TEST_TITLE "[SPH流体算法初探 20130630]"//[test Title + code +date]

#define WM_MOUSEHWHEEL 0x020a

//在这添加自定义的变量

//字符
//tommyGLtext testText;
tommyGLtext tommyGL_LAB_INF;
tommyGLtext tommyGL_LAB_Control;//控制方法
tommyGLtext FPS_INF;

tommyGLtext tommyGL_LAB_Prompt;//控制方法

/*tommyGLtext data_INF;*/

// char controlBar_text[255];
// char* controlBar_l;

char fpsinfo[255];
//char traceinfo[255];

//显示场景
tommyGLdisplay testSence;
tommyGLlight testLight;

void displaymode(int* selectmode);
void showConsole(bool Console);
void showData(bool Data);
bool _showConsole;			     //F1显示控制台
bool _showdatalisten;		     //F4显示数据侦听
bool _showConsole_datalisten;	 //F4显示控制台数据侦听
int  _displaymode;			 //F2显示模式
int  _displaymode_tmp;	     //F2显示模式
bool _displaylight;		     //F3显示灯光

bool _data;		             //数据是否运算

//主要函数方法以及变量的声明
/* game console*/
int tommy_Init(void);
int tommy_Shutdown(void);
int tommy_Main(void);
/*void tommy_FrameRefesh(int value);*/
static void updateView(int state, int ox, int oy, int nx, int ny);
void updateData();//刷新数据
void display();
void reshape_helptest(float width,float height);
void draw_helptext();

/*实验初期专用坐标缓存*/
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

//动态获得窗口大小
float win_height;
float win_width;

static float alpha[8];
static float ex = 2.718282;

tommyGLcamera testCamera;
GLfloat cameraR[2];//记录镜头上下左右的朝向
GLfloat cameraZoom;
int cameraZoomINT = 0;
enum CAMERAPOSE { 
	cameraROTATE = 1,		    /*镜头[旋转]映射*/
	cameraZOOM,                  /*镜头[缩放]映射*/
	scenesCONTROL 
};

HDC hDC;				//hDC是DC的句柄,API中的一个类似指针的数据类型.
HPALETTE hPalette = 0;			/* custom palette (if needed) *///？？？

//在这添加自定义的变量02

//定时器
enum TIMER { 
	TIMER_SEC = 1,		    //一秒
	TIMER_quarter_SEC,      //两秒
	TIMER_25MSEC,           //25毫秒
	TIMER_MIN               //一分钟
};