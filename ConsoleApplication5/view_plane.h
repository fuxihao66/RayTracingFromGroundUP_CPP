#ifndef __VIEWPLANE__
#define __VIEWPLANE__

#include "my_math.h"

class ViewPlane{
    public:
        int    hres;        //horizontal resolution
        int    vres;
        float  s;           //pixel size ??? p67 可以用来zoom in
        float  gamma;       //monitor gamma
        float  inv_gamma;
        RGBColor *color_array;

		ViewPlane() = default;
        ViewPlane(int hres, int vres, int pix_size, float gamma);
};
#endif