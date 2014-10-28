#pragma once
class tommyGLcamera
{
public:
	tommyGLcamera(void);
	~tommyGLcamera(void);

	//tommy标准测试镜头,把这段代码加到display函数里
	void tommyGLcameraSTANDARD(GLfloat cameraX,GLfloat cameraY,GLfloat cameraZ,GLfloat targetX,GLfloat targetY,GLfloat targetZ,GLfloat RotateX,GLfloat RotateY,GLfloat cameraScale);
};

