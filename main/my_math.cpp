#include <math.h>
#include "my_math.h"


RGBColor::RGBColor()
    : x(0.0), y(0.0), z(0.0){}
RGBColor::RGBColor(double r, double g, double b)
    : x(r), y(g), z(b){}
Ray::Ray(Point3D& origin, Vector3D& direction)
    : o(origin), d(direction){}



RGBColor RGBColor::powc(double gamma){
    return RGBColor(pow(x,gamma),pow(x,gamma),pow(z,gamma));
}

double Point3D::distance(const Point3D& p) const {
    return (sqrt(		(x - p.x) * (x - p.x)
                   + 	(y - p.y) * (y - p.y)
                   +	(z - p.z) * (z - p.z) ));
}

Vector3D Vector3D::norm(){
    double mo = sqrt(x*x + y*y + z*z);
    return Vector3D(x/mo, y/mo, z/mo);
}

// Point3D& Point3D::operator= (const Point3D& rhs) {

//     if (this == &rhs)
//         return (*this);

//     x = rhs.x;
//     y = rhs.y;
//     z = rhs.z;
//     return (*this);
// }
// Point3D operator* (const Matrix& mat, const Point3D& p) {
//     return (Point3D(mat.m[0][0] * p.x + mat.m[0][1] * p.y + mat.m[0][2] * p.z + mat.m[0][3],
//                     mat.m[1][0] * p.x + mat.m[1][1] * p.y + mat.m[1][2] * p.z + mat.m[1][3],
//                     mat.m[2][0] * p.x + mat.m[2][1] * p.y + mat.m[2][2] * p.z + mat.m[2][3]));
// }


