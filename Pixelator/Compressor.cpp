#include "Compressor.h"

cv::Vec3b compress_pixels(std::vector<cv::Vec3b> pixel_vec) {
	unsigned int r = 0;
	unsigned int g = 0;
	unsigned int b = 0;

	for (unsigned int i = 0; i < pixel_vec.size(); ++i) {
		b += pixel_vec[i][0];//Blue
		g += pixel_vec[i][1];//Green
		r += pixel_vec[i][2];//Red
	}
	b /= pixel_vec.size();
	g /= pixel_vec.size();
	r /= pixel_vec.size();
	cv::Vec3b res(b, g, r);
	return res;
}




//Takes a size = s,
//Saves all colors pixels of a square of size s in a Vector with size (s * s)
//Outputs Vector
std::vector<cv::Vec3b> get_colors_square(cv::Mat& img, unsigned int row, unsigned int column, unsigned int size) {
	std::vector<cv::Vec3b> vec;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (row + i < img.rows && column + j < img.cols)
				vec.push_back(img.at<cv::Vec3b>(row + i, column + j));
		}
	}
	return vec;
}

//TODO:: proper naming
//Takes an image and a range
//Makes a 2D vector, it stores the pixel colors of the whole picture and sort them into "squares" size(range * range)
std::vector<std::vector<cv::Vec3b>> make_rangevector(cv::Mat& img, cv::Mat& mod_img, unsigned int range) {
	std::vector<std::vector<cv::Vec3b>> testing;
	for (int r = 0; r < mod_img.rows; r += range) {
		for (int c = 0; c < mod_img.cols; c += range) {
			testing.push_back(get_colors_square(img, r, c, range));
		}
	}

	return testing;
}

//Take a Vector of Colorvectors(Vec3b)
//Compresses it to a Colorvector;
std::vector<cv::Vec3b> compress_vector(std::vector<std::vector<cv::Vec3b>> vec) {
	std::vector<cv::Vec3b> compressed;
	for (int i = 0; i < vec.size(); i++) {
		compressed.push_back(compress_pixels(vec[i]));
	}

	return compressed;
}



cv::Mat create_compressed_image(std::string path, unsigned int factor) {
	//Loading original image
	cv::Mat img = cv::imread(path);
	imshow("original", img);

	//Creating image with new dimensions
	cv::Mat mod = make_new_dimensions(img, factor);

	//Modifying image
	std::vector<cv::Vec3b> compressed;
	compressed = compress_vector(make_rangevector(img, mod, factor));
	fill_new_image(mod, compressed, factor);
	return mod;
}

//Creates an Image with specific size
cv::Mat make_new_dimensions(cv::Mat& img, unsigned int factor) {
	unsigned int height = calc_new_image_height(img, factor);
	unsigned int width = calc_new_image_width(img, factor);
	cv::Mat new_img(height, width, CV_8UC3, cv::Scalar(255, 255, 255));
	std::cout << "New Image Size: " << new_img.rows << ", " << new_img.cols << std::endl;
	return new_img;
}

void save_image(cv::Mat& img, std::string path) {
	std::cout << path << std::endl;
	imwrite(path, img);
}

void make_new_pixels(cv::Mat& img, std::vector<cv::Vec3b>& compressed_vec, unsigned int range, unsigned int r, unsigned int c, unsigned int k) {

	for (unsigned int x = 0; x < range; ++x) {
		for (unsigned int y = 0; y < range; ++y) {
			img.at<cv::Vec3b>(r + x, c + y) = compressed_vec[k];
		}
	}

}

void fill_new_image(cv::Mat& img, std::vector<cv::Vec3b>& compressed_vec, unsigned int factor) {
	int k = 0;

	for (int r = 0; r < img.rows; r += factor) {
		for (int c = 0; c < img.cols; c += factor) {
			make_new_pixels(img, compressed_vec, factor, r, c, k);
			k++;
		}
	}
}

unsigned int calc_new_image_height(cv::Mat& img, int factor) {
	std::cout << "Rows: " << img.rows << ", Factor:" << factor;
	unsigned int height = img.rows / factor;
	std::cout << " Factor: " << height;
	std::cout << " New Height:" << height * factor << std::endl;
	return (height *= factor);
	std::cout << std::endl;
}

unsigned int calc_new_image_width(cv::Mat& img, int factor) {
	std::cout << "Cols: " << img.cols << ", Factor:" << factor;
	unsigned int width = img.cols / factor;
	std::cout << " Factor: " << width;
	std::cout << " New Width:" << width * factor << std::endl;
	return (width *= factor);
	std::cout << std::endl;
}
