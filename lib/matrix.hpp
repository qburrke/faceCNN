#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <fstream>

namespace mat {
template <typename T>
struct Mat {
    int m;
    int n;
    T** elements;
};

template <typename T>
bool check(Mat<T>*& a, Mat<T>*& b){
    if(a->m == b->m && a->n == a->n){ return true; }
    return false;
}

template <typename T>
Mat<T>* create(const int& m, const int& n){
    auto mat = new Mat<T>;
    mat->m = m; mat->n = n;
    mat->elements = new T*[m];
    for(int i = 0; i < m; i++){ mat->elements[i] = new T[n](); }
    return mat;
}

template <typename T>
Mat<T>* copy(Mat<T>* mat){
    Mat<T>* copy = create<T>(mat->m, mat->n);
    for(int i = 0; i < mat->m; i++){
        for(int j = 0; j < mat->n; j++){
            copy->elements[i][j] = mat->elements[i][j];
        }
    }
    return copy;
}

template <typename T>
void free(Mat<T>* mat){
    for(int i = 0; i < mat->m; i++){ delete[] mat->elements[i]; }
    delete[] mat->elements;
    delete mat;
    mat = nullptr;
}

template <typename T>
void save(const char* path, Mat<T>* mat){
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

template <typename T>
Mat<T>* load(const char* path){
    std::ifstream file(path, std::ios::in);
    int m, n;
    file >> m; file >> n;
    Mat<T>* mat = create<T>(m, n);
    for(int i = 0; i < mat->m; i++){
        for(int j = 0; j < mat->n; j++){
            file >> mat->elements[i][j];
        }
    }
    file.close();
    return mat;
}

template <typename T>
void fill(Mat<T>*& mat, int num){
    for(int i = 0; i < mat->m; i++){
        for(int j = 0; j < mat->n; j++){
            mat->elements[i][j] = num;
        }
    }
}

template <typename T>
void mrand(Mat<T>*& mat){
    for(int i = 0; i < mat->m; i++){
        for(int j = 0; j < mat->n; j++){
            mat->elements[i][j] = (T)(rand()) / (T)(RAND_MAX / 2.0f) - 1.0f;
        }
    }
}

template <typename T>
void add(Mat<T>* a, Mat<T>* b, Mat<T>*& buff){
    for(int i = 0; i < a->m; i++){
        for(int j = 0; j < a->n; j++){
            buff->elements[i][j] = a->elements[i][j] + b->elements[i][j];
        }
    }
}

template <typename T>
void sub(Mat<T>* a, Mat<T>* b, Mat<T>*& buff){
    for(int i = 0; i < a->m; i++){
        for(int j = 0; j < a->n; j++){
            buff->elements[i][j] = a->elements[i][j] - b->elements[i][j];
        }
    }
}

template <typename T>
void mul(Mat<T>* a, Mat<T>* b, Mat<T>*& buff){
    for(int i = 0; i < a->m; i++){
        for(int j = 0; j < a->n; j++){
            buff->elements[i][j] = a->elements[i][j] * b->elements[i][j];
        }
    }
}

template <typename T>
void dot(Mat<T>* a, Mat<T>* b, Mat<T>*& buff){
    for(int i = 0; i < a->m; i++){
        for(int j = 0; j < b->n; j++){
            for(int k = 0; k < b->m; k++){
                buff->elements[i][j] += a->elements[i][k] * b->elements[k][j];
            }
        }
    }
}

template <typename T>
void scale(Mat<T>* mat, float scale, Mat<T>*& buff){
    for(int i = 0; i < mat->m; i++){
        for(int j = 0; j < mat->n; j++){
            buff->elements[i][j] = mat->elements[i][j] * scale;
        }
    }
}

template <typename T>
void transpose(Mat<T>* mat, Mat<T>*& buff){
    for(int i = 0; i < mat->m; i++){
        for(int j = 0; j < mat->n; j++){
            buff->elements[j][i] = mat->elements[i][j];
        }
    }
}
}
#endif
