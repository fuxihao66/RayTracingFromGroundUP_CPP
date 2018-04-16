#include "light.h"
#include <iostream>
#include <vector>
using std::vector;
Light::Light() {}
/*
* 
* ls: 光强
*/
AmbientLight::AmbientLight(void) 
	:	Light(),
		color(RGBColor(1.0,1.0,1.0)),
		ls(0.07){}

Vector3D AmbientLight::get_dir(ShadeRec& sr) {
	return Vector3D(0.0,0.0,0.0);
}

RGBColor AmbientLight::radience(ShadeRec& sr) {
	return (ls*color);
}
bool AmbientLight::cast_shadow() {
	return false;
}
bool AmbientLight::in_shadow(const Ray& shadow_ray, const ShadeRec& sr) {
	return false;
}





DirLight::DirLight() 
	: Light(),
	  color(RGBColor(1.0,1.0,1.0)),
	  ls(1.0){}

// 方向与通常用的相反
// 即是指向光源的
void DirLight::set_dir(const Vector3D& dir) {
	direction = -1.0 * dir;
}
Vector3D DirLight::get_dir(ShadeRec& sr) {
	return direction;
}
RGBColor DirLight::radience(ShadeRec& sr) {
	return (ls*color);
}
bool DirLight::cast_shadow() {
	return true;
}
bool DirLight::in_shadow(const Ray& shadow_ray, const ShadeRec& sr) {
	return true;
}


PointLight::PointLight(const Point3D& loc) 
	: Light(),
	  color(RGBColor(1.0,1.0,1.0)),
	  ls(1.0),
	  location(loc){}

bool PointLight::cast_shadow() {
	return true;
}
bool PointLight::in_shadow(const Ray& shadow_ray, const ShadeRec& sr) {
	int num_obj = sr.w->objects.size();
	vector<GeometricObject*> obj = sr.w->objects;
	double dis = location.distance(shadow_ray.o);   // 计算光源到hit点的距离
	double t;
	// 逐物体检测 是否在碰到光源前就碰到物体，如果碰到就退出 返回false
	for (int i = 0; i < num_obj; i++) {
		if (obj[i]->shadow_hit(shadow_ray, t) && t < dis) {
			return true;
		}
	}

	return false;
}
Vector3D PointLight::get_dir(ShadeRec& sr) {
	//std::cout << (location - sr.hit_point).norm().x << std::endl;
	return (location - sr.hit_point).norm();
}

RGBColor PointLight::radience(ShadeRec& sr) {
	return (ls*color);
}