#ifndef CNN_H
#define CNN_H

#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "network.hpp"

namespace cnn {
struct Filter {
    static const int height = 3;
    static const int width = 3;
    float pixel[height][width];
    float dot;
    mat::Mat<float>* map;
    float bias;
    mat::Mat<float>* pool;
};

template <typename T>
mat::Mat<T>* img_to_Mat(const char* path){
    cv::Mat img = cv::imread(path, cv::IMREAD_GRAYSCALE);
    auto mat = mat::create<T>(img.rows, img.cols);
    for(int i = 0; i < img.rows; i++){
        for(int j = 0; j < img.cols; j++){
            mat->elements[i][j] = img.at<uint8_t>(i, j);
        }
    }
    return mat;
}

template <typename T>
cv::Mat Mat_to_cvMat(mat::Mat<T>*& mat){
    cv::Mat img(mat->m, mat->n, CV_8UC1);
    for(int i = 0; i < mat->m; i++){
        for(int j = 0; j < mat->n; j++){
            img.at<uint8_t>(i, j) = mat->elements[i][j];
        }
    }
    return img;
}

template <typename T>
void filter(mat::Mat<T>*& img, Filter& filter){
    if(img->m < 3 || img->n < 3){ return; }
    for(int i = 0; i < img->m - filter.height - 1; i++){
        for(int j = 0; j < img->n - filter.width - 1; j++){
            for(int h = 0; h < filter.height; h++){
                for(int w = 0; w < filter.width; w++){
                    filter.dot += img->elements[i][j] * filter.pixel[h][w];
                }
            }
            filter.map->elements[i][j] = net::ReLU<T>(filter.dot + filter.bias);
        }
    }
}
}
#endif
