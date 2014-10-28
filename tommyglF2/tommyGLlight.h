#pragma once
class tommyGLlight
{
private:
	GLfloat Ambient[4];  //环境
	GLfloat Diffuse[4];  //漫反射
	GLfloat Specular[4]; //镜面
	GLfloat Shininess;   //镜面反射指数
	GLfloat Emission[4]; //自发光
	GLfloat Position[4]; //位置
public:
	tommyGLlight(void);
	~tommyGLlight(void);

	//tommyGL标准灯光
	void tommyGLlightSTANDARD(GLfloat lightX,GLfloat lightY,GLfloat lightZ);

	//设置tommyGL标准灯光的位置,调用本函需要先调用tommyGLlightSTANDARD对光源初始化
	void tommyGLlightSTANDARD_setPosition(GLfloat lightX,GLfloat lightY,GLfloat lightZ);

	void tommyGLlightSTANDARD_on();
	void tommyGLlightSTANDARD_off();
};

