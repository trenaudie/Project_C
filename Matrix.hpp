#include <vector>
#include <string>
#include <array>
#include <functional>
#include <iostream>
#include <fstream>
#include <cmath>
#pragma once

typedef std::vector<double> vect;

void display(const vect& v);
void display(const double &k);
void display(const std::string &s);
const double pi = 3.1415926535897932384;
double f(double x){return 0.5 + sin(2*pi*x) + 0.5 * cos(2*pi*x);}

class Matrix{
    public:
    Matrix();
    Matrix(vect v0, int r = 1, int c = 0): vals(v0), rows(r), cols(c){
        if(c == 0){cols = v0.size();}
        assert (rows * cols == v0.size()); 
        }
    vect vals;
    int rows; //number of rows
    int cols; //number of cols


    void add(const Matrix& m2){
        assert(vals.size() == m2.vals.size());
        Matrix m3(m2);
        for(vect::size_type i = 0; i < vals.size(); ++i ){
                vals[i] += m2.vals[i];}
        }
    Matrix operator+(const Matrix& m2){
        Matrix res(vals, rows, cols);
        res.add(m2);
        return res;}
    void add(const double &k){
        for(double &x: vals){x+=k;}}
    Matrix operator+(const double &k){
        Matrix res(vals, rows, cols);
        res.add(k);
        return res;
    }
    void substract(const Matrix& m2){
        assert(vals.size() == m2.vals.size());

        for(vect::size_type i = 0; i < rows * cols; ++i ){
            vals[i] -= m2.vals[i];
        }
    }
    Matrix operator-(const Matrix& m2){
        Matrix res(vals, rows, cols);
        res.substract(m2);
        return res;
    }
    void substract(const double &k){
        for(double &x: vals){x-=k;}}
    Matrix operator-(const double &k){
        Matrix res(vals, rows, cols);
        res.substract(k);
        return res;
    }
    void mult(const Matrix&  m2) {
        assert (cols == m2.rows );
        vect v2 = m2.vals;
        vect res(rows*m2.cols); //on reserve "rows*m2.cols" places dans le resultat
        for(auto i = 0; i<rows; ++i){
            for(auto j = 0; j<m2.cols; ++j){
                for(auto k = 0; k<cols; ++k){ res[i*m2.cols + j] += vals[i * cols + k]*m2.vals[k*m2.cols + j];}}}
        vals = res;
        cols = m2.cols;
    }
    Matrix operator*(const Matrix& m2){
        Matrix res(vals, rows, cols);
        res.mult(m2);
        return res;
    }
    void mult(const double &k){
        for(double &x: vals){x*=k;}}
    Matrix operator*(const double &k){
        Matrix res(vals, rows, cols);
        res.mult(k);
        return res;
    }
    double get(vect::size_type i, vect::size_type j){return vals[i*cols + j];}
    vect operator[](vect::size_type i){
        vect v2;
        for(auto j = 0; j < cols; ++j){v2.push_back(this -> get(i, j));}
        return v2;}
     
    void append_vect1D(const Matrix &m2, int axis = 0){
        //if axis = 0, same number of columns
        if(axis == 0){
            assert (m2.cols == cols);
            vals.insert(vals.end(), m2.vals.begin(), m2.vals.end());
            ++rows;
        }
        if(axis == 1){
            assert (m2.rows == rows);
            for(vect::size_type i = 0; i<rows; ++i){
                auto b = vals.begin() + cols;
                vals.insert(b + i*(cols + 1), m2.vals[i]);
            }
            ++cols;
        }
    }
    void append_vect1D(const vect &v, int axis = 0){
        //if axis = 0, same number of columns
        if(axis == 0){
            assert (v.size() == cols);
            vals.insert(vals.end(), v.begin(), v.end());
            ++rows;
        }
        if(axis == 1){
            assert (v.size() == rows);
            for(vect::size_type i = 0; i<rows; ++i){
                auto b = vals.begin() + cols;
                vals.insert(b + i*(cols + 1), v[i]);
            }
            ++cols;
        }
    }
    void append(const Matrix &m2, int axis = 0){
        Matrix m3(m2.vals, m2.rows, m2.cols);

        if(axis == 0){
            assert (m2.cols == cols);
            //add each row of m2 onto this
            for(auto i = 0; i< m2.rows; ++i){
                append_vect1D(m3[i], 0);
            }
        }
        if(axis == 1){
            assert (m2.rows == rows);
            //add each column of m3 onto this
            for(auto j= 0; j< m3.cols; ++j){
                //extract j_th colummn of m3 then add it to this
                vect col;
                for(auto i=0; i<rows; ++i){col.push_back(m3[i][j]);}
                append_vect1D(col, 1);
            }
        }
    }
    void print_shape(){
        std::cout << rows << "," << cols << std::endl;
    }
    Matrix transpose_1D(){
        assert(cols == 1 && rows > 1);//on a bien une matrice colonne 
        Matrix res(vals, cols, rows);
        return res; //on renvoie une matrix ligne (*this).T
    }
    double max(){
        assert(cols == 1 && rows > 1); //on a bien une matrice colonne 
        double max = vals[0];
        for(auto i = 1; i<rows; ++i){
            if( vals[i]>max){ max = vals[i];}
        }
        return max;
        }
    void verify_shapes(const Matrix &m2){
        assert(rows == m2.rows);
        assert(cols == m2.cols);
        assert(vals.size() == m2.vals.size());}
    double norm_1D(){
        assert(rows == 1 || cols == 1);
        double S = 0;
        for(auto x : vals){S+=x*x;}
        return sqrt(S);
    }
};

void display(const Matrix& m){
    assert( !m.vals.empty());
    for(vect::size_type i = 0 ; i < m.rows ; ++i){
        for(vect::size_type j = 0; j < m.cols; ++j){
            std::cout << m.vals[m.cols * i + j] << ' ';
            }
            std::cout << std::endl;
    }
}
void display(const vect& v){
    assert( !v.empty());
    for(vect::size_type i = 0 ; i < v.size(); ++i){ std::cout << v[i] << ' ';}
    std::cout << std::endl;}

void display(const double &k){
    std::cout << k << std::endl;
}

void display_infile(std::ofstream &os, const vect& v,const std::string &s){
    assert( !v.empty());
    os.open(s, std::ios::out);
    for(auto x:v){
        os << x << ' ';
    }
    os.close();
}
void display_infile(std::ofstream &os, const Matrix& M,const std::string &s){
    vect v = M.vals;
    assert( !v.empty());
    os.open(s, std::ios::out);
    for(auto x:v){
        os << x << ' ';
    }
    os.close();
}

void display(const std::string &s){
    std::cout << s << std::endl; 
}
void display(const std::string &s, const Matrix &m){
    display(s);
    display(m);
}