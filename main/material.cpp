/*store brdf*/
#include "material.h"
#include <iostream>

//Material::Material(const Material& m) {
//}


Matte::Matte() 
	:	Material(),
		ambient_brdf(new Lambertian),
		diffuse_brdf(new Lambertian){}

/*设置环境光反射系数*/
void Matte::set_ka(const double ka) {
	ambient_brdf->set_kd(ka);
}
/*设置漫反射系数*/
void Matte::set_kd(const double kd) {
	diffuse_brdf->set_kd(kd);
}

void Matte::set_cd(const RGBColor& c) {
	ambient_brdf->set_cd(c);
	diffuse_brdf->set_cd(c);
}
void Matte::init_material(const double ka, const double kd, const RGBColor& c) {
	set_ka(ka);
	set_kd(kd);
	set_cd(c);
}

// 计算当前点处的颜色

RGBColor Matte::shade(ShadeRec& sr) {

	Vector3D wo = -1.0*sr.ray.d;
	RGBColor L = ambient_brdf->rho(sr, wo)*sr.w->Ambient_ptr->radience(sr);
	//RGBColor L = RGBColor(0.0, 0.0, 0.0);
	int numLights = sr.w->Lights.size();
	
	for (int i = 0; i < numLights; i++) {
		Vector3D wi = sr.w->Lights[i]->get_dir(sr);   // 光线的入射方向
		double ndotwi = sr.normal*wi;
		bool in_shadow = false;
		if (ndotwi > 0.0) {
			if (sr.w->Lights[i]->cast_shadow()) {  //if enable shadow
				Ray shadow_ray(sr.hit_point, wi);
				in_shadow = sr.w->Lights[i]->in_shadow(shadow_ray, sr);
			}
			if (!in_shadow) {
				L = ndotwi * diffuse_brdf->f(sr, wo, wi)*sr.w->Lights[i]->radience(sr) + L;
			}
		}

	}
	return L;
}
RGBColor Matte::shade_distance(ShadeRec& sr) {

	Vector3D wo = -1.0*sr.ray.d;
	RGBColor L = ambient_brdf->rho(sr, wo)*sr.w->Ambient_ptr->radience(sr);
	//RGBColor L = RGBColor(0.0, 0.0, 0.0);
	int numLights = sr.w->Lights.size();
	for (int i = 0; i < numLights; i++) {
		Vector3D wi = sr.w->Lights[i]->get_dir(sr);   // 光线的入射方向
		double ndotwi = sr.normal*wi;
		bool in_shadow = false;
		if (ndotwi > 0.0) {
			if (sr.w->Lights[i]->cast_shadow()) {  //if enable shadow
				Ray shadow_ray(sr.hit_point, wi);
				in_shadow = sr.w->Lights[i]->in_shadow(shadow_ray, sr);
			}
			if (!in_shadow) {
				L = ndotwi * diffuse_brdf->f(sr, wo, wi)*sr.w->Lights[i]->radience(sr) / sr.local_hit_point.distance(Point3D(0.0, 0.0, 50.0)) + L;
			}
		}

	}
	return L;
}