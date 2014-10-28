//这是(tommy的)孵化机Opengl实验窗口模板02型~~(GDUT_3111000704)
//ALL Rights Reserve! 权利保留 2013
//仅供研究使用.

//version 2013 [0000000] [这里填写实验编号]

#include <stdio.h>
#include <math.h>
#include <windows.h>			
#include <GL/gl.h>			
#include <GL/glu.h>			
#include <GL/glut.h>
#include "tommyGLmainF2.h"
#include "tommyGLdisplay.h"
//#include "tommyGLtext.h"

int tommy_Init(void)
{
	glEnable(GL_DEPTH_TEST);//打开深度测试
	glEnable(GL_LIGHTING);//打开灯光
	glClearColor (0.26, 0.26, 0.26, 0.0);//设置背景颜色
	glShadeModel (GL_FLAT);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	win_height = WINDOW_HEIGHT;
	win_width = WINDOW_WIDTH;
	_showConsole = false;
	_showdatalisten = false;
	_data = false;
	_displaymode=1;
	_displaymode_tmp = _displaymode;
	_displaylight = false;//controlBar_l="关闭";
	cameraR[0]=30;//x
	cameraR[1]=60;//y
	cameraZoom = 1.0;//缩放值
	testLight.tommyGLlightSTANDARD(-49.0f,49.0f,66.0f);
	tommyGL_LAB_Control.tommyGL_FreeType_load(微软雅黑,13,13);
	tommyGL_LAB_Prompt.tommyGL_FreeType_load(微软雅黑,16,16);//提示
	tommyGL_LAB_INF.tommyGL_FreeType_load(微软雅黑,13,13);
	FPS_INF.tommyGL_FreeType_load("msyh.ttf",16,16);
	

	//场景初始化
	testSence.init_display();
	tmp_x = 0;
	tmp_y = 0;

	return (1);
}


int tommy_Main(void)
{
	//Main函数
	display();
	
	return (1);
}

int tommy_Shutdown(void)
{
	//在这里添加程序关闭处理代码

	return (1);
}


//reshape处理函数
void reshape(int width, int height)
{
	glViewport(0, 0, width, height);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	gluPerspective(56.0, (float)width/height, 1.0, 60.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	reshape_helptest(width,height);
}

//鼠标控制相关计算
static void updateView(int state, int ox, int oy, int nx, int ny)
{
	//计算x,y的变化率
	int dx = ox - nx;
	int dy = ny - oy;

	switch(state)
	{
		case cameraROTATE:
			cameraR[0] += (dy * 180.0f) / 260.0f;
			cameraR[1] -= (dx * 180.0f) / 260.0f;
			cameraR[0] = cameraR[0] > 86.0f ? cameraR[0]=86.0f : cameraR[0] < -30.0f ? cameraR[0]=-30.0f : cameraR[0];
			cameraR[1] = cameraR[1] > 360.0f ? cameraR[1]-=360.0f : cameraR[1] < 0.0f ? cameraR[1]+=360.0f : cameraR[1];
			break;
		case cameraZOOM:
			cameraZoom += cameraZoomINT*0.05f;
			cameraZoom = cameraZoom > 1.5f ? cameraZoom=1.5 : cameraZoom < 0.66f ? cameraZoom=0.66f : cameraZoom;
			break;
		
		case scenesCONTROL://场景控制...
			if (_data)
			{
				if( cameraR[1] < 45 || cameraR[1] > 315)
				{
					testSence.bottole_x += (ny - oy) * 0.05;
					testSence.bottole_y += (nx - ox) * 0.05;
				}
				if( cameraR[1] >= 45 && cameraR[1] <= 135)
				{
					testSence.bottole_x += (nx - ox) * 0.05;
					testSence.bottole_y += (oy - ny) * 0.05;
				}
				if( cameraR[1] > 135 && cameraR[1] < 225)
				{
					testSence.bottole_x += (oy - ny) * 0.05;
					testSence.bottole_y += (ox - nx) * 0.05;
				}
				if( cameraR[1] >= 225 && cameraR[1] <= 315)
				{
					testSence.bottole_x += (ox - nx) * 0.05;
					testSence.bottole_y += (ny - oy) * 0.05;
				}
			}
			//
			if (_data)
			{
				updateData();
			}
			break;
		default:
			break;
	}

}


//display函数
void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glCullFace( GL_FRONT );//不知道为什么是front?
	testCamera.tommyGLcameraSTANDARD(16,0,0,0.0,0.0,0.0,cameraR[0],cameraR[1],cameraZoom);
	//glDisable( GL_CULL_FACE );
	glPushMatrix();
	//glRotatef(90,1.0,0.0,0.0);
	displaymode(&_displaymode);
	//在这里添加显示绘制代码
	testSence.main_display();

	//
	glPopMatrix();
	glPushMatrix();//
	glDisable(GL_LIGHTING);
	glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
	draw_helptext();//绘制信息..
	glEnable(GL_LIGHTING);
	glPopMatrix();

	SwapBuffers(hDC);			/* nop if singlebuffered */
}


//绘制帮助信息(..)
void reshape_helptest(float width,float height)
{
	tommyGL_LAB_INF.tommyGLTextInt(1.0,1.0,1.0,width,height);
	FPS_INF.tommyGLTextInt(1.0,0.8,0.12,width,win_height);
	tommyGL_LAB_Control.tommyGLTextInt(1.0,1.0,1.0,width,height);
	tommyGL_LAB_Prompt.tommyGLTextInt(1.0,0.66,0.28,width,win_height);

	//其他文字的reshape
	testSence.text_reshape(width,height);
}

void draw_helptext()
{
	if (win_width>=WINDOW_WIDTH*0.96)// && win_height>=WINDOW_HEIGHT*0.8
	{
		tommyGL_LAB_INF.tommyGL_FreeType(LAB_type,win_width-390,18);
	}
	tommyGL_LAB_INF.tommyGL_FreeType(LAB_copyright,6,win_height-8);
	FPS_INF.tommyGLfps(fpsinfo,5,18);
	tommyGL_LAB_Control.tommyGL_FreeType("控制台    (F1)\n开始实验 (F2)\n重设场景 (F3)\n侦听数据 (F4)\n显示模式 (F5)\n灯光材质 (F6)",win_width-86,win_height-104);//,6,16

	tommyGL_LAB_INF.tommyGL_FreeType(LAB_TEST_TITLE,6,win_height-26);
	tommyGL_LAB_INF.tommyGL_FreeType("左键:改变镜头角度\n右键:移动容器位置",win_width-230,win_height-28);

	if (!_data)
	{
		tommyGL_LAB_Prompt.tommyGL_FreeType("( 暂停! F2开始计算 )\n暂停状态下,鼠标不能移动容器！",6,win_height-80);
	}

	//其他文字
	testSence.text_display();
}

///这里添加其他代码.

//显示模式
void displaymode(int* selectmode)//显示模式切换
{
	switch(*selectmode)
	{
	case 1:
		glShadeModel (GL_FLAT);
		glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
		break;
	case 2:
		glShadeModel (GL_SMOOTH);
		glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
		break;
	case 3:
		glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
		break;
	default:
		*selectmode = 1;
		break;
	}
	_displaylight == true ? glEnable(GL_LIGHTING)://glEnable(GL_CULL_FACE)
		_displaylight == false ?glDisable(GL_LIGHTING),*selectmode = 3:_displaylight;
}

//打开控制台(待改进)
void showConsole(bool Console)
{
	HWND hwnd_cmd;
	HMENU hmenu_cmd;
	char consoleT[MAX_PATH];   

	if (Console == true)
	{
		AllocConsole();//初始化控制台
		GetConsoleTitle(consoleT, MAX_PATH);//获得窗口标题
		hwnd_cmd = ::FindWindow(NULL, consoleT);  //通过标题找到窗口句柄
		hmenu_cmd = ::GetSystemMenu(hwnd_cmd, FALSE);   //得到窗口菜单栏hmenu
		if (hwnd_cmd)
		{
			::RemoveMenu(hmenu_cmd, SC_CLOSE, MF_BYCOMMAND);//禁止窗口关闭按钮
			::SetWindowPos(hwnd_cmd,HWND_TOPMOST,100,100,680,480,NULL);
		}
		freopen("CONOUT$", "w", stdout);//重新指定stdio
		freopen("CONIN$", "r", stdin);
		freopen("CONOUT$", "w", stderr);
		SetConsoleTitle(CONSOLE_TITLE);
		printf("(tommy的)孵化机Opengl实验窗口02型~beta~(GDUT_3111000704)\nALL Rights Reserve! 权利保留 2013");
		printf("\n\n操作方法:\nF1 关闭控制台\nF2 开始\\暂停实验\nF4 侦听数据\n");
		printf("\n鼠标左键:改变镜头角度\n鼠标右键:移动容器位置\n");
		if (_showdatalisten)
		{
			_showConsole_datalisten = !_showConsole_datalisten;//
		}
	} 
	else
	{
		fclose(stdout);
		fclose(stdin);
		fclose(stderr);
		FreeConsole();
	}
}

//数据更新
void updateData()
{
	testSence.data_update();
}

//数据输出
void DataTrace()
{
	testSence.data_trace();
	cout<<"tmp_x = "<<tmp_x;
}


////////////////////////////////////显示窗口的生成//////////////////////////////////////////////////////
//事件响应
LONG WINAPI
WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{ 
	static PAINTSTRUCT ps;
	static GLboolean left  = GL_FALSE;	/* left button currently down? */
	static GLboolean right = GL_FALSE;	/* right button currently down? */
	static GLuint    state   = 0;	    /* mouse state flag */
	static int omx, omy, mx, my;

	switch(uMsg) {
	case WM_PAINT:
		/*display();*/
		BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		return 0;
		break;

	//窗口大小改变事件
	case WM_SIZE:
		win_width = LOWORD(lParam);
		win_height = HIWORD(lParam);
		reshape(LOWORD(lParam), HIWORD(lParam));
		PostMessage(hWnd, WM_PAINT, 0, 0);
		return 0;
		break;

	case WM_KEYDOWN:
		switch (wParam) 
		{
			//键盘事件
			//case 104:       /* 'H' key */
			//	dhelp = !dhelp;  /* display help*/
			//	break;
		    case VK_F1://F1
				//打开控制台
				_showConsole = !_showConsole;
				showConsole(_showConsole);
				if (!_showConsole)
				{
					KillTimer(hWnd, TIMER_quarter_SEC) ;//如果console窗口关闭,则数据侦听的关闭时间器
				}
				break;
			case VK_F2:
				_data = !_data;
				if (_data)
				{
					SetTimer(hWnd, TIMER_25MSEC, 25, NULL) ;
				}
				else
					KillTimer(hWnd, TIMER_25MSEC) ;
				break;
			case VK_F3:
				if (_data)
				{
					_data = !_data;
					KillTimer(hWnd, TIMER_25MSEC) ;
				}
				testSence.init_display();
				break;
			case VK_F4:
				_showdatalisten = !_showdatalisten;
				if (_showConsole)
				{
					_showConsole_datalisten =!_showConsole_datalisten;
					if (_showConsole_datalisten)
					{
						printf("\n开始侦听数据! 主窗口按F4停止\n");
						SetTimer(hWnd, TIMER_quarter_SEC, 250, NULL) ;
					}
					else
					{
						printf("停止数据侦听!\n");
						KillTimer(hWnd, TIMER_quarter_SEC) ;
					}
				}
				break;
			case VK_F5:
				_displaymode++;
				//切换显示模式
				break;
			case VK_F6:
				_displaylight = !_displaylight;
				_displaylight == true ? _displaymode = _displaymode_tmp:
				_displaylight == false ? _displaymode_tmp = _displaymode :_displaylight;//controlBar_l="打开"
				break;
		    case 0:
				break;
		    default:
				break;
		}
		return 0;
		break;

	case WM_LBUTTONDOWN:
	case WM_RBUTTONDOWN:
		/* if we don't set the capture we won't get mouse move
		messages when the mouse moves outside the window. */
		SetCapture(hWnd);
		mx = LOWORD(lParam);
		my = HIWORD(lParam);
		//if (uMsg == WM_MOUSEHWHEEL)//鼠标滚轮 state=缩放
		//	state |= cameraZOOM;
		if (uMsg == WM_LBUTTONDOWN)//鼠标左键按下 state=旋转
			state |= cameraROTATE;
		if (uMsg == WM_RBUTTONDOWN)//鼠标右键按下 state=
			state |= scenesCONTROL;
		return 0;
		break;

	case WM_LBUTTONUP:
	case WM_RBUTTONUP:
		/* remember to release the capture when we are finished. */
		ReleaseCapture();
		state = 0;
		return 0;
		break;

	//鼠标滚轮事件
	case WM_MOUSEHWHEEL:
		cameraZoomINT = GET_WHEEL_DELTA_WPARAM(wParam);
		cameraZoomINT = cameraZoomINT/120;
		updateView(cameraZOOM,omx,omy,mx,my);
		cameraZoomINT = 0;
		return 0;
		break;

	//鼠标移动事件
	case WM_MOUSEMOVE:
		if (state) {
			omx = mx;
			omy = my;
			mx = LOWORD(lParam);
			my = HIWORD(lParam);
			/* Win32 is pretty braindead about the x, y position that
			it returns when the mouse is off the left or top edge
			of the window (due to them being unsigned). therefore,
			roll the Win32's 0..2^16 pointer co-ord range to the
			more amenable (and useful) 0..+/-2^15. */
			//窗口内的坐标和窗口外的坐标不一样，为了避免出现错误显示的情况，进行如下设置
			if(mx & 1 << 15) mx -= (1 << 16);
			if(my & 1 << 15) my -= (1 << 16);
			updateView(state,omx,omy,mx,my);
			PostMessage(hWnd, WM_PAINT, 0, 0);
		}
		return 0;
		break;

	case WM_PALETTECHANGED:
		if (hWnd == (HWND)wParam)
			break;
		/* fall through to WM_QUERYNEWPALETTE */

	case WM_QUERYNEWPALETTE:
		if (hPalette) {
			UnrealizeObject(hPalette);
			SelectPalette(hDC, hPalette, FALSE);
			RealizePalette(hDC);
			return TRUE;
		}
		return FALSE;
		break;

	case WM_CLOSE:
		PostQuitMessage(0);
		return 0;
		break;

	/*获得窗口大小改变*/
	case WM_GETMINMAXINFO:
		MINMAXINFO *mminfo;  
		mminfo=(PMINMAXINFO)lParam;  //窗口尺寸最小值
		mminfo->ptMinTrackSize.x=640;  
		mminfo->ptMinTrackSize.y=480;  
		break;

	case WM_TIMER:
		switch (wParam)
		{
		case TIMER_25MSEC:
			updateData();
			//每25毫秒的处理
			break;
		case TIMER_quarter_SEC:
			DataTrace();
			//每分钟一次的处理
			break;
		default:
			break;
		}

		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam); 
} 


//创建DC
HWND
CreateOpenGLWindow(char* title, int x, int y, int width, int height, 
				   BYTE type, DWORD flags)
{
	int         n, pf;
	HWND        hWnd;
	WNDCLASS    wc;
	LOGPALETTE* lpPal;
	PIXELFORMATDESCRIPTOR pfd;
	static HINSTANCE hInstance = 0;

	/* only register the window class once - use hInstance as a flag. */
	if (!hInstance) {
		hInstance = GetModuleHandle(NULL);
		wc.style         = CS_OWNDC;
		wc.lpfnWndProc   = (WNDPROC)WindowProc;
		wc.cbClsExtra    = 0;
		wc.cbWndExtra    = 0;
		wc.hInstance     = hInstance;
		wc.hIcon         = LoadIcon(NULL, IDI_WINLOGO);
		wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
		wc.hbrBackground = NULL;
		wc.lpszMenuName  = NULL;
		wc.lpszClassName = "OpenGL";

		if (!RegisterClass(&wc)) {
			MessageBox(NULL, "RegisterClass() failed:  "
				"Cannot register window class.", "Error", MB_OK);
			return NULL;
		}
	}

	//创建窗口
	//WS_MAXIMIZEBOX|WS_MINIMIZEBOX|WS_SYSMENU //不可拖动改变大小的风格
	//WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN |
	hWnd = CreateWindow("OpenGL", title, WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN ,
		x, y, width, height, NULL, NULL, hInstance, NULL);

	//创建失败！
	if (hWnd == NULL) {
		MessageBox(NULL, "CreateWindow() failed:  Cannot create a window.",
			"Error", MB_OK);
		return NULL;
	}

	hDC = GetDC(hWnd);

	/* there is no guarantee that the contents of the stack that become
	the pfd are zeroed, therefore _make sure_ to clear these bits. */
	memset(&pfd, 0, sizeof(pfd));
	pfd.nSize        = sizeof(pfd);
	pfd.nVersion     = 1;
	pfd.dwFlags      = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | flags;
	pfd.iPixelType   = type;
	pfd.cDepthBits   = 32;
	pfd.cColorBits   = 32;

	pf = ChoosePixelFormat(hDC, &pfd);
	if (pf == 0) {
		MessageBox(NULL, "ChoosePixelFormat() failed:  "
			"Cannot find a suitable pixel format.", "Error", MB_OK); 
		return 0;
	} 

	if (SetPixelFormat(hDC, pf, &pfd) == FALSE) {
		MessageBox(NULL, "SetPixelFormat() failed:  "
			"Cannot set format specified.", "Error", MB_OK);
		return 0;
	} 

	DescribePixelFormat(hDC, pf, sizeof(PIXELFORMATDESCRIPTOR), &pfd);

	if (pfd.dwFlags & PFD_NEED_PALETTE ||
		pfd.iPixelType == PFD_TYPE_COLORINDEX) {

			n = 1 << pfd.cColorBits;
			if (n > 256) n = 256;

			lpPal = (LOGPALETTE*)malloc(sizeof(LOGPALETTE) +
				sizeof(PALETTEENTRY) * n);
			memset(lpPal, 0, sizeof(LOGPALETTE) + sizeof(PALETTEENTRY) * n);
			lpPal->palVersion = 0x300;
			lpPal->palNumEntries = n;

			GetSystemPaletteEntries(hDC, 0, n, &lpPal->palPalEntry[0]);

			/* if the pixel type is RGBA, then we want to make an RGB ramp,
			otherwise (color index) set individual colors. */
			if (pfd.iPixelType == PFD_TYPE_RGBA) {
				int redMask = (1 << pfd.cRedBits) - 1;
				int greenMask = (1 << pfd.cGreenBits) - 1;
				int blueMask = (1 << pfd.cBlueBits) - 1;
				int i;

				/* fill in the entries with an RGB color ramp. */
				for (i = 0; i < n; ++i) {
					lpPal->palPalEntry[i].peRed = 
						(((i >> pfd.cRedShift)   & redMask)   * 255) / redMask;
					lpPal->palPalEntry[i].peGreen = 
						(((i >> pfd.cGreenShift) & greenMask) * 255) / greenMask;
					lpPal->palPalEntry[i].peBlue = 
						(((i >> pfd.cBlueShift)  & blueMask)  * 255) / blueMask;
					lpPal->palPalEntry[i].peFlags = 0;
				}
			} else {
				lpPal->palPalEntry[0].peRed = 0;
				lpPal->palPalEntry[0].peGreen = 0;
				lpPal->palPalEntry[0].peBlue = 0;
				lpPal->palPalEntry[0].peFlags = PC_NOCOLLAPSE;
				lpPal->palPalEntry[1].peRed = 255;
				lpPal->palPalEntry[1].peGreen = 0;
				lpPal->palPalEntry[1].peBlue = 0;
				lpPal->palPalEntry[1].peFlags = PC_NOCOLLAPSE;
				lpPal->palPalEntry[2].peRed = 0;
				lpPal->palPalEntry[2].peGreen = 255;
				lpPal->palPalEntry[2].peBlue = 0;
				lpPal->palPalEntry[2].peFlags = PC_NOCOLLAPSE;
				lpPal->palPalEntry[3].peRed = 0;
				lpPal->palPalEntry[3].peGreen = 0;
				lpPal->palPalEntry[3].peBlue = 255;
				lpPal->palPalEntry[3].peFlags = PC_NOCOLLAPSE;
			}

			hPalette = CreatePalette(lpPal);
			if (hPalette) {
				SelectPalette(hDC, hPalette, FALSE);
				RealizePalette(hDC);
			}

			free(lpPal);
		}

		ReleaseDC(hWnd, hDC);

		return hWnd;
}    

int WINAPI WinMain(HINSTANCE hCurrentInst, HINSTANCE hPreviousInst,
				   LPSTR lpszCmdLine, int nCmdShow)
{
	HGLRC hRC;				/* opengl context */
	HWND  hWnd;				/* window */
	MSG   msg;				/* message */
	DWORD buffer = PFD_DOUBLEBUFFER;	/* buffering type */
	BYTE  color  = PFD_TYPE_RGBA;	/* color type */

	if (strstr(lpszCmdLine, "-sb")) {
		buffer = 0;
	} 
	if (strstr(lpszCmdLine, "-ci")) {
		color = PFD_TYPE_COLORINDEX;
	} 
	if (strstr(lpszCmdLine, "-h")) {
		MessageBox(NULL, "mouse [-ci] [-sb]\n"
			"  -sb   single buffered\n"
			"  -ci   color index\n",
			"Usage help", MB_ICONINFORMATION);
		exit(0);
	}
	//运行CreateOpenGLWindow
	
// 	freopen("conin$", "r+t", stdin);   
// 	freopen("conout$", "w+t", stdout); 
// 	freopen("conout$", "w+t", stderr);  

	hWnd = CreateOpenGLWindow(WINDOW_TITLE, 100, 100, WINDOW_WIDTH, WINDOW_HEIGHT, color, buffer);
	if (hWnd == NULL)
		exit(1);

	hDC = GetDC(hWnd);
	hRC = wglCreateContext(hDC);
	wglMakeCurrent(hDC, hRC);

	/* tommmy init*/
	tommy_Init();

	ShowWindow(hWnd, nCmdShow);	

	while(1)
	{
		if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))
		{ 
			/* test if this is a quit*/
			if (msg.message == WM_QUIT)
				break;

			/* translate any accelerator keys*/
			TranslateMessage(&msg);

			/* send the message to the window proc*/
			DispatchMessage(&msg);
		} 

		/* main function loop*/
		tommy_Main();
	}
	
	/* shut down*/
	tommy_Shutdown();

	wglMakeCurrent(NULL, NULL);
	ReleaseDC(hWnd, hDC);
	wglDeleteContext(hRC);
	DestroyWindow(hWnd);
	if (hPalette)
		DeleteObject(hPalette);

	return msg.wParam;
}