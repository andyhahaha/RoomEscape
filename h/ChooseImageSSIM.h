#ifndef CHOOSEIMAGESSIM_H
#define CHOOSEIMAGESSIM_H

#include <iostream> 
#include <string> 
#include <opencv2/highgui/highgui.hpp>
#include <opencv/cv.h>

using namespace std;
using namespace cv;

// Compute the SSIM between 2 images
extern double ssim(Mat & img_src, Mat & img_compressed, int block_size, bool show_progress = FALSE);

extern double compute_quality_metrics(Mat img_1, Mat img_2, int block_size) ;
extern void choose_image(string& room_name, int position_number, int vertical_angle, int img_num1, int img_num2);


#endif