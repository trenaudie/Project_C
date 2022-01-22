#include <vector>
#include <string>
#include <array>
#include <functional>
#include <iostream>
#include <cmath>
#include <fstream>

#pragma once
#include "Matrix.hpp"

using vect = std::vector<double>;


void solve_Euler1(double dt = 0.001, double dx = 0.1){
    //parametres initiaux
    double tf = 0.5;
    vect T0;
    for(double x = 0; x < 1; x += dx){
        T0.push_back(f(x));
    }
    vect::size_type N = T0.size();


    //code pour la matrice K 
    vect D;
    for(double x = 0; x < 1; x += dx){
        D.push_back(1);
    }
    vect values(N*N);
    
    for(vect::size_type i = 0 ; i < N; ++i ){
        for(vect::size_type j = 0; j < N; ++j){
            if(j == i-1){ values[i*N + j ] = D[i];}
            if(j == i){ values[i*N + j ] = -D[i]-D[i+1];}
            if(j == i+1){ values[i*N + j ] = D[i+1];}
        }
    }
    Matrix Tk(T0, N, 1);
    Matrix K(values, N,N);

    //qq tests rapides de D puis de K.
    display("K[5]: ");
    display(K[5]);
    display("K[5][5]: ");
    display(K[5][5]);

    display("after division dy dx**2:");
    K = K * (1/(dx*dx));
    display("K[5]: ");
    display(K[5]);

    //qq tests rapides
    assert(K[1][1] == K[2][2]);
    assert(K[1][2] == K[2][3]); 

    Matrix T(T0, N,1);
    vect time {0.};
    double t = 0.;

    while(t < tf){
        t += dt;
        time.push_back(t);
        Tk.substract((K*Tk) * dt);
        T.append_vect1D(Tk, 1);
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

    display("Euler numerical method finished");
    display("T is of shape: ");
    T.print_shape();



    //code pour une matrice T avec tf/dt lignes et N colonnes
    

}
