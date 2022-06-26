#include "cnn.hpp"

#define P(x) std::cout << x << std::endl
#define IMG_PATH "resources/red.png"
#define ROWS 100
#define COLS 100

int main(int argc, const char** argv){
	cv::Mat dog = cv::imread("resources/dog.png", cv::IMREAD_GRAYSCALE);
	auto mat = cnn::img_to_Mat<uint8_t>("resources/dog.png");
	cv::Mat img = cnn::Mat_to_cvMat<uint8_t>(mat);

	cnn::Filter fil;
	cv::imshow("from mat", img);
	cv::imshow("orignal", dog);

	while(cv::waitKey(20) != 27){};
	mat::free(mat);
	return 0;
}

