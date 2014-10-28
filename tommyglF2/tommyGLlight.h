#pragma once
class tommyGLlight
{
private:
	GLfloat Ambient[4];  //����
	GLfloat Diffuse[4];  //������
	GLfloat Specular[4]; //����
	GLfloat Shininess;   //���淴��ָ��
	GLfloat Emission[4]; //�Է���
	GLfloat Position[4]; //λ��
public:
	tommyGLlight(void);
	~tommyGLlight(void);

	//tommyGL��׼�ƹ�
	void tommyGLlightSTANDARD(GLfloat lightX,GLfloat lightY,GLfloat lightZ);

	//����tommyGL��׼�ƹ��λ��,���ñ�����Ҫ�ȵ���tommyGLlightSTANDARD�Թ�Դ��ʼ��
	void tommyGLlightSTANDARD_setPosition(GLfloat lightX,GLfloat lightY,GLfloat lightZ);

	void tommyGLlightSTANDARD_on();
	void tommyGLlightSTANDARD_off();
};

