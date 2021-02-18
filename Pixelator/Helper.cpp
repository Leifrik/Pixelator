#include "Helper.h"

void check_path(std::string& path) {
	std::replace(path.begin(), path.end(), '\\', '/');
}


void get_unser_input(std::string& path, std::string& destination_path, unsigned int& factor) {
	std::cout << "Please enter the path of the Original image:" << std::endl;
	std::cin >> path;
	std::cout << "Please enter the path of the modified image:" << std::endl;
	std::cin >> destination_path;
	std::cout << "Please enter the Compression factor:" << std::endl;
	std::cin >> factor;
}