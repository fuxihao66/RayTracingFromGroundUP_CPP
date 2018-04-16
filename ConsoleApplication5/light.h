#ifndef __LIGHT__
#define __LIGHT__
#include "my_math.h"
#include "shade_rec.h"
class ShadeRec;
class Light {
public:
	Light();
	virtual Vector3D get_dir(ShadeRec& sr) = 0;
	virtual RGBColor radience(ShadeRec& sr) = 0;  // 返回hit到点的入射辐射照度？
	virtual bool     cast_shadow() = 0;
	virtual bool     in_shadow(const Ray& shadow_ray, const ShadeRec& sr) = 0;
protected:
	bool shadows;
};
class AmbientLight : public Light {
public:
	AmbientLight();
	virtual Vector3D get_dir(ShadeRec& sr);
	virtual RGBColor radience(ShadeRec& sr);
	virtual bool     cast_shadow();
	virtual bool     in_shadow(const Ray& shadow_ray, const ShadeRec& sr);
private:
	RGBColor color;
	double   ls;
};

class DirLight : public Light {
public:
	DirLight();
	void set_dir(const Vector3D& dir);
	virtual Vector3D get_dir(ShadeRec& sr);
	virtual RGBColor radience(ShadeRec& sr);
	virtual bool     cast_shadow();
	virtual bool     in_shadow(const Ray& shadow_ray, const ShadeRec& sr);
private:
	Vector3D direction;
	RGBColor color;
	double	 ls;
};

class PointLight : public Light {
public:
	PointLight(const Point3D& loc);
	virtual Vector3D get_dir(ShadeRec& sr);
	virtual RGBColor radience(ShadeRec& sr);
	virtual bool     cast_shadow();
	virtual bool     in_shadow(const Ray& shadow_ray, const ShadeRec& sr);
private:
	RGBColor color;
	double	 ls;
	Point3D  location;
};

#endif 

