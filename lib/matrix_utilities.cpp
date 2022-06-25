#include "matrix.hpp"

bool m_check(Mat*& a, Mat*& b){
    if(a->m == b->m && a->n == a->n){ return true; }
    return false;
}

Mat* m_create(int m, int n){
    Mat* mat = new Mat;
    mat->m = m; mat->n = n;
    mat->elements = new float*[m];
    for(int i = 0; i < m; i++){ mat->elements[i] = new float[n](); }
    return mat;
}

Mat* m_copy(Mat* mat){
    Mat* copy = m_create(mat->m, mat->n);
    for(int i = 0; i < mat->m; i++){
        for(int j = 0; j < mat->n; j++){
            copy->elements[i][j] = mat->elements[i][j];
        }
    }
    return copy;
}

void m_free(Mat* mat){
    for(int i = 0; i < mat->m; i++){ delete[] mat->elements[i]; }
    delete[] mat->elements;
    delete mat;
    mat = nullptr;
}

void m_save(const char* path, Mat* mat){
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

Mat* m_load(const char* path){
    std::ifstream file(path, std::ios::in);
    int m, n;
    file >> m; file >> n;
    Mat* mat = m_create(m, n);
    for(int i = 0; i < mat->m; i++){
        for(int j = 0; j < mat->n; j++){
            file >> mat->elements[i][j];
        }
    }
    file.close();
    return mat;
}

void m_fill(Mat*& mat, int num){
    for(int i = 0; i < mat->m; i++){
        for(int j = 0; j < mat->n; j++){
            mat->elements[i][j] = num;
        }
    }
}

void m_rand(Mat*& mat){
    for(int i = 0; i < mat->m; i++){
        for(int j = 0; j < mat->n; j++){
            mat->elements[i][j] = (float)(rand()) / (float)(RAND_MAX / 2.0f) - 1.0f;
        }
    }
}
