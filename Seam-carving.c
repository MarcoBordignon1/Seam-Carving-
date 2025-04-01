#include <math.h> 
// Ok 1) need to read the image to make it into the stuctue 
//    2) then use the create img function actually take the info from the file and into the stuct
//    3) then need to set each pixel to get the r,b,g values 

struct rgb_img{
    uint8_t *raster;
    size_t height;
    size_t width;
}; 

void create_img(struct rgb_img **im, size_t height, size_t width){
    *im = (struct rgb_img *)malloc(sizeof(struct rgb_img));
    (*im)->height = height;
    (*im)->width = width;
    (*im)->raster = (uint8_t *)malloc(3 * height * width);
} 

uint8_t get_pixel(struct rgb_img *im, int y, int x, int col){
    return im->raster[3 * (y*(im->width) + x) + col]; 
} 

void set_pixel(struct rgb_img *im, int y, int x, int r, int g, int b){
    im->raster[3 * (y*(im->width) + x) + 0] = r;
    im->raster[3 * (y*(im->width) + x) + 1] = g;
    im->raster[3 * (y*(im->width) + x) + 2] = b;
} 

int get_grad(struct rbg_img *im, int y, int x, int color, char axis){ 
    // calculate the x 
    int height = im->height 
    int width = im->width 

    if (axis == 'x'){ 
        int left = (x == 0) ? width : x - 1 
        int right = (x == width) ? 0 : x + 1 
        return getpixel(im, y, right, color) - getpixel(im, y, left, color) 
    } 

    if (axis == 'y'){ 
        int up = (y == 0) ? height : y - 1 
        int down = (y == height) ? 0: y + 1 
        return getpixel(im, down, x, color) - getpixel(im, up, x, color) 
    }
}

void calc_energy(struct rgb_img *im, struct rgb_img **grad){ 
    // need to get get_grad 
    int width = im -> width 
    int height = im -> height 

    for(int i, i < height, i++){ 
        for(int j, j < width, j++){ 

            int Rx = get_grad(im, i, j, 0, 'x')
            int Gx = get_grad(im, i, j, 1, 'x')
            int Bx = get_grad(im, i, j, 2, 'x')

            int Ry = get_grad(im, i, j, 0, 'y')
            int Gy = get_grad(im, i, j, 1, 'y')
            int By = get_grad(im, i, j, 2, 'y') 

            double energy = ((Rx * Rx) + (Gx * Gx) + (Bx * Bx) + (Ry * Ry) + (Gy * Gy) + (By * By)) 
            energy = pow(double(energy), 0.5)
            return energy 
        }
    } 
} 
