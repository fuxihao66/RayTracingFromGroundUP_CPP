#ifndef __SR__
#define __SR__

#include "my_math.h"
#include "World.h"
#include "material.h"
class World;

class ShadeRec{
    public:
        bool		hit_an_obj;
        Point3D		local_hit_point;	//用于绑定纹理
		Point3D		hit_point;			//hit到的点 在世界坐标下
        Vector3D	normal;
		double		t;					// 当前光线hit到最近的t
        World*		w;
		Ray			ray;
		Material*	material_ptr;


		ShadeRec();
        ShadeRec(World* world_ptr);
		ShadeRec(const ShadeRec& sr);
};

#endif