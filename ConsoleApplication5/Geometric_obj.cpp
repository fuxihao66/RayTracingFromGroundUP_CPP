#include "Geometric_obj.h"
#include <math.h>



const double Plane::epsilon = 0.000000001;
Plane::Plane(const Point3D& p, const Vector3D& n)
    : point(p), normal(n){}

Material* Plane::get_material() {
	return material_ptr;
}
void Plane::set_material(Material* mat) {
	material_ptr = mat;
}
bool Plane::hit(const Ray &ray, double &tmin, ShadeRec &sr){
    //计算出t
    double t = (point-ray.o)*normal/(ray.d*normal);

    //判断t是否符合要求
    if (t > epsilon){
        tmin = t;         //如果屏幕中有多个物体，每个求交，算出来t小的被渲染
        sr.normal = normal;
        sr.local_hit_point = ray.o + t*ray.d;
        return true;
    }
    else {
        return false;
    }
}
bool Plane::shadow_hit(const Ray& shadow_ray, double& tmin) {
	double t = (point - shadow_ray.o)*normal / (shadow_ray.d*normal);

	if (t > epsilon) {
		tmin = t;        
		return true;
	}
	else {
		return false;
	}
}






Sphere::Sphere(const Point3D c, const float r)
    : center(c), radius(r){}

Material* Sphere::get_material() {
	return material_ptr;
}

void Sphere::set_material(Material* mat) {
	material_ptr = mat;
}

const double Sphere::epsilon = 0.00000000001;
bool Sphere::hit(const Ray &ray, double &tmin, ShadeRec &sr){
    double t;
    Vector3D temp = ray.o - center;
    double a = ray.d*ray.d;
    double b = 2.0*ray.d*temp;
    double c = temp*temp - radius*radius;
    double delta = b*b - 4.0* a * c;
    if (delta < 0.0){
        return false;
    }
    else {
        double e = sqrt(delta);
        double denom = 2.0*a; 
        t = (-b-e)/denom;       //计算较近的交点

        if (t > epsilon){
            tmin = t;
            sr.normal = (ray.o+t*ray.d-center).norm();
            sr.local_hit_point = ray.o+t*ray.d;
            return true;
        }

        t = (-b+e)/denom;
        if (t > epsilon){
            tmin = t;
            sr.normal = (ray.o+t*ray.d-center).norm();
            sr.local_hit_point = ray.o+t*ray.d;
            return true;
        }
    }
    return false;
}

bool Sphere::shadow_hit(const Ray& shadow_ray, double& tmin) {
	double t;
	Vector3D temp = shadow_ray.o - center;
	double a = shadow_ray.d*shadow_ray.d;
	double b = 2.0*shadow_ray.d*temp;
	double c = temp * temp - radius * radius;
	double delta = b * b - 4.0* a * c;
	if (delta < 0.0) {
		return false;
	}
	else {
		double e = sqrt(delta);
		double denom = 2.0*a;
		t = (-b - e) / denom;       //计算较近的交点

		if (t > epsilon) {
			tmin = t;
			return true;
		}

		t = (-b + e) / denom;
		if (t > epsilon) {
			tmin = t;
			return true;
		}
	}
	return false;

}


