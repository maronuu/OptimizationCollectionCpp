#include <simplex.hpp>


void Simplex::solve() {
    
}

void Simplex::show_ans() {
    std::cout << "A:\n"
            << A << "\n"
            << "b:\n"
            << b << "\n"
            << "c: \n"
            << c << "\n"
            << "Problem:\n"
            << "\t max c^T x\n"
            << "\t s.t. Ax <= b\n"
            << "\t       x >= 0\n"
            << "Result:\n"
            << "\t opt_x:\n"
            << "\t " << x_opt << "\n";
}

void Simplex::swap_NB(
    VectorXf &cB,
    VectorXf &cN,
    MatrixXf &B,
    MatrixXf &N,
    VectorXi &Nidx,
    VectorXi &Bidx,
    const int Bpos,
    const int Npos
) {
    float tmp_f = cN[Npos];
    cN[Npos] = cB[Bpos];
    B[Bpos] = tmp_f;

    VectorXf tmp_vec = N.col(Npos);
    N.col(Npos) = B.col(Bpos);
    B.col(Bpos) = tmp_vec;

    int tmp_i = Nidx[Npos];
    Nidx[Npos] = Bidx[Bpos];
    Bidx[Bpos] = tmp_i;
}

void Simplex::simplex(
    const VectorXf &cB_0,
    const VectorXf &cN_0,
    const MatrixXf &B_0,
    const MatrixXf &N_0,
    const VectorXi &Nidx_0,
    const VectorXi &Bidx_0
) {
    VectorXf cB = cB_0;
    VectorXf cN = cN_0;
    MatrixXf B = B_0;
    MatrixXf N = N_0;
    VectorXi Nidx = Nidx_0;
    VectorXi Bidx = Bidx_0;

    VectorXf b_bar;
    VectorXf cN_bar;
    VectorXf a_k_bar;
    VectorXf ratio;
    MatrixXf N_bar;
    while (1) {
        b_bar = B.inverse() * b;
        N_bar = B.inverse() * N;
        cN_bar = cN - N_bar.transpose() * cB;
        if (cN_bar.minCoeff() <= 0) {
            // all elements in cN_bar are non-positive
            // end
            optval = cB.transpose() * b_bar; // z = cB.T * b_bar + cN_bar.T * xN (xN=0)
            x_opt = b_bar; // x_opt = b_bar - N_bar * xN (xN = 0)
            return;
        }

        // choose any k where cN_bar[k] > 0
        int k = 0;
        while (1) {
            if (cN_bar(k) > 0) break;
            ++k;
        }

        a_k_bar = N_bar.col(k);
        if (a_k_bar.maxCoeff() <= 0) {
            opt_status = 1; // non limit
            return;
        }

        // max |b|
        int l;
        b_bar.minCoeff(&l);

        // swap
        swap_NB(cB, cN, B, N, Nidx, Bidx, l, k);
    }
}

void Simplex::calc_init_dict(
    const VectorXf &cB_0,
    const VectorXf &cN_0,
    const MatrixXf &B_0,
    const MatrixXf &N_0,
    const VectorXi &Nidx_0,
    const VectorXi &Bidx_0
) {
    // min b >= 0   ->   this args are feasible dict
    if (b.minCoeff() >= 0) return;

    // artificial variables
    VectorXf cB_art = cB_0;
    MatrixXf B_art = B_0;
    VectorXi Bidx_art = Bidx_0;

    
}