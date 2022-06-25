#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <fstream>

struct Mat {
    int m;
    int n;
    float** elements;
};

/*** Matrix utilities ***/
bool m_check(Mat*&, Mat*&);

Mat* m_create(int, int);
Mat* m_copy(Mat*);
void m_free(Mat*);

void m_save(const char*, Mat*);
Mat* m_load(const char*);

void m_fill(Mat*&, int);
void m_rand(Mat*&);

/*** Matrix operations ***/
void m_add(Mat*, Mat*, Mat*&);
void m_sub(Mat*, Mat*, Mat*&);
void m_mul(Mat*, Mat*, Mat*&);
void m_dot(Mat*, Mat*, Mat*&);
void m_scale(Mat*, float, Mat*&);
void m_T(Mat*, Mat*&);

#endif
