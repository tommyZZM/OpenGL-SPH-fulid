#include <stdio.h>
#include <math.h>
#include <iostream>
//#include <afxfontcombobox.h>
#include <windows.h>		
#include <string.h>
#include <shlobj.h>
#include <atlstr.h>
using namespace std;

//opengl
#include <GL/gl.h>			
#include <GL/glu.h>			
#include <GL/glut.h>

//freetype
#include <ft2build.h>
#include <freetype/freetype.h>
#include <freetype/ftglyph.h>
#include <freetype/ftoutln.h>
#include <freetype/fttrigon.h>

#define 微软雅黑 "msyh.ttf"
#define 黑体 "simhei.ttf"

#pragma once
class tommyGLtext
{
public:
	tommyGLtext(void);
	~tommyGLtext(void);

	GLfloat R;
	GLfloat G;
	GLfloat B;

	float w_width;
	float w_height;

	// tommg的Opengl英文字符初始化(设置字体颜色以及窗口大小)(效率低..)
	void tommyGLTextInt(GLfloat Red, GLfloat Green, GLfloat Blue, float window_width,float window_height);

	// tommg的Opengl英文字符(tommyGLTestEng(x,y,字符,glut字体))(效率低..)
	void tommyGLTextEng(int x, int y, char* s,void* font);

	///////////////////////////////wglUseFontBitmaps//////////////////
	
	// 使用wglUseFontBitmaps的Opengl中英字符显示de初始化(大小,编码,字体)(效率极低..)
	void tommyGLTextFontBitmapsInt(int size, int charset, const char* face);

	// 使用wglUseFontBitmaps的Opengl中英字符显示(x,y,字符)//使用前必须用tommyGLTestSuperInt初始化(PS:效率极低..慎用.)
	void tommyGLTextFontBitmaps(int x, int y,const char* s);
	
	///////////////////////////////FreeType2//////////////////

	//class tGL_FreeTypeLib{};

	/*使用freetype的Opengl文字,初始化字体和字体样式(字体文件名称,窗口宽,窗口高)*/
	void tommyGL_FreeType_load(const char* fontfile_name, int tex_w, int tex_h);

	/*使用freetype的Opengl文字*/
	void tommyGL_FreeType(const char* s,int x , int y);

	// tommg的Opengl帧速(tommyGLfps(x,y))
	void tommyGLfps(char* s,int x, int y);

private:
	//wglUseFontBitmaps
	const char* TestSuper;
	int TestSuper_len;
	GLuint TestSuper_list;
	///////////////////////////////FreeType2//////////////////
	FT_Library m_FT2Lib;
	FT_Face    m_FT_Face;

	int   m_w;
	int   m_h;
	GLuint loadChar(wchar_t ch);

	//tGL_FreeTypeTextures* getTextChar(wchar_t ch);
	LPWSTR AnsiToUnicode(LPCSTR lpcstr);

	char* font_file;

	struct tGL_FreeTypeTextures
	{
		GLuint  m_texID;
		wchar_t m_chaID;
		int     m_Width;
		int     m_Height;
		int     m_adv_x;
		int     m_adv_y;
		int     m_delta_x;
		int     m_delta_y;
	public:
		tGL_FreeTypeTextures()
		{
			m_texID  = 0;
			m_chaID  = 0;
			m_Width  = 0;
			m_Height = 0;
		}
	};
	tGL_FreeTypeTextures g_TexID[50000];
};

