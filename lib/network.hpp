#ifndef NETWORK_H
#define NETWORK_H

#include "matrix.hpp"

#define ALPHA 0.01
#define NET_FILE "data/net.data"

namespace net {
template <typename T>
struct Net {
	mat::Mat<T>* A0;

	mat::Mat<T>* W1;
	mat::Mat<T>* B1;
	mat::Mat<T>* Z1;
	mat::Mat<T>* A1;

	mat::Mat<T>* W2;
	mat::Mat<T>* B2;
	mat::Mat<T>* Z2;
	mat::Mat<T>* A2;

	mat::Mat<T>* W3;
	mat::Mat<T>* B3;
	mat::Mat<T>* Z3;
	mat::Mat<T>* A3;

	mat::Mat<T>* dW1;
	mat::Mat<T>* dB1;
	mat::Mat<T>* dW2;
	mat::Mat<T>* dB2;
	mat::Mat<T>* dW3;
	mat::Mat<T>* dB3;
	mat::Mat<T>* Y;
};

template <typename T>
void create(Net<T>& net, int A0, int A1, int A2, int A3){
    net.A0 = mat::create<T>(A0, 1);
    net.W1 = mat::create<T>(A1, A0);
    net.B1 = mat::create<T>(A1, 1);
    net.Z1 = mat::create<T>(A1, 1);
    net.A1 = mat::create<T>(A1, 1);
    net.W2 = mat::create<T>(A2, A1);
    net.B2 = mat::create<T>(A2, 1);
    net.Z2 = mat::create<T>(A2, 1);
    net.A2 = mat::create<T>(A2, 1);
    net.W3 = mat::create<T>(A3, A2);
    net.B3 = mat::create<T>(A3, 1);
    net.Z3 = mat::create<T>(A3, 1);
    net.A3 = mat::create<T>(A3, 1);
    net.dW1 =mat::create<T>(A1, A0);
    net.dB1 = mat::create<T>(A1, 1);
    net.dW2 = mat::create<T>(A2, A1);
    net.dB2 = mat::create<T>(A2, 1);
    net.dW3 = mat::create<T>(A3, A2);
    net.dB3 = mat::create<T>(A3, 1);
    net.Y = mat::create<T>(A3, 1);
}

template <typename T>
void load(const char* path, Net<T>& net){
    std::ifstream file(path, std::ios::in);
    int A0, A1, A2, A3, temp;
    file >> A0; file >> temp;
    file >> A1; file >> temp;
    file >> A2; file >> temp;
    file >> A3; file >> temp;
    create<T>(net, A0, A1, A2, A3);
    
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

template <typename T>
void save(const char* path, Net<T>& net){
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

template <typename T>
void rand(Net<T>& net){
    mat::mrand<T>(net.W1);
    mat::mrand<T>(net.W2);
    mat::mrand<T>(net.W3);
}

template <typename T>
void n_free(Net<T>& net){
    mat::free<T>(net.A0);
    mat::free<T>(net.W1);
    mat::free<T>(net.B1);
    mat::free<T>(net.Z1);
    mat::free<T>(net.A1);
    mat::free<T>(net.W2);
    mat::free<T>(net.B2);
    mat::free<T>(net.Z2);
    mat::free<T>(net.A2);
    mat::free<T>(net.W3);
    mat::free<T>(net.B3);
    mat::free<T>(net.Z3);
    mat::free<T>(net.A3);
    mat::free<T>(net.dW1);
    mat::free<T>(net.dB1);
    mat::free<T>(net.dW2);
    mat::free<T>(net.dB2);
    mat::free<T>(net.dW3);
    mat::free<T>(net.dB3);
    mat::free<T>(net.Y);
}

template <typename T>
T ReLU(T x){
    if(x < 0){ return 0; }
    return x;
}

template <typename T>
void activation(mat::Mat<T>*&, mat::Mat<T>*&){

}

template <typename T>
void dactivation(mat::Mat<T>*&, mat::Mat<T>*&){

}

template <typename T>
int argmax(mat::Mat<T>*& mat){
    int max = mat->elements[0][0];
    for(int i = 1; i < mat->m; i++){
        for(int j = 0; j < mat->n; j++){
            if(max < mat->elements[i][j]){ max = mat->elements[i][j]; }
        }
    }
    return max;
}

template <typename T>
void forward_prop(Net<T>&){

}

template <typename T>
void back_prop(Net<T>&){

}
}
#endif
