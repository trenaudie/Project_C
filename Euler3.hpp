#include <vector>
#include <string>
#include <array>
#include <functional>
#include <iostream>
#include <cmath>
#include <fstream>
#include <random>

#pragma once
#include "Matrix.hpp"

using vect = std::vector<double>;


double random_double(double min, double max){
        return sqrt((double)rand() / RAND_MAX) * (max-min) + min; // for generating random points between 0 to 1
    }

void solve_Euler3(double dt = 0.001, double dx = 0.01){
    //parametres initiaux
    double tf = 0.5;
    vect T0;
    for(double x = 0; x < 1; x += dx){
        T0.push_back(f(x));
    }
    vect::size_type N = T0.size();


    //code pour la matrice K 
    vect D;
    double min = 0.5;
    double max = 1.5;
    for(double x = 0; x < 1; x += 0.01){
        double d = random_double(min, max);
        D.push_back(d);
    }
    display(D);
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
    K = K * (1/(dx*dx));
    Matrix T(T0, N,1);
    vect time {0.};
    double t = 0.;

    while(t < tf){
        t += dt;
        time.push_back(t);
        Tk.substract((K*Tk) * dt);
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

    std::cout << std::endl;
    display("Resolution method finished");
    display("Temperature matrix T is of shape:");
    T.print_shape();

    //code pour une matrice T avec tf/dt lignes et N colonnes
    

}
