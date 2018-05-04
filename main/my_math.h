#ifndef __MY_MATH__
#define __MY_MATH__

class Normal{
    public:
        double x, y, z;
		Normal() = default;
        Normal(double a, double b, double c)
            : x(a), y(b), z(c) {}
};
class Vector3D{
    public:
        double x, y, z;
		Vector3D() = default;
        Vector3D(double a, double b, double c)
            : x(a), y(b), z(c) {}
        Vector3D norm();
};

class Point3D{
    public:
        double x, y, z;

		Point3D() = default;
        Point3D(double a, double b, double c)
            : x(a), y(b), z(c){}
		double distance(const Point3D& p) const;
};


class RGBColor { //x, y, z的范围为0~1
    public:
        double x;
        double y;
        double z;
        RGBColor(void);
        RGBColor(double r, double g, double b);

        RGBColor powc(double gamma);
};

class Ray {
    public:
        Point3D     o;
        Vector3D    d;
        Ray() = default;
        Ray(Point3D& origin, Vector3D& direction);
};

//操作符重载

inline RGBColor operator + (const RGBColor& a, const RGBColor& b){
    return RGBColor(a.x+b.x, a.y+b.y, a.z+b.z);
}

//inline double operator * (const RGBColor& a, const RGBColor& b) {
//	return (a.x*b.x + a.y*b.y + a.z*b.z);
//}

inline RGBColor operator * (const RGBColor& a, const RGBColor& b) {
	return RGBColor(a.x*b.x, a.y*b.y, a.z*b.z);
}

inline Vector3D operator + (const Vector3D& a, const Vector3D& b){
    return Vector3D(a.x+b.x, a.y+b.y, a.z+b.z);
}

inline Vector3D operator - (const Vector3D& a, const Vector3D& b){
    return Vector3D(a.x-b.x, a.y-b.y, a.z-b.z);
}

inline double operator * (const Vector3D& a, const Vector3D& b){
    return a.x*b.x+a.y*b.y+a.z*b.z;
}

inline Vector3D operator * (double a, const Vector3D& b){
    return Vector3D(a*b.x, a*b.y, a*b.z);
}

inline Point3D operator + (const Point3D& a, const Vector3D& b) {
	return Point3D(a.x + b.x, a.y + b.y, a.z + b.z);
}

inline RGBColor operator / (const RGBColor& a, const double b) {
	return RGBColor(a.x/b, a.y/b, a.z/b);
}

inline RGBColor operator * (double b, const RGBColor& a) {
	return RGBColor(b*a.x, b*a.y, b*a.z);
}

inline Point3D operator + (const Point3D& a, const Point3D& b){
    return Point3D(a.x+b.x, a.y+b.y, a.z+b.z);
}

inline Vector3D operator - (const Point3D& a, const Point3D& b){
    return Vector3D(a.x-b.x, a.y-b.y, a.z-b.z);
}



#endif