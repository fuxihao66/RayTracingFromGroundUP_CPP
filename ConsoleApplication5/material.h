#ifndef __MATERIAL__
#define __MATERIAL__
#include "my_math.h"
#include "shade_rec.h"
#include "lambertian.h"
#include "light.h"
class ShadeRec;
class Lambertian;
class Material
{
public:
	//Material();
	//Material(const Material& m);
	virtual void init_material(const double ka, const double kd, const RGBColor& c) = 0;
	virtual void set_ka(const double k) = 0;
	virtual void set_kd(const double k) = 0;
	virtual void set_cd(const RGBColor& c) = 0;
	virtual RGBColor shade(ShadeRec& sr) = 0;
	virtual RGBColor shade_distance(ShadeRec& sr) = 0;
	/*virtual RGBColor area_light_shade(ShadeRec& sr) = 0;
	virtual RGBColor path_shade(ShadeRec& sr) = 0;*/



};

class Matte :public Material {
private:
	Lambertian* ambient_brdf;
	Lambertian* diffuse_brdf;
public:
	Matte();
	virtual RGBColor shade(ShadeRec& sr);
	RGBColor shade_distance(ShadeRec& sr);
	virtual void init_material(const double ka, const double kd, const RGBColor& c);
	virtual void set_ka(const double k);
	virtual void set_kd(const double k);
	virtual void set_cd(const RGBColor& c);
};


#endif 
