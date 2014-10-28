//����(tommy��)������Openglʵ�鴰��ģ��02��~~(GDUT_3111000704)
//ALL Rights Reserve! Ȩ������ 2013
//�����о�ʹ��.

//version 2013 [0000000] [������дʵ����]

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
	glEnable(GL_DEPTH_TEST);//����Ȳ���
	glEnable(GL_LIGHTING);//�򿪵ƹ�
	glClearColor (0.26, 0.26, 0.26, 0.0);//���ñ�����ɫ
	glShadeModel (GL_FLAT);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	win_height = WINDOW_HEIGHT;
	win_width = WINDOW_WIDTH;
	_showConsole = false;
	_showdatalisten = false;
	_data = false;
	_displaymode=1;
	_displaymode_tmp = _displaymode;
	_displaylight = false;//controlBar_l="�ر�";
	cameraR[0]=30;//x
	cameraR[1]=60;//y
	cameraZoom = 1.0;//����ֵ
	testLight.tommyGLlightSTANDARD(-49.0f,49.0f,66.0f);
	tommyGL_LAB_Control.tommyGL_FreeType_load(΢���ź�,13,13);
	tommyGL_LAB_Prompt.tommyGL_FreeType_load(΢���ź�,16,16);//��ʾ
	tommyGL_LAB_INF.tommyGL_FreeType_load(΢���ź�,13,13);
	FPS_INF.tommyGL_FreeType_load("msyh.ttf",16,16);
	

	//������ʼ��
	testSence.init_display();
	tmp_x = 0;
	tmp_y = 0;

	return (1);
}


int tommy_Main(void)
{
	//Main����
	display();
	
	return (1);
}

int tommy_Shutdown(void)
{
	//��������ӳ���رմ������

	return (1);
}


//reshape������
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

//��������ؼ���
static void updateView(int state, int ox, int oy, int nx, int ny)
{
	//����x,y�ı仯��
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
		
		case scenesCONTROL://��������...
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


//display����
void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glCullFace( GL_FRONT );//��֪��Ϊʲô��front?
	testCamera.tommyGLcameraSTANDARD(16,0,0,0.0,0.0,0.0,cameraR[0],cameraR[1],cameraZoom);
	//glDisable( GL_CULL_FACE );
	glPushMatrix();
	//glRotatef(90,1.0,0.0,0.0);
	displaymode(&_displaymode);
	//�����������ʾ���ƴ���
	testSence.main_display();

	//
	glPopMatrix();
	glPushMatrix();//
	glDisable(GL_LIGHTING);
	glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
	draw_helptext();//������Ϣ..
	glEnable(GL_LIGHTING);
	glPopMatrix();

	SwapBuffers(hDC);			/* nop if singlebuffered */
}


//���ư�����Ϣ(..)
void reshape_helptest(float width,float height)
{
	tommyGL_LAB_INF.tommyGLTextInt(1.0,1.0,1.0,width,height);
	FPS_INF.tommyGLTextInt(1.0,0.8,0.12,width,win_height);
	tommyGL_LAB_Control.tommyGLTextInt(1.0,1.0,1.0,width,height);
	tommyGL_LAB_Prompt.tommyGLTextInt(1.0,0.66,0.28,width,win_height);

	//�������ֵ�reshape
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
	tommyGL_LAB_Control.tommyGL_FreeType("����̨    (F1)\n��ʼʵ�� (F2)\n���賡�� (F3)\n�������� (F4)\n��ʾģʽ (F5)\n�ƹ���� (F6)",win_width-86,win_height-104);//,6,16

	tommyGL_LAB_INF.tommyGL_FreeType(LAB_TEST_TITLE,6,win_height-26);
	tommyGL_LAB_INF.tommyGL_FreeType("���:�ı侵ͷ�Ƕ�\n�Ҽ�:�ƶ�����λ��",win_width-230,win_height-28);

	if (!_data)
	{
		tommyGL_LAB_Prompt.tommyGL_FreeType("( ��ͣ! F2��ʼ���� )\n��ͣ״̬��,��겻���ƶ�������",6,win_height-80);
	}

	//��������
	testSence.text_display();
}

///���������������.

//��ʾģʽ
void displaymode(int* selectmode)//��ʾģʽ�л�
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

//�򿪿���̨(���Ľ�)
void showConsole(bool Console)
{
	HWND hwnd_cmd;
	HMENU hmenu_cmd;
	char consoleT[MAX_PATH];   

	if (Console == true)
	{
		AllocConsole();//��ʼ������̨
		GetConsoleTitle(consoleT, MAX_PATH);//��ô��ڱ���
		hwnd_cmd = ::FindWindow(NULL, consoleT);  //ͨ�������ҵ����ھ��
		hmenu_cmd = ::GetSystemMenu(hwnd_cmd, FALSE);   //�õ����ڲ˵���hmenu
		if (hwnd_cmd)
		{
			::RemoveMenu(hmenu_cmd, SC_CLOSE, MF_BYCOMMAND);//��ֹ���ڹرհ�ť
			::SetWindowPos(hwnd_cmd,HWND_TOPMOST,100,100,680,480,NULL);
		}
		freopen("CONOUT$", "w", stdout);//����ָ��stdio
		freopen("CONIN$", "r", stdin);
		freopen("CONOUT$", "w", stderr);
		SetConsoleTitle(CONSOLE_TITLE);
		printf("(tommy��)������Openglʵ�鴰��02��~beta~(GDUT_3111000704)\nALL Rights Reserve! Ȩ������ 2013");
		printf("\n\n��������:\nF1 �رտ���̨\nF2 ��ʼ\\��ͣʵ��\nF4 ��������\n");
		printf("\n������:�ı侵ͷ�Ƕ�\n����Ҽ�:�ƶ�����λ��\n");
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

//���ݸ���
void updateData()
{
	testSence.data_update();
}

//�������
void DataTrace()
{
	testSence.data_trace();
	cout<<"tmp_x = "<<tmp_x;
}


////////////////////////////////////��ʾ���ڵ�����//////////////////////////////////////////////////////
//�¼���Ӧ
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

	//���ڴ�С�ı��¼�
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
			//�����¼�
			//case 104:       /* 'H' key */
			//	dhelp = !dhelp;  /* display help*/
			//	break;
		    case VK_F1://F1
				//�򿪿���̨
				_showConsole = !_showConsole;
				showConsole(_showConsole);
				if (!_showConsole)
				{
					KillTimer(hWnd, TIMER_quarter_SEC) ;//���console���ڹر�,�����������Ĺر�ʱ����
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
						printf("\n��ʼ��������! �����ڰ�F4ֹͣ\n");
						SetTimer(hWnd, TIMER_quarter_SEC, 250, NULL) ;
					}
					else
					{
						printf("ֹͣ��������!\n");
						KillTimer(hWnd, TIMER_quarter_SEC) ;
					}
				}
				break;
			case VK_F5:
				_displaymode++;
				//�л���ʾģʽ
				break;
			case VK_F6:
				_displaylight = !_displaylight;
				_displaylight == true ? _displaymode = _displaymode_tmp:
				_displaylight == false ? _displaymode_tmp = _displaymode :_displaylight;//controlBar_l="��"
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
		//if (uMsg == WM_MOUSEHWHEEL)//������ state=����
		//	state |= cameraZOOM;
		if (uMsg == WM_LBUTTONDOWN)//���������� state=��ת
			state |= cameraROTATE;
		if (uMsg == WM_RBUTTONDOWN)//����Ҽ����� state=
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

	//�������¼�
	case WM_MOUSEHWHEEL:
		cameraZoomINT = GET_WHEEL_DELTA_WPARAM(wParam);
		cameraZoomINT = cameraZoomINT/120;
		updateView(cameraZOOM,omx,omy,mx,my);
		cameraZoomINT = 0;
		return 0;
		break;

	//����ƶ��¼�
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
			//�����ڵ�����ʹ���������겻һ����Ϊ�˱�����ִ�����ʾ�������������������
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

	/*��ô��ڴ�С�ı�*/
	case WM_GETMINMAXINFO:
		MINMAXINFO *mminfo;  
		mminfo=(PMINMAXINFO)lParam;  //���ڳߴ���Сֵ
		mminfo->ptMinTrackSize.x=640;  
		mminfo->ptMinTrackSize.y=480;  
		break;

	case WM_TIMER:
		switch (wParam)
		{
		case TIMER_25MSEC:
			updateData();
			//ÿ25����Ĵ���
			break;
		case TIMER_quarter_SEC:
			DataTrace();
			//ÿ����һ�εĴ���
			break;
		default:
			break;
		}

		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam); 
} 


//����DC
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

	//��������
	//WS_MAXIMIZEBOX|WS_MINIMIZEBOX|WS_SYSMENU //�����϶��ı��С�ķ��
	//WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN |
	hWnd = CreateWindow("OpenGL", title, WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN ,
		x, y, width, height, NULL, NULL, hInstance, NULL);

	//����ʧ�ܣ�
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
	//����CreateOpenGLWindow
	
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