#include "view_plane.h"
#include <stdlib.h>

ViewPlane::ViewPlane(int hres, int vres, int pix_size, float gamma)
    :   hres(hres),
        vres(vres),
        s(pix_size),
        gamma(gamma)
    {
        color_array = (RGBColor*)malloc(sizeof(RGBColor)*hres*vres);
        inv_gamma = 2.2;
    }