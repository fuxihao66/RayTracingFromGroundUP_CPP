#ifndef __LAMB__
#define __LAMB__
#include "my_math.h"
#include "shade_rec.h"
#define pi 3.14159265359
class ShadeRec;
class BRDF {
public:

	virtual RGBColor f(const ShadeRec& sr, const Vector3D& wi, const Vector3D& wo) = 0; //返回BRDF
	virtual RGBColor f_sample(const ShadeRec& sr, Vector3D& wi, const Vector3D& wo) = 0;//wi用于返回反射方向
	virtual RGBColor rho(const ShadeRec& sr, const Vector3D& wo) = 0;
	
};

class Lambertian : public BRDF {

public:
	Lambertian();
	virtual RGBColor f(const ShadeRec& sr, const Vector3D& wi, const Vector3D& wo);
	virtual RGBColor f_sample(const ShadeRec& sr, Vector3D& wi, const Vector3D& wo);
	virtual RGBColor rho(const ShadeRec& sr, const Vector3D& wo);
	void set_kd(double kd);
	void set_cd(const RGBColor& cd);
protected:
	double kd;
	RGBColor cd;
};


#endif
