#include <vector>
#include <string>
#include <array>
#include <functional>
#include <iostream>
#include <cmath>
#include <fstream>

#pragma once
#include "Matrix.hpp"
#pragma once
#include "Gradient.hpp"

using vect = std::vector<double>;


void solve_Euler2(double dt = 0.0001, double dx = 0.01){
    //parametres initiaux
    double tf = 0.5;
    vect T0;
    for(double x = 0; x < 1; x += dx){
        T0.push_back(f(x));
    }
    vect::size_type N = T0.size();


    //code pour la matrice K 
    vect D;
    for(double x = 0; x < 1; x += 0.01){
        D.push_back(1.); //on 
    }
    vect K_vals(N*N);
    for(vect::size_type i = 0 ; i < N; ++i ){
        for(vect::size_type j = 0; j < N; ++j){
            if(j == i-1){ K_vals[i*N + j ] = D[i];}
            if(j == i){ K_vals[i*N + j ] = -D[i]-D[i+1];}
            if(j == i+1){ K_vals[i*N + j ] = D[i+1];}
        }
    }
    Matrix K(K_vals, N,N);
    K = K * (1/(dx*dx));

    //code pour une matrice identité In 
    vect I_vals(N*N);
    for(vect::size_type i = 0 ; i < N; ++i ){
        for(vect::size_type j = 0; j < N; ++j){
            if( i == j ) { I_vals[i*N + j] = 1;}
            else { I_vals[i*N + j] = 0;}
        }
    }
    Matrix I(I_vals, N, N);


    //calcul de la matrice A = I + dt * K
    Matrix A = I + K*dt;
    Matrix Tk(T0, N, 1);
    Matrix T(T0, N,1); //grande matrice dont les colonnes sont les T^(k)
    

    vect time {0.};
    double t = 0.;

    while(t < tf){
        t += dt;
        time.push_back(t);
        Tk = solve_gradient(A, Tk);
        T.append(Tk, 1);
    }
    std::ofstream file1;
    display_infile(file1, time, "time.txt");
    std::ofstream file2;
    display_infile(file2, T, "temperature.txt");
    std::ofstream size_file;
    double r = T.rows;
    double c = T.cols;
    std::vector<double> Tshape_ {r, c, dt};
    Matrix Tshape(Tshape_, 1,3); 
    display_infile(size_file, Tshape, "T_shape.txt");

    display("finish! T shape: "); T.print_shape(); 
    display("time shape: "); display(time.size());
}
