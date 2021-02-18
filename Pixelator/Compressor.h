#pragma once
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <vector>
#include <iostream>

//PIXEL MAINPULATION

//Takes a Vector with BGR colors
//Outputs the mean BGR values of the Vector;
cv::Vec3b compress_pixels(std::vector<cv::Vec3b> pixel_vec);


//Takes a size = s,
//Saves all colors pixels of a square of size s in a Vector with size (s * s)
//Outputs Vector
std::vector<cv::Vec3b> get_colors_square(cv::Mat& img, unsigned int row, unsigned int column, unsigned int size);

//TODO:: proper naming
//Takes an image and a range
//Makes a 2D vector, it stores the pixel colors of the whole picture and sort them into "squares" size(range * range)
std::vector<std::vector<cv::Vec3b>> make_rangevector(cv::Mat& img, cv::Mat& mod_img, unsigned int range);

//Take a Vector of Colorvectors(Vec3b)
//Compresses it to a Vector with the meaned BGR values;
std::vector<cv::Vec3b> compress_vector(std::vector<std::vector<cv::Vec3b>> vec);


//?MAGE CREATION
cv::Mat create_compressed_image(std::string path, unsigned int factor);

cv::Mat make_new_dimensions(cv::Mat& img, unsigned int factor);

void save_image(cv::Mat& img, std::string path);

void make_new_pixels(cv::Mat& img, std::vector<cv::Vec3b>& compressed_vec, unsigned int range, unsigned int r, unsigned int c, unsigned int k);

void fill_new_image(cv::Mat& img, std::vector<cv::Vec3b>& compressed_vec, unsigned int factor);

unsigned int calc_new_image_height(cv::Mat& img, int factor);

unsigned int calc_new_image_width(cv::Mat& img, int factor);