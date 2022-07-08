#ifndef NETWORK_H
#define NETWORK_H

#include "matrix.hpp"

#define ALPHA 0.01
#define NET_FILE "data/net.data"

namespace net {
struct Net {
	mat::Mat* A0;

	mat::Mat* W1;
	mat::Mat* B1;
	mat::Mat* Z1;
	mat::Mat* A1;

	mat::Mat* W2;
	mat::Mat* B2;
	mat::Mat* Z2;
	mat::Mat* A2;

	mat::Mat* W3;
	mat::Mat* B3;
	mat::Mat* Z3;
	mat::Mat* A3;

	mat::Mat* dW1;
	mat::Mat* dB1;
	mat::Mat* dW2;
	mat::Mat* dB2;
	mat::Mat* dW3;
	mat::Mat* dB3;
	mat::Mat* Y;
};

void create(Net& net, int A0, int A1, int A2, int A3){
    net.A0 = mat::create(A0, 1);
    net.W1 = mat::create(A1, A0);
    net.B1 = mat::create(A1, 1);
    net.Z1 = mat::create(A1, 1);
    net.A1 = mat::create(A1, 1);
    net.W2 = mat::create(A2, A1);
    net.B2 = mat::create(A2, 1);
    net.Z2 = mat::create(A2, 1);
    net.A2 = mat::create(A2, 1);
    net.W3 = mat::create(A3, A2);
    net.B3 = mat::create(A3, 1);
    net.Z3 = mat::create(A3, 1);
    net.A3 = mat::create(A3, 1);
    net.dW1 =mat::create(A1, A0);
    net.dB1 = mat::create(A1, 1);
    net.dW2 = mat::create(A2, A1);
    net.dB2 = mat::create(A2, 1);
    net.dW3 = mat::create(A3, A2);
    net.dB3 = mat::create(A3, 1);
    net.Y = mat::create(A3, 1);
}

void load(const char* path, Net& net){
    std::ifstream file(path, std::ios::in);
    int A0, A1, A2, A3, temp;
    file >> A0; file >> temp;
    file >> A1; file >> temp;
    file >> A2; file >> temp;
    file >> A3; file >> temp;
    create(net, A0, A1, A2, A3);
    
    for(int i = 0; i < A1; i++){
        for(int j = 0; j < A0; j++){ file >> net.W1->elements[i][j]; }
    } for(int i = 0; i < A1; i++){ file >> net.B1->elements[i][0]; }

    for(int i = 0; i < A2; i++){
        for(int j = 0; j < A1; j++){ file >> net.W2->elements[i][j]; }
    } for(int i = 0; i < A2; i++){ file >> net.B2->elements[i][0]; }
    
    for(int i = 0; i < A3; i++){
        for(int j = 0; j < A2; j++){ file >> net.W3->elements[i][j]; }
    } for(int i = 0; i < A3; i++){ file >> net.B3->elements[i][0]; }
    
    file.close();
}

void save(const char* path, Net& net){
    std::ofstream file(path, std::ios::out);
    file << net.A0->m; file << " "; file << net.A0->n; file << " ";
    file << net.A1->m; file << " "; file << net.A1->n; file << " ";
    file << net.A2->m; file << " "; file << net.A2->n; file << " ";
    file << net.A3->m; file << " "; file << net.A3->n; file << "\n";
    
    for(int i = 0; i < net.A1->m; i++){
        for(int j = 0; j < net.A0->m; j++){ file << net.W1->elements[i][j]; file << " "; }
        file << "\n";
    } for(int i = 0; i < net.A1->m; i++){ file << net.B1->elements[i][0]; file << " "; }

    for(int i = 0; i < net.A2->m; i++){
        for(int j = 0; j < net.A1->m; j++){ file << net.W2->elements[i][j]; file << " "; }
        file << "\n";
    } 
    for(int i = 0; i < net.A2->m; i++){ file << net.B2->elements[i][0]; file << " "; }
    
    for(int i = 0; i < net.A3->m; i++){
        for(int j = 0; j < net.A2->m; j++){ file << net.W3->elements[i][j]; file << " "; }
        file << "\n";
    } for(int i = 0; i < net.A3->m; i++){ file << net.B3->elements[i][0]; file << " "; }
    
    file.close();
}

void rand(Net& net){
    mat::mrand(net.W1);
    mat::mrand(net.W2);
    mat::mrand(net.W3);
}

void n_free(Net& net){
    mat::free(net.A0);
    mat::free(net.W1);
    mat::free(net.B1);
    mat::free(net.Z1);
    mat::free(net.A1);
    mat::free(net.W2);
    mat::free(net.B2);
    mat::free(net.Z2);
    mat::free(net.A2);
    mat::free(net.W3);
    mat::free(net.B3);
    mat::free(net.Z3);
    mat::free(net.A3);
    mat::free(net.dW1);
    mat::free(net.dB1);
    mat::free(net.dW2);
    mat::free(net.dB2);
    mat::free(net.dW3);
    mat::free(net.dB3);
    mat::free(net.Y);
}

float ReLU(float x){
    if(x < 0){ return 0; }
    return x;
}

void activation(mat::Mat*&, mat::Mat*&){

}

void dactivation(mat::Mat*&, mat::Mat*&){

}

int argmax(mat::Mat*& mat){
    int max = mat->elements[0][0];
    for(int i = 1; i < mat->m; i++){
        for(int j = 0; j < mat->n; j++){
            if(max < mat->elements[i][j]){ max = mat->elements[i][j]; }
        }
    }
    return max;
}

void forward_prop(Net&){

}

void back_prop(Net&){

}
}
#endif
