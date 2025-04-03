int get_grad(struct rbg_img *im, int y, int x, int color, char axis){ 
    // calculate the x 
    int height = im->height; 
    int width = im->width; 

    if (axis == 'x'){ 
        int left = (x == 0) ? width - 1 : x - 1; 
        int right = (x == width) ? 0 : x + 1; 
        return getpixel(im, y, right, color) - getpixel(im, y, left, color); 
    } 

    if (axis == 'y'){ 
        int up = (y == 0) ? height - 1: y - 1; 
        int down = (y == height) ? 0: y + 1; 
        return getpixel(im, down, x, color) - getpixel(im, up, x, color); 
    }
}

void calc_energy(struct rgb_img *im, struct rgb_img **grad){ // dont know how to use **grad yet 
    // need to get get_grad 
    int width = im -> width; 
    int height = im -> height;  // need to set the dimensions of grad which are the same as im just dont know why double pointer 

    for(int i = 0; i < height; i++){ 
        for(int j = 0; j < width; j++){ 

            int Rx = get_grad(im, i, j, 0, 'x'); 
            int Gx = get_grad(im, i, j, 1, 'x'); 
            int Bx = get_grad(im, i, j, 2, 'x'); 

            int Ry = get_grad(im, i, j, 0, 'y'); 
            int Gy = get_grad(im, i, j, 1, 'y'); 
            int By = get_grad(im, i, j, 2, 'y'); 

            double energy = ((Rx * Rx) + (Gx * Gx) + (Bx * Bx) + (Ry * Ry) + (Gy * Gy) + (By * By)); 
            energy = pow(double(energy), 0.5); //might have to be double 
            unit8_t pixel = (unit8_t)(energy/10); 
            set_pixel(*grad, i, j, pixel, pixel, pixel); 
        }
    } 
} 

void dynamic_seam(struct rgb_img *grad, double **best_arr){ //idk if this is void so change if needed 
    
}

void recover_path(double *best, int height, int width, int **path){ 
    *path = (int*) malloc(height * sizeof(int)); 
    int min = 1000; 
    int min_col = 0; 
    int cur_val = 10000; 
    for(int i = 0; i < width; i++){ 
        cur_val = best[(height-1)*width + i]; 
        if(min > cur_val){ 
            min = cur_val; 
            min_col = i; 
        }
    } 
    (*path)(height - 1) = min_col; 

    int left = 0; 
    int right = 0; 
    int above = 0; 

    for(int j = height - 2; j > 0; j--){ 
        left = (min_col == 0) ? 10000: best[(j*width + min_col - 1)]; 
        right = (min_col == width) ? 10000: best[(j*width + min_col + 1)]; 
        if( left == right == above){ 
            (*path)(j) = above; 
        } 
        else{ 
            (*path)(j) = min(left, right, above); 
        }
    }
} 

void remove_seam(struct rgb_img *src, struct rgb_img **dest, int *path){ 
    int height = src -> height; 
    int width = src -> width; 
    bool after_seam = false 

    create_image(*dest, height, width - 1); 

    for(int y = 0; y < height; y++){ 
        after_seam = false 
        for(int x = 0; x < width; x++){ 
            if(x == (*path)(y)){ 
                after_seam = true 
                continue; 
            }
            if(after_seam == true){  // need to basically shift pixels to the left once we remove one 
                R = getpixel(src, y, x, 0); //get info for pixel at the spot in the picture 
                G = getpixel(src, y, x, 1); 
                B = getpixel(src, y, x, 2); 
                set_pixel(*grad, y, x-1, R, G, B); // place the pixel 1 to the left 
            }
            else{ 
                R = getpixel(src, y, x, 0); 
                G = getpixel(src, y, x, 1); 
                B = getpixel(src, y, x, 2); 
                set_pixel(*grad, y, x, R, G, B); 
            } 
        } 
    }
