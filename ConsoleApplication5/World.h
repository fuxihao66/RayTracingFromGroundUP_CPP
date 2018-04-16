#ifndef __WORLD__
#define __WORLD__
#include "view_plane.h"
#include "my_math.h"
#include "Geometric_obj.h"
#include "light.h"
// #include "Tracer.h"
#include "material.h"
#include "shade_rec.h"
#include <math.h>
#include <vector>

class Tracer;
class Light;
class GeometricObject;
class World{
    public:
        ViewPlane						vp;
        RGBColor						background_color; //没有hit到的时候的颜色
        std::vector<GeometricObject*>	objects;
        //Sphere							TestSphere;
		int								SampleNum;    // 每行的采样数，实际采样数是其平方
		Light*							Ambient_ptr;
		std::vector<Light*>				Lights;
		std::vector<Material*>			materials;
		// Tracer               tracer;
        // Camera               Cam;
        World();
        void prepare_scene();
        void add_object(GeometricObject* obj_ptr);
		void add_light(Light* light_ptr);
		void add_material(Material* mat_ptr);
		void bind_mat_obj();
		ShadeRec hit_objects(const Ray& ray);
        void render_scene();
        void save_to_file();
        RGBColor trace_ray(const Ray& ray);
        RGBColor clamp_pixel(RGBColor& raw_color);
};

#endif