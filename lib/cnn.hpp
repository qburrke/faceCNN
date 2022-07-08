#ifndef CNN_H
#define CNN_H

#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "network.hpp"

namespace cnn {

#define HEIGHT 3;
#define WIDTH 3;

struct Filter {
    float pixel[3][3];
    float dot;
    mat::Mat* map;
    float bias;
    mat::Mat* pool;
};

mat::Mat* img_to_Mat(const char* path){
    cv::Mat img = cv::imread(path, cv::IMREAD_GRAYSCALE);
    auto mat = mat::create(img.rows, img.cols);
    for(int i = 0; i < img.rows; i++){
        for(int j = 0; j < img.cols; j++){
            mat->elements[i][j] = (float)img.at<uint8_t>(i, j);
        }
    }
    return mat;
}

cv::Mat Mat_to_cvMat(mat::Mat*& mat){
    cv::Mat img(mat->m, mat->n, CV_8UC1);
    for(int i = 0; i < mat->m; i++){
        for(int j = 0; j < mat->n; j++){
            img.at<uint8_t>(i, j) = (int)mat->elements[i][j];
        }
    }
    return img;
}

void filter(mat::Mat*& img, Filter*& filter){
    if(img->m < 3 || img->n < 3){ return; }
    for(int i = 0; i < img->m - 3 + 1; i++){
        for(int j = 0; j < img->n - 3 + 1; j++){
            filter->dot = 0.0f;
            for(int h = 0; h < 3; h++){
                for(int w = 0; w < 3; w++){
                    filter->dot += (float)img->elements[i+h][j+w] * filter->pixel[h][w];
                }
            }
            filter->map->elements[i][j] = net::ReLU(filter->dot + filter->bias);
        }
    }
    float max;
    for(int i = 0, k = 0; i < img->m - 2; i += 2, k++){
        for(int j = 0, l = 0; j < img->n - 2; j += 2, l++){
            max = filter->map->elements[i][j];
            for(int h = 1; h < 2; h++){
                for(int w = 0; w < 2; w++){
                    if(max < filter->map->elements[i+h][j+w]){
                        max = filter->map->elements[i+h][j+w];
                    }
                }
            }
            filter->pool->elements[k][l] = max;
        }
    }
}
}
#endif
