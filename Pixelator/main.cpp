#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include "Compressor.h"
#include "Helper.h"

using namespace cv;
using namespace std;



int main(int argc, char* argv[]) {
	//TODO: If factor/height and factor/width is different a bug happens;
	string path = "";

	//string path = "C:/Users/guita/Pictures/09ec5.png";
	string destination_path = "";

	unsigned int factor = 0;

	//Comandline args
	if (argc > 1) {
		std::cout << "PARAMS" << std::endl;
		for (int i = 0; i < argc; ++i) {
			std::cout << argv[i] << std::endl;
		}
		path = argv[1];
		destination_path = argv[2];
		check_path(path);
		check_path(destination_path);
		factor = strtol(argv[3], nullptr, 0);

		//Loading original image
		Mat img = imread(path);
		imshow("original", img);

		//Creating image with new dimensions
		Mat mod = create_compressed_image(path, factor);

		//Modifying image
		std::vector<cv::Vec3b> compressed;
		compressed = compress_vector(make_rangevector(img, mod, factor));
		fill_new_image(mod, compressed, factor);

		//Saving and showing modified image
		save_image(mod, destination_path);
		imshow("modified", mod);

	}
	else {
		std::cout << "Input incorrect try again" << std::endl;
		get_unser_input(path, destination_path, factor);

	}



	waitKey(0);
}