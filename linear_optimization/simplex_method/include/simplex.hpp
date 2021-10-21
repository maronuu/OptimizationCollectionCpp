#ifndef _SIMPLEX_HPP_
#define _SIMPLEX_HPP_

#include <iostream>
#include <algorithm>
#include <eigen3/Eigen/Core>
using namespace Eigen;


class Simplex {
private:
    MatrixXf A;
    VectorXf b, c;
    VectorXf x_opt;
    double optval;
    int opt_status; // 0 = have opt, 1 = non limit, 2 = non opt

    VectorXf cB_init;
    VectorXf cN_init;
    MatrixXf B_init;
    MatrixXf N_init;
    VectorXi Nidx_init;
    VectorXi Bidx_init;

public:
    Simplex(
        const MatrixXf &A_,
        const VectorXf &b_,
        const VectorXf &c_
    ) : A(A_), b(b_), c(c_) { }
    ~Simplex();
    
    MatrixXf get_A() { return A; }
    VectorXf get_b() { return b; }
    VectorXf get_c() { return c; }

    void solve();

    void show_ans();
    
    void swap_NB(
        VectorXf &cB,
        VectorXf &cN,
        MatrixXf &B,
        MatrixXf &N,
        VectorXi &Nidx,
        VectorXi &Bidx,
        const int Bpos,
        const int Npos
    );
    
    void simplex(
        const VectorXf &cB_0,
        const VectorXf &cN_0,
        const MatrixXf &B_0,
        const MatrixXf &N_0,
        const VectorXi &Nidx_0,
        const VectorXi &Bidx_0
    );

    void calc_init_dict(
        const VectorXf &cB_0,
        const VectorXf &cN_0,
        const MatrixXf &B_0,
        const MatrixXf &N_0,
        const VectorXi &Nidx_0,
        const VectorXi &Bidx_0
    );
};



#endif