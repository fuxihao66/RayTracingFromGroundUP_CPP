//存储shade所需要的信息
#include "shade_rec.h"
//constructor

ShadeRec::ShadeRec()
	: hit_an_obj(false) {}
ShadeRec::ShadeRec(World* world_ptr)
    :   hit_an_obj(false),
		w(world_ptr){}

ShadeRec::ShadeRec(const ShadeRec& sr)
	: hit_an_obj(sr.hit_an_obj),
	material_ptr(sr.material_ptr),
	hit_point(sr.hit_point),
	local_hit_point(sr.local_hit_point),
	normal(sr.normal),
	ray(sr.ray),
	w(sr.w){}