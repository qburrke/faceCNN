#include "network.hpp"

void n_create(Net& net, int A0, int A1, int A2, int A3){
    net.A0 = m_create(A0, 1);
    net.W1 = m_create(A1, A0);
    net.B1 = m_create(A1, 1);
    net.Z1 = m_create(A1, 1);
    net.A1 = m_create(A1, 1);
    net.W2 = m_create(A2, A1);
    net.B2 = m_create(A2, 1);
    net.Z2 = m_create(A2, 1);
    net.A2 = m_create(A2, 1);
    net.W3 = m_create(A3, A2);
    net.B3 = m_create(A3, 1);
    net.Z3 = m_create(A3, 1);
    net.A3 = m_create(A3, 1);
    net.dW1 = m_create(A1, A0);
    net.dB1 = m_create(A1, 1);
    net.dW2 = m_create(A2, A1);
    net.dB2 = m_create(A2, 1);
    net.dW3 = m_create(A3, A2);
    net.dB3 = m_create(A3, 1);
    net.Y = m_create(A3, 1);
}

void n_load(const char* path, Net& net){
    std::ifstream file(path, std::ios::in);
    int A0, A1, A2, A3, temp;
    file >> A0; file >> temp;
    file >> A1; file >> temp;
    file >> A2; file >> temp;
    file >> A3; file >> temp;
    std::cout << A0 << " " << A1 << " " << A2 << " " << A3 << std::endl;
    n_create(net, A0, A1, A2, A3);
    
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

void n_save(const char* path, Net& net){
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

void n_rand(Net& net){
    m_rand(net.W1);
    m_rand(net.W2);
    m_rand(net.W3);
}

void n_free(Net& net){
    m_free(net.A0);
    m_free(net.W1);
    m_free(net.B1);
    m_free(net.Z1);
    m_free(net.A1);
    m_free(net.W2);
    m_free(net.B2);
    m_free(net.Z2);
    m_free(net.A2);
    m_free(net.W3);
    m_free(net.B3);
    m_free(net.Z3);
    m_free(net.A3);
    m_free(net.dW1);
    m_free(net.dB1);
    m_free(net.dW2);
    m_free(net.dB2);
    m_free(net.dW3);
    m_free(net.dB3);
    m_free(net.Y);
}
