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



Matrix solve_gradient(const Matrix &A_, const Matrix &B_){
    Matrix A = A_;
    Matrix B = B_;
    //resolution de AX = B;
    //tests de taille
    int n = A.rows;
    int q = A.cols;
    assert(A.cols == B.rows);
    //def de x0 = 0
    vect x_0;
    for(auto i = 0; i<q; ++i){x_0.push_back(0.);}
    Matrix x(x_0, q, 1); //p rows and 1 column for matrix x0;
    assert(x.cols == B.cols);
    assert(x.rows == B.rows);

    //r0 definition (first rest)
    Matrix r = B - A*x;
    //p0 definition, (first vector of orthonormal base (p0,...pn)
    Matrix p = r;
    int k = 0;
    while (1){
        //calculation of the "double" alpha = r.T * r / (p.T * A * p) 
        Matrix coef = r.transpose_1D() * r;
        double coef_val = coef.vals[0]; //numerateur
        Matrix coef2 = p.transpose_1D() * (A * p);
        double coef2_val = coef2.vals[0]; //denominateur
        double alpha = coef_val / coef2_val;

        //calculation of x = x + alpha * p 
        //x will converge to the result x
        x.verify_shapes(p*alpha);
        x = x + p * alpha;

        //calculation of r = A * x - B = r - alpha * A * p ;
        //r is the next rest. r will converge to the vector<double> 0.
        Matrix r_avt = r; //on sauvegarde r_(k-1) avant de calculer r
        r = r - A * p * alpha;
        if(r.norm_1D() < 0.000001){break;}

        //calculation of Beta = r.T * r / [r_(k-1).T * r_(k-1)]
        Matrix num = r.transpose_1D() * r;
        double num_val = num.vals[0];
        Matrix den = r_avt.transpose_1D() * r_avt ;
        double den_val = den.vals[0];
        double Beta = num_val / den_val;

        //calculation of next vector p = r + Beta*p
        r.verify_shapes(p);
        p = r + p * Beta;
        k++;
    }
    return x;
}



