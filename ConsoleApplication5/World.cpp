#include "World.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#define black (Vector3D(0.0,0.0,0.0))
using namespace std;
RGBColor& clamp(RGBColor& a){ 
    a.x = a.x<0 ? 0 : a.x>1 ? 1 : a.x;
    a.y = a.y<0 ? 0 : a.y>1 ? 1 : a.y;
    a.z = a.z<0 ? 0 : a.z>1 ? 1 : a.z;
    return a;
}
inline double clamp(double x){
    return (x<0 ? 0 : x>1 ? 1 : x);
}
inline int toInt(double x){ return int(pow(clamp(x),1/2.2)*255+.5); }


World::World()
{
    vp = ViewPlane(1920, 1080, 1.0, 1.0);
	SampleNum = 6 ;
	background_color = RGBColor(0.0,0.0,0.0);
	
	Ambient_ptr = new AmbientLight();
}

//add obj to the scene
void World::prepare_scene() {
	//add_object(new Sphere(Point3D(-40.0, -60, 0.0), 30));
	add_object(new Plane( Point3D(0.0,20.0,0.0), Vector3D(-0.10,-1.0,0.0)));
	add_object(new Sphere(Point3D(0.0, -5.0, -10.0), 50));
	add_material(new Matte());
	add_material(new Matte());
	for (int i = 0; i < materials.size(); i++) {
		materials[i]->init_material(1.0,1.0, RGBColor(0.0,1.0,1.0)); //设置ka() kd() 光的颜色
	}
	bind_mat_obj();
	add_light(new PointLight(Point3D(65.0, -10.0, 50.0)));
	

}
 void World::add_object(GeometricObject* obj_ptr) {
     objects.push_back(obj_ptr);
 }
 void World::add_light(Light* light_ptr) {
	 Lights.push_back(light_ptr);
 }

void World::add_material(Material* mat_ptr) {
	materials.push_back(mat_ptr);
}



void World::bind_mat_obj() {
	int size = objects.size();
	for (int i = 0; i < size; i++) {
		objects[i]->set_material(materials[i]);
	}
}

void World::render_scene() {
    //成员检查

    RGBColor pixel_color;
    Ray      ray;
    double   zw = 10.0;
    double pix_size = vp.s;
	int    index = 0;
    //ray.d = Vector3D(0,0,-1);
	ray.o = Point3D(0, 0, 50);
	
    for (int r = 0; r < vp.vres; r++){
        for (int c = 0; c < vp.hres; c++){

			pixel_color = background_color;

			for (int p = 0; p < SampleNum; p++) {
				for (int q = 0; q < SampleNum; q++) {

					float nx = pix_size * (c - 0.5f * vp.hres + (q+0.5f)/SampleNum);
					float ny = pix_size * (r - 0.5f * vp.vres + (p+0.5f)/SampleNum);

					ray.d = (Point3D(nx,ny,zw)-ray.o).norm();

					// 把图片中心放到世界坐标xy平面的原点上
					/*float nx = pix_size * (c - 0.5f * vp.hres + 0.5f);
					float ny = pix_size * (r - 0.5f * vp.vres + 0.5f);*/



					// 确定原点
					//ray.o = Point3D(nx, ny, zw);
					pixel_color = trace_ray(ray) + pixel_color;

				}
			}
			pixel_color = pixel_color / ((double)SampleNum*SampleNum);
           
            vp.color_array[index++] = clamp_pixel(pixel_color);
			
			
        }
    }
	
}


ShadeRec World::hit_objects(const Ray& ray) {
	ShadeRec sr(this);
	double t;
	Vector3D normal;
	Point3D local_hit_point;
	int num_objects = objects.size();
	double t_min = 10e8;
	// 这个过程找到了最近的
	for (int i = 0; i < num_objects; i++) {
		if (objects[i]->hit(ray, t, sr) && t < t_min) {
			sr.hit_an_obj = true;
			t_min = t;
			sr.material_ptr = objects[i]->get_material();
			sr.hit_point = ray.o + t * ray.d;
			normal = sr.normal;
			local_hit_point = sr.local_hit_point;
		}
	}
	if (sr.hit_an_obj) {
		sr.t = t_min;
		sr.normal = normal;
		sr.local_hit_point = local_hit_point;
	}
	return sr;
}

RGBColor World::trace_ray(const Ray& ray){
    ShadeRec  sr(hit_objects(ray));
	if (sr.hit_an_obj) {
		sr.ray = ray;
		return sr.material_ptr->shade(sr);
	}
	else {
		return background_color;
	}
 
}

void World::save_to_file(){//给定分辨率

    FILE *f = fopen("image.ppm", "w");         // Write image to PPM file.
    fprintf(f, "P3\n%d %d\n%d\n", vp.hres, vp.vres, 255);
	for (int i=0; i<vp.hres*vp.vres; i++){
		//cout << vp.color_array[i].y << endl;
		fprintf(f,"%d %d %d ", toInt(vp.color_array[i].x), toInt(vp.color_array[i].y), toInt(vp.color_array[i].z));
    }
}


// RGBColor is a 3 dimention vector
// i and j are pixel coordinate
// 启用“钳制”(Clamped)以将颜色和Alpha 值限制在0-1 范围内
// out of gamut: 在color cube之外
// tone mapping: mapping color components to range [0,1]
// gamma correction: monitor bright
RGBColor World::clamp_pixel(RGBColor& raw_color){

    RGBColor mapped_color;

    mapped_color = clamp(raw_color);
    // if (vp.show_out_of_gamut)
    //     mapped_color = clamp_to_color(raw_color);
    // else
    //     mapped_color = max_to_one(raw_color);

    if (vp.gamma != 1.0)
        mapped_color = mapped_color.powc(vp.inv_gamma);

    return mapped_color;
}



