#include <vector>
#include <string>
#include <array>
#include <functional>
#include <iostream>
#include <typeinfo>


#include "Matrix.hpp"
#include "Euler1.hpp"
#include "Gradient.hpp"
#include "Euler2.hpp"
#include "Euler3.hpp"



void tests1_exo1(){
    vect v0 {0,0,0,0,0,0,0,0,0};
    vect v1 {0,0,1,0,1,0,1,0,0};
    vect v2 {1,2,3,4,5,6,7,8,9};

    
    Matrix m0(v0, 3,3); //matrice nulle
    Matrix m1(v1, 3,3 ); //matrice identite
    Matrix m2(v2, 3,3); //matrice qqconque

    std::cout << "m2: " << std::endl;
    display(m2);
    std::cout << "m1: " << std::endl;
    display(m1);

    display("\n quick operation tests: ");
    std::cout << "m2 * m1: " << std::endl;
    display(m2*m1);
    std::cout << "m2 * m0: " << std::endl;
    display(m2*m0);
    std::cout << "m2 + m1: " << std::endl;
    display(m2 + m1); 
    std::cout <<"m2 - 100.1*m1: " << std::endl;
    display(m2-m1*100.1);
    display("number of rows: "); display((m2-m1*100.1).rows);
    Matrix m3 = m2-m1*100.1;

    display("\nnew test");
    m3.append(m1, 1);
    display(m3);
    display("number of cols: "); display(m3.cols);
}

void tests2_exo1(){
    vect v0 {10,20,30,40,50,60};
    vect v1 {0,0,1,0,1,0,1,0,0};
    vect v2 {1,2,3,4,5,6,7,8,9};

    
    Matrix m0(v0); 
    Matrix m1(v1, 3,3 ); 
    Matrix m2(v2, 3,3); //matrice qqconque
    Matrix m3(m2[2], 3, 1 );

    std::cout << "m0 \n" << "shape: ("<< m0.rows <<", " << m0.cols << ") " <<std::endl;
    std::cout << "vals: "; display(m0);

    std::cout << "m1 \n" << "shape: ("<< m1.rows <<", " << m2.cols << ") " <<std::endl;
    std::cout << "vals: \n"; display(m1);

    std::cout << "m2: " << std::endl;
    display(m2);

    std::cout << "m1.append((m2*100) + 1); " << std::endl;
    m1.append((m2*100) + 1);
    display(m1);

    std::cout << "m1.append(m2*100 + 1); " << std::endl;
    m1.append(m2*100 + 1); //on rajoute une troisieme matrice : m2 * 100 + 1
    display(m1); //on remarque que l'operateur * précède l'operateur + 

    //qq tests en plus (fonction transpose et print_shape())
    display(m3);
    display(m2*m3);
    (m2*m3).print_shape();
    display(m3.transpose_1D() * m3);
    (m3.transpose_1D() * m3).print_shape();
    std::cout << 7*7 + 8*8 + 9*9 << std::endl; // on est bon
}

void tests_exo3(){
    vect v1 {1,0,0,0,1,0,0,0,1};
    Matrix A(v1, 3, 3); //matrice identité

    vect b1 {1,2,3}; 
    vect b2 {4,5,6}; 
    vect b3 {7,8,9};
    vect b4 {6,15,24};
    Matrix B1(b1, 3, 1);
    Matrix B2(b2, 3, 1);
    Matrix B3(b3, 3, 1);
    Matrix B4(b4, 3, 1);

    //creation d'une matrice A2 = np.arange(10).reshape((3,3))
    display("------ before A2 ------");
    Matrix B1_copy = B1.transpose_1D(); 
    B1_copy.append_vect1D(B2.transpose_1D()); 
    B1_copy.append_vect1D(B3.transpose_1D()); 
    Matrix A2 = B1_copy;
    display("A2", A2);
    display("A", A);


    //resolvons ax = b;
    Matrix X = solve_gradient(A,B1);
    display("AX = [1,2,3], solution: ", X);
    X = solve_gradient(A,B2);
    display("AX = [4,5,6], solution: ", X);
    X = solve_gradient(A,B3);
    display("AX = [7,8,9], solution: ", X);
    X = solve_gradient(A2, B4);
    display("AX = [6,15,24], solution: ", X);
    display("problem: on cherchait le vecteur [1,1,1], donc on est bon.");


}







int main(){
    
    //tests1_exo1(); //exo1 bon
    //tests2_exo1(); //append works
    //solve_Euler1(0.001, 0.15);
    //tests_exo3(); //la résolution par gradient conjugué fonctionne
    //solve_Euler2(0.001, 0.15);
    //solve_Euler3(0.001, 0.15);



}