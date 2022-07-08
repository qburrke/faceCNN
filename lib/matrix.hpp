#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <fstream>

namespace mat {

struct Mat {
    int m;
    int n;
    float** elements;
};

bool check(Mat*& a, Mat*& b){
    if(a->m == b->m && a->n == a->n){ return true; }
    return false;
}

Mat* create(const int& m, const int& n){
    auto mat = new Mat;
    mat->m = m; mat->n = n;
    mat->elements = new float*[m];
    for(int i = 0; i < m; i++){ mat->elements[i] = new float[n](); }
    return mat;
}

Mat* copy(Mat* mat){
    Mat* copy = create(mat->m, mat->n);
    for(int i = 0; i < mat->m; i++){
        for(int j = 0; j < mat->n; j++){
            copy->elements[i][j] = mat->elements[i][j];
        }
    }
    return copy;
}

void free(Mat* mat){
    for(int i = 0; i < mat->m; i++){ delete[] mat->elements[i]; }
    delete[] mat->elements;
    delete mat;
    mat = nullptr;
}

void save(const char* path, Mat* mat){
    std::ofstream file(path, std::ios::out);
    file << mat->m; file << " "; file << mat->n;
    for(int i = 0; i < mat->m; i++){
        file << "\n";
        for(int j = 0; j < mat->n; j++){
            file << mat->elements[i][j]; file << " ";
        }
    }
    file.close();
}

Mat* load(const char* path){
    std::ifstream file(path, std::ios::in);
    int m, n;
    file >> m; file >> n;
    Mat* mat = create(m, n);
    for(int i = 0; i < mat->m; i++){
        for(int j = 0; j < mat->n; j++){
            file >> mat->elements[i][j];
        }
    }
    file.close();
    return mat;
}

void fill(Mat*& mat, int num){
    for(int i = 0; i < mat->m; i++){
        for(int j = 0; j < mat->n; j++){
            mat->elements[i][j] = num;
        }
    }
}

void mrand(Mat*& mat){
    for(int i = 0; i < mat->m; i++){
        for(int j = 0; j < mat->n; j++){
            mat->elements[i][j] = (float)(rand()) / (float)(RAND_MAX / 2.0f) - 1.0f;
        }
    }
}

void add(Mat* a, Mat* b, Mat*& buff){
    for(int i = 0; i < a->m; i++){
        for(int j = 0; j < a->n; j++){
            buff->elements[i][j] = a->elements[i][j] + b->elements[i][j];
        }
    }
}

void sub(Mat* a, Mat* b, Mat*& buff){
    for(int i = 0; i < a->m; i++){
        for(int j = 0; j < a->n; j++){
            buff->elements[i][j] = a->elements[i][j] - b->elements[i][j];
        }
    }
}

void mul(Mat* a, Mat* b, Mat*& buff){
    for(int i = 0; i < a->m; i++){
        for(int j = 0; j < a->n; j++){
            buff->elements[i][j] = a->elements[i][j] * b->elements[i][j];
        }
    }
}

void dot(Mat* a, Mat* b, Mat*& buff){
    for(int i = 0; i < a->m; i++){
        for(int j = 0; j < b->n; j++){
            for(int k = 0; k < b->m; k++){
                buff->elements[i][j] += a->elements[i][k] * b->elements[k][j];
            }
        }
    }
}

void scale(Mat* mat, float scale, Mat*& buff){
    for(int i = 0; i < mat->m; i++){
        for(int j = 0; j < mat->n; j++){
            buff->elements[i][j] = mat->elements[i][j] * scale;
        }
    }
}

void transpose(Mat* mat, Mat*& buff){
    for(int i = 0; i < mat->m; i++){
        for(int j = 0; j < mat->n; j++){
            buff->elements[j][i] = mat->elements[i][j];
        }
    }
}
}
#endif

