//tommy的opengGL文字类
#include "tommyGLtext.h"

tommyGLtext::tommyGLtext(void)
	: R(1.0),G(1.0),B(1.0),w_width(100),w_height(100)
{
}

tommyGLtext::~tommyGLtext(void)
{
}

// tommg的Opengl字体初始化(设置字体颜色以及窗口大小)
void tommyGLtext::tommyGLTextInt(GLfloat Red, GLfloat Green, GLfloat Blue, float window_width,float window_height)
{
	R = Red;
	G = Green;
	B = Blue;
	w_width = window_width;
	w_height = window_height;
}

// tommg的Opengl英文字符(tommyGLTextEng(x,y,字符,glut字体))
void tommyGLtext::tommyGLTextEng(int x, int y, char* s,void* glutfont)
{
	//glDisable(GL_LIGHTING);
	int lines;
	char* p;
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, w_width, 0, w_height);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glColor3f(R,G,B);
	glRasterPos2i(x,y);
	for(p = s, lines = 0; *p; p++) {
		if (*p == '\n')
		{
			lines++;
			glRasterPos2i(x, y-(lines*18));
		}
		glutBitmapCharacter(glutfont, *p);
	}
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	//glEnable(GL_LIGHTING);
}

// tommg的Opengl帧速(tommyGLfps(x,y))
void tommyGLtext::tommyGLfps(char* s,int x, int y)//,void* glutfont
{
	static unsigned long lastTime = 0;
	static int hitCount = 0;
	static double fps = 0.0;
	double thisTime;

	if(lastTime == 0 )
		lastTime = GetTickCount();

	thisTime = GetTickCount();

	if( hitCount == 100 )
	{
		fps = hitCount / ((thisTime - lastTime)/1000);
		hitCount = 0;
		lastTime = thisTime;
	}
	else
		hitCount++;

	sprintf(s,"FPS:%.2f", fps);

	tommyGL_FreeType(s,x,y);
	
	//tommyGLTextEng(x,y,s,GLUT_BITMAP_HELVETICA_18);
}

// 使用wglUseFontBitmaps的Opengl中英字符显示de初始化(大小,编码,字体)
void tommyGLtext::tommyGLTextFontBitmapsInt(int size, int charset, const char* face)
{
	HFONT hFont = CreateFontA(size, 0, 0, 0, FW_MEDIUM, 0, 0, 0,
		charset, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, face);
	HFONT hOldFont = (HFONT)SelectObject(wglGetCurrentDC(), hFont);
	DeleteObject(hOldFont);
	TestSuper = NULL;
}

// 使用wglUseFontBitmaps的Opengl中英字符显示(x,y,字符)//使用前必须用tommyGLTextSuperInt初始化
void tommyGLtext::tommyGLTextFontBitmaps(int x, int y,const char* s)
{
	//glDisable(GL_LIGHTING);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, w_width, 0, w_height);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glColor3f(R,G,B);
	glRasterPos2i(x,y);
	//主体
	int i;
	if (TestSuper == NULL||TestSuper != s)
	{
		TestSuper = s;
		//HDC hDC = wglGetCurrentDC();
		TestSuper_list = glGenLists(1);
		 /*计算字符的个数
		 如果是双字节字符的（比如中文字符），两个字节才算一个字符
		 否则一个字节算一个字符*/
		TestSuper_len = 0;
		for(int i=0; s[i]!='\0'; ++i)
		{
			if( IsDBCSLeadByte(s[i]) )
				++i;
			++TestSuper_len;
		}
	}
	wchar_t* wstring;
	//char a = wstring[TestSuper_len];
	// 将混合字符转化为宽字符
	wstring = (wchar_t*)malloc((TestSuper_len+1) * sizeof(wchar_t));
	MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, s, -1, wstring, TestSuper_len);
	wstring[TestSuper_len] = L'\0';

	// 逐个输出字符
	for(i=0; i<TestSuper_len; ++i)
	{
		wglUseFontBitmapsW(wglGetCurrentDC(), wstring[i], 1, TestSuper_len);
		glCallList(TestSuper_len);
	}

	//主体
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	//glEnable(GL_LIGHTING);

	// 回收所有临时资源
	free(wstring);
	//glDeleteLists(list, 1);
}


/*
使用freetype的Opengl字符显示
*/

void tommyGLtext::tommyGL_FreeType_load(const char* fontfile_name, int tex_w, int tex_h)
{
	TCHAR szBuf[MAX_PATH];
	TCHAR szFile[MAX_PATH];  

	SHGetSpecialFolderPath(NULL , szBuf , CSIDL_FONTS , FALSE);//获得系统字体文件的路径
	PathAddBackslash(szBuf);//在路径后加"\"
	char* font_path = szBuf;
	CString path_string(font_path);//CString path_string;
	path_string.Replace("\\","\\\\");
	path_string += _T("msyh.ttf");
	font_path = (LPSTR)(LPCTSTR)path_string;

	FT_Library library;
	if (FT_Init_FreeType( &library) ) 
		exit(0);
 	if (FT_New_Face( library, font_path, 0, &m_FT_Face )) 
	{
		font_path = szBuf;
		CString path_string2(font_path);
		path_string2.Replace("\\","\\\\");
		path_string2 += _T("msyh.ttc");
		font_path = (LPSTR)(LPCTSTR)path_string2;
		FT_New_Face( library, font_path, 0, &m_FT_Face );
 		//exit(0);
	}
	FT_Select_Charmap(m_FT_Face, FT_ENCODING_UNICODE);
	m_w = tex_w ; m_h = tex_h;
	m_FT_Face->num_fixed_sizes;
	//MessageBox(NULL,m_FT_Face->family_name,"测试输出",MB_ICONASTERISK);
	//大小要乘64.这是规定。照做就可以了。
	//FT_Set_Char_Size( m_FT_Face , 0 , m_w << 6, 96, 96);
	FT_Set_Pixel_Sizes(m_FT_Face,m_w, m_h);
	
}

GLuint tommyGLtext::loadChar(wchar_t ch)
{
	if(g_TexID[ch].m_texID)
		return g_TexID[ch].m_texID;
	if(FT_Load_Char(m_FT_Face, ch, /*FT_LOAD_RENDER|*/FT_LOAD_FORCE_AUTOHINT|
	(TRUE ? FT_LOAD_TARGET_NORMAL : FT_LOAD_MONOCHROME | FT_LOAD_TARGET_MONO) )   )
	{
	return 0;
	}
	/*if(FT_Load_Glyph( m_FT_Face, FT_Get_Char_Index( m_FT_Face, ch ), FT_LOAD_FORCE_AUTOHINT ))
	throw std::runtime_error("FT_Load_Glyph failed");*/
	tGL_FreeTypeTextures& charTex = g_TexID[ch];
 
	//得到字模
	FT_Glyph glyph;
	if(FT_Get_Glyph( m_FT_Face->glyph, &glyph ))
	return 0;
	//转化成位图
	FT_Render_Glyph( m_FT_Face->glyph,   FT_RENDER_MODE_LCD );//FT_RENDER_MODE_NORMAL  ); 
	FT_Glyph_To_Bitmap( &glyph, ft_render_mode_normal, 0, 1 );
	FT_BitmapGlyph bitmap_glyph = (FT_BitmapGlyph)glyph;
	//取道位图数据
	FT_Bitmap& bitmap=bitmap_glyph->bitmap;
	//把位图数据拷贝自己定义的数据区里.这样旧可以画到需要的东西上面了。
	int width  =  bitmap.width;
	int height =  bitmap.rows;
	m_FT_Face->size->metrics.y_ppem;
	m_FT_Face->glyph->metrics.horiAdvance;

	charTex.m_Width = width;
	charTex.m_Height = height;
	charTex.m_adv_x = m_FT_Face->glyph->advance.x / 64.0f;
	charTex.m_adv_y = m_FT_Face->size->metrics.y_ppem; //m_FT_Face->glyph->metrics.horiBearingY / 64.0f;
	charTex.m_delta_x = (float)bitmap_glyph->left;
	charTex.m_delta_y = (float)bitmap_glyph->top - height;
	glGenTextures(1,&charTex.m_texID);
	glBindTexture(GL_TEXTURE_2D,charTex.m_texID);
	char* pBuf = new char[width * height * 4];
	for(int j=0; j  < height ; j++)
	{
	for(int i=0; i < width; i++)
	{
	unsigned char _vl =  (i>=bitmap.width || j>=bitmap.rows) ? 0 : bitmap.buffer[i + bitmap.width*j];
	pBuf[(4*i + (height - j - 1) * width * 4)  ] = 0xFF;
	pBuf[(4*i + (height - j - 1) * width * 4)+1] = 0xFF;
	pBuf[(4*i + (height - j - 1) * width * 4)+2] = 0xFF;
	pBuf[(4*i + (height - j - 1) * width * 4)+3] = _vl;
	}
	}
	glTexImage2D( GL_TEXTURE_2D,0,GL_RGBA,width, height,0,GL_RGBA,GL_UNSIGNED_BYTE,pBuf);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
	glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
	glTexEnvi(GL_TEXTURE_2D,GL_TEXTURE_ENV_MODE,GL_REPLACE);
	/*gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, width, height, GL_RGBA, GL_UNSIGNED_BYTE, pBuf);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
	glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
	glTexEnvi(GL_TEXTURE_2D,GL_TEXTURE_ENV_MODE,GL_REPLACE);*/
	delete[] pBuf;
	return charTex.m_chaID;
}

//ANSI To Unicode
LPWSTR tommyGLtext::AnsiToUnicode(LPCSTR lpcstr)
{
	LPWSTR Pwstr;
	int  i;
	i=MultiByteToWideChar(CP_ACP,0,lpcstr,-1,NULL,0);
	Pwstr=new WCHAR[i]; 
	MultiByteToWideChar(CP_ACP,0,lpcstr,-1,Pwstr,i);
	return (Pwstr);
} 

void tommyGLtext::tommyGL_FreeType(const char* s,int x , int y)
{
	glMatrixMode(GL_PROJECTION);
	glEnable ( GL_TEXTURE_2D );
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, w_width, w_height,0 );
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glColor3f(R,G,B);
	glRasterPos2i(x,y);
	//主体
	wchar_t *_strText = AnsiToUnicode(s);//ANSI To Unicode
	int sx = x;
	int sy = y;
	int maxH = w_height;
	size_t nLen = wcslen(_strText);

	for(int i = 0 ; i <nLen ; i ++)
	{
		if(_strText[i] =='\n')
		{
			sx = x ; sy += m_h +6;
			continue;
		}
		//loadChar(_strText[i]);
		loadChar(_strText[i]);
		tGL_FreeTypeTextures* pCharTex = &g_TexID[_strText[i]];
		glBindTexture(GL_TEXTURE_2D,pCharTex->m_texID);
		glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
		glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
		//glDisable(GL_TEXTURE_2D);
		int w = pCharTex->m_Width;
		int h = pCharTex->m_Height;
		int ch_x = sx + pCharTex->m_delta_x;
		int ch_y = sy - h - pCharTex->m_delta_y;
		if(maxH < h) maxH = h;
		glBegin ( GL_QUADS );//设置纹理贴图的映射坐标
		{
			glTexCoord2f(0.0f, 1.0f); glVertex3f(ch_x      , ch_y    ,  1.0f);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(ch_x +  w, ch_y    ,  1.0f);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(ch_x +  w, ch_y + h,  1.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(ch_x     , ch_y + h,  1.0f);
		}
		glEnd();
		sx += pCharTex->m_adv_x;
		if(sx > x + w_width)
		{
			sx = x ; sy += maxH + 12;
		}
	}
	free(_strText);//释放内存，不然占用的内存会越来越大
	//主体
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glDisable ( GL_TEXTURE_2D );
	glMatrixMode(GL_MODELVIEW);
}