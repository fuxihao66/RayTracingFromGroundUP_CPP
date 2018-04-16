#include "lambertian.h"

Lambertian::Lambertian() 
	: BRDF(){}

void Lambertian::set_cd(const RGBColor& c) {
	cd = c;
}
void Lambertian::set_kd(double k) {
	kd = k;
}

RGBColor Lambertian::f(const ShadeRec& sr, const Vector3D& wi, const Vector3D& wo) {
	return kd / pi * cd;
}

RGBColor Lambertian::f_sample(const ShadeRec& sr, Vector3D& wi, const Vector3D& wo) {
	return RGBColor(1.0,1.0,1.0);
}

RGBColor Lambertian::rho(const ShadeRec& sr, const Vector3D& wo) {
	return kd * cd;
}