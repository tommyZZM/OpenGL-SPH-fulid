#include "tommyGLfulid.h"

tommyGLfulid::tommyGLfulid(void)
{
}


tommyGLfulid::~tommyGLfulid(void)
{
}

void tommyGLfulid::init_fulid(int fulid_size)
{
	//初始化流体de参数
	f_Mass = 0.006f;                                  //质量系数
	f_SmoothRange = (_box_size/(fulid_size-1))*1.2;  //光滑核半径
	f_Sh2 = f_SmoothRange*f_SmoothRange;              //*2
	f_Viscosity = 0.16f;                               //粘稠度
	f_DENSITY   = 1.0f;                               //平静时密度

	//初始化初始流体块
	if (fulid_size >= 8)//最大体积为8.(太多了可能会把机子卡爆)
	{
		fulid_size = 8;
	}
	_fulidsize = fulid_size;
	fulid_ele_num = fulid_size*fulid_size*fulid_size;
	_fulid_ele = new tommyGLfulid_ele[fulid_ele_num];//创建芥末多个流体元的数据空间

	int i = 0;//初始化流体元的位置..
	for (int z=1;z<=fulid_size;z++)
	{
		for (int y=1;y<=fulid_size;y++)
		{
			for (int x=1;x<=fulid_size;x++)
			{
				_fulid_ele[i].ele_init(1.5 - (3.0/(_fulidsize-1))*(x-1),1.5 - (3.0/(_fulidsize-1))*(y-1) , _box_size/2 - (3.0/(_fulidsize-1))*(z));
				_fulid_ele[i].e_Neighbor = new int[fulid_ele_num];//初始化邻居的储存(最大)
				i++;
			}
		}
	}

	fef_dists = new double*[fulid_ele_num];           //初始化距离矩阵(fulid_ele_num x fulid_ele_num)
	for( int i = 0; i<fulid_ele_num; i++ )
	{
		fef_dists[i] = new double[fulid_ele_num];
	}
}

void tommyGLfulid::Draw_fulid()
{
	for (int i=0;i<fulid_ele_num;i++)//绘制所有流体元
	{
		_fulid_ele[i].ele_draw();
	}
}

void tommyGLfulid::PlaceContainer(GLfloat box_size)
{
	_box_size = box_size;
	_box_pos = Vector3d(0.0f,0.0f,0.0f);
	_box_last_pos = _box_pos;
	_box_Force = Vector3d(0.0f,0.0f,0.0f);
	_box_Speed = Vector3d(0.0f,0.0f,0.0f);
	_box_last_Speed = _box_Speed;
	//DrawBoxContainer(c_x,c_y);
}

void tommyGLfulid::DrawBoxContainer(GLfloat x,GLfloat y)
{
	_box_last_pos.x() = _box_pos.x();
	_box_last_pos.y() = _box_pos.y();
	glPushMatrix();
	glColor3f(0.76,0.76,0.76);
	glLineWidth(2.8);
	glTranslatef(x,y,0.0f);
	glutWireCube(_box_size);
	glPopMatrix();
	glLineWidth(1.0);
	_box_pos.x() = x;
	_box_pos.y() = y;
}

void tommyGLfulid::Compute_box()
{
	_box_Speed = _box_pos - _box_last_pos;//计算容器速度
	_box_Force += (_box_Speed - _box_last_Speed)*0.99f;//计算容器施力
	_box_last_Speed = _box_Speed;
}

bool tommyGLfulid::VolumeBoxContainer(GLfloat a,int x1_or_y2)
{
	switch(x1_or_y2)
	{
	case 1:
		return (fabs(a - _box_pos.x()) >= fabs(_box_size - _box_pos.x()));
		break;
	case 2:
		return (fabs(a - _box_pos.y()) >= fabs(_box_size - _box_pos.y()));
		break;
	default:
		return false;
		break;
	}
}

//囧囧的流体运算...[]0604

void tommyGLfulid::Compute_fulid()
{
	int       i, j, k;
	Vector3d  vec_tmp;
	GLfloat   s_weight;
	GLfloat   s_pressure;
	GLfloat   s_viscosity;
	double    dist, inv_dist;

	for (i=0;i<fulid_ele_num;i++)//初始化参数
	{
		for (j=i+1;j<fulid_ele_num;j++)
		{
			vec_tmp = _fulid_ele[i].ele_pos - _fulid_ele[j].ele_pos;
			fef_dists[i][j] = fef_dists[j][i] = vec_tmp.length(); 
			//计算并且获得流体元之间的距离
		}
		fef_dists[i][i]=0;

		_fulid_ele[i].ef_Force = Vector3d(0.0f,0.0f,0.0f);
		_fulid_ele[i].e_Density = 0.0f;
		_fulid_ele[i].e_NeighborNum = 0;
		//_fulid_ele[i].[_fulid_ele[i].e_NeighborNum] = -1;
	}

	for (i=0;i<fulid_ele_num;i++)
	{
		for (j=i+1;j<fulid_ele_num;j++)
		{
			if (fef_dists[i][j] < f_SmoothRange)
			{
				s_weight = pow(1 - fef_dists[i][j]/f_SmoothRange,2);
				_fulid_ele[i].e_Density += s_weight;
				_fulid_ele[j].e_Density += s_weight;
				//互相加为邻居
				_fulid_ele[i].e_NeighborNum++;//i的邻居数加1(初值为1)
				_fulid_ele[i].e_Neighbor[_fulid_ele[i].e_NeighborNum] = j;
				_fulid_ele[j].e_NeighborNum++;
				_fulid_ele[j].e_Neighbor[_fulid_ele[j].e_NeighborNum] = i;
			}
		}
	}

	//计算鸭梨
	for (i=0;i<fulid_ele_num;i++)
	{
		if (_fulid_ele[i].e_Density < f_DENSITY)
		{
			_fulid_ele[i].e_Density = f_DENSITY;
		}
		//_fulid_ele[i].e_Density = 
		_fulid_ele[i].e_Pressure = (_fulid_ele[i].e_Density - f_DENSITY)*gasK;
	}

	for (i=0;i<fulid_ele_num;i++)
	{
		for (j=1;j<_fulid_ele[i].e_NeighborNum;j++)
		{
			k = _fulid_ele[i].e_Neighbor[j]; //获取i号流体元的第j个邻居的引索..
			vec_tmp = _fulid_ele[i].ele_pos - _fulid_ele[k].ele_pos;//坐标差
			//cout<<"x="<<vec_tmp.x()<<"  y="<<vec_tmp.y()<<"  z="<<vec_tmp.z()<<"\n";
			s_weight = 1-fef_dists[i][k]/f_SmoothRange;
			s_pressure = s_weight*(_fulid_ele[i].e_Pressure + _fulid_ele[k].e_Pressure)/(2*_fulid_ele[k].e_Density) * PRESS;
			inv_dist = 1.0f/fef_dists[i][k];
			vec_tmp  *= inv_dist;
			_fulid_ele[i].ef_Force += vec_tmp*s_pressure;//计算并且加上鸭梨
			s_viscosity = (s_weight / _fulid_ele[i].e_Density) * f_Viscosity;
			vec_tmp = _fulid_ele[i].ef_Speed - _fulid_ele[k].ef_Speed;
			_fulid_ele[i].ef_Force -= vec_tmp*s_viscosity;//计算并且加上粘滞力
		}
	}
	
	for (i=0;i<fulid_ele_num;i++)
	{
		_fulid_ele[i].ef_Force -= (_box_Force);
		_fulid_ele[i].ef_Force.z() -= GRAVITY;
		_fulid_ele[i].ele_move(_box_pos,_box_size);
	}
}

