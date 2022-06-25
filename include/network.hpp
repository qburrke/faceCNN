#ifndef NETWORK_H
#define NETWORK_H

#include "matrix.hpp"

#define ALPHA 0.01
#define NET_FILE "data/net.data"

struct Net {
	Mat* A0;

	Mat* W1;
	Mat* B1;
	Mat* Z1;
	Mat* A1;

	Mat* W2;
	Mat* B2;
	Mat* Z2;
	Mat* A2;

	Mat* W3;
	Mat* B3;
	Mat* Z3;
	Mat* A3;

	Mat* dW1;
	Mat* dB1;
	Mat* dW2;
	Mat* dB2;
	Mat* dW3;
	Mat* dB3;
	Mat* Y;
};

/*** Network utilities ***/
void n_create(Net&, int, int, int, int);
void n_load(const char*, Net&);
void n_save(const char*, Net&);
void n_rand(Net&);
void n_free(Net&);

/*** Network operations ***/
void activation(Mat*&, Mat*&);
void dactivation(Mat*&, Mat*&);
int argmax(Mat*&);
void forward_prop(Net&);
void back_prop(Net&);

#endif
