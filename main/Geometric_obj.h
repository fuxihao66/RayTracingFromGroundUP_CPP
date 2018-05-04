#ifndef __GEOOBJ__
#define __GEOOBJ__

#include "my_math.h" 
#include "shade_rec.h"
#include "material.h"

class ShadeRec;
class Material;
class GeometricObject{
    public:
        virtual bool hit(const Ray &ray, double &tmin, ShadeRec &sr) = 0;
		virtual Material* get_material() = 0;
		virtual void	  set_material(Material* mat) = 0;
		virtual bool      shadow_hit(const Ray& shadow_ray, double& t) = 0;
    protected:
        RGBColor color; //之后将替换成 material pointer
};

class Plane: public GeometricObject{
    public:
        Plane(const Point3D& p, const Vector3D& n);
        virtual bool hit(const Ray &ray, double &tmin, ShadeRec &sr);
		virtual Material* get_material();
		virtual void	  set_material(Material* mat);
		virtual bool      shadow_hit(const Ray& shadow_ray, double& t);

    private:
		Material * material_ptr;
        Point3D             point;   //初始点a
        Vector3D            normal;  //法线
        static const double epsilon; //细小偏移量（t<epsilon），用于阴影
};


class Sphere: public GeometricObject{
    public:
        Sphere(const Point3D c, const float r);
        Sphere() = default;
        virtual bool hit(const Ray &ray, double &tmin, ShadeRec &sr);
		virtual Material* get_material();
		virtual void	  set_material(Material* mat);
		virtual bool      shadow_hit(const Ray& shadow_ray, double& t);
    private:
		Material *			material_ptr;
        Point3D             center;
        float               radius;
        const static double epsilon;
};

#endif