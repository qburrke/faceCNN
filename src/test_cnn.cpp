#include "cnn.hpp"

#define P(x) std::cout << x << std::endl
#define IMG_PATH "resources/red.png"
#define ROWS 100
#define COLS 100

int main(int argc, const char** argv){
	/*
	cv::Mat dog = cv::imread("resources/dog.png", cv::IMREAD_GRAYSCALE);
	auto mat = cnn::img_to_Mat<uint8_t>("resources/dog.png");
	cv::Mat img = cnn::Mat_to_cvMat(mat);
	*/

	cv::Mat dog = cv::imread(argv[1], cv::IMREAD_GRAYSCALE);
	auto mat = cnn::img_to_Mat(argv[1]);
	cv::Mat img = cnn::Mat_to_cvMat(mat);

	cnn::Filter* line_fil = new cnn::Filter;
	line_fil->bias = 1.0f;
	for(int i = 0; i < 3; i++){ for(int j = 0; j < 3; j++){ line_fil->pixel[i][j] = 0.0f; } }
	line_fil->pixel[0][1] = 1.0f;
	line_fil->pixel[0][2] = 1.0f;
	line_fil->pixel[0][3] = 1.0f;
	line_fil->map = mat::create(mat->m, mat->n);
	line_fil->pool = mat::create(mat->m, mat->n);
	cnn::filter(mat, line_fil);
	//cnn::filter(line_fil->pool, line_fil);
	//cnn::filter(line_fil->pool, line_fil);
	cv::Mat line_fil_img = cnn::Mat_to_cvMat(line_fil->map);
	cv::Mat line_pool_img = cnn::Mat_to_cvMat(line_fil->pool);
	
	cnn::Filter* dia_fil = new cnn::Filter;
	dia_fil->bias = 1.0f;
	for(int i = 0; i < 3; i++){ for(int j = 0; j < 3; j++){ dia_fil->pixel[i][j] = 0.0f; } }
	dia_fil->pixel[0][2] = 1.0f;
	dia_fil->pixel[1][1] = 1.0f;
	dia_fil->pixel[2][0] = 1.0f;
	dia_fil->map = mat::create(mat->m, mat->n);
	dia_fil->pool = mat::create(mat->m, mat->n);
	//cnn::filter(mat, dia_fil);
	//cnn::filter(dia_fil->pool, dia_fil);
	cnn::filter(line_fil->pool, dia_fil);
	cv::Mat dia_fil_img = cnn::Mat_to_cvMat(dia_fil->map);
	cv::Mat dia_pool_img = cnn::Mat_to_cvMat(dia_fil->pool);

	P("dog Submatrix " << (dog.isSubmatrix() ? "yes" : "no"));
	P("line f Submatrix " << (line_fil_img.isSubmatrix() ? "yes" : "no"));
	P("line p Submatrix " << (line_pool_img.isSubmatrix() ? "yes" : "no"));
	P("dia f Submatrix " << (dia_fil_img.isSubmatrix() ? "yes" : "no"));
	P("dia p Submatrix " << (dia_pool_img.isSubmatrix() ? "yes" : "no"));
	P("dog con "<< (dog.isContinuous() ? "yes" : "no"));
	P("line f con " << (line_fil_img.isContinuous() ? "yes" : "no"));
	P("line p con " << (line_pool_img.isContinuous() ? "yes" : "no"));
	P("dia f con " << (dia_fil_img.isContinuous() ? "yes" : "no"));
	P("dia p con " << (dia_pool_img.isContinuous() ? "yes" : "no"));

	P("img dim " << dog.rows << " " << dog.cols);
	
	//dog = dog(cv::Range(80,280), cv::Range(150,330));
	int h = std::stoi(argv[2]);
	int w = std::stoi(argv[3]);
	line_fil_img = line_fil_img(cv::Range(0,h), cv::Range(0,w));
	line_pool_img = line_pool_img(cv::Range(0, h / 2), cv::Range(0, w/2));
	dia_fil_img = dia_fil_img(cv::Range(0, h), cv::Range(0,w));
	dia_pool_img = dia_pool_img(cv::Range(0, h / 2), cv::Range(0, w/2));

	cv::resize(dog, dog, cv::Size(320, 476), cv::INTER_LINEAR);
	
	//cv::resize(line_fil_img, line_fil_img, cv::Size(320, 476), cv::INTER_LINEAR);
	cv::resize(line_pool_img, line_pool_img, cv::Size(h, w), cv::INTER_LINEAR);
	//cv::resize(dia_fil_img, dia_fil_img, cv::Size(320, 476), cv::INTER_LINEAR);
	cv::resize(dia_pool_img, dia_pool_img, cv::Size(h, w), cv::INTER_LINEAR);
	
	cv::imshow("orignal", dog);
	cv::imshow("line filter", line_fil_img);
	cv::imshow("line pool", line_pool_img);
	cv::imshow("dia filter", dia_fil_img);
	cv::imshow("dia pool", dia_pool_img);

	while(cv::waitKey(20) != 27){};
	mat::free(mat);
	mat::free(line_fil->map);
	mat::free(line_fil->pool);
	mat::free(dia_fil->map);
	mat::free(dia_fil->pool);
	delete line_fil;
	delete dia_fil;
	return 0;
}

