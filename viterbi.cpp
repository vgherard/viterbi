//' Viterbi algorithm.
//' 
//' Given a path 'y' in the observable space of an hidden Markov model, 
//' compute the path 'x' in hidden space which maximises the joint probability
//' Prob(x, y).
//'
//' Variables:
//'     - y. Input path in observable space:
//'             y[i - 1] = y_i
//'     - x. Output (optimal) path in hidden space:
//'             x[i - 1] = x_i
//'     - T. Hidden space transition log-probability matrix:
//'             T(i - 1, j - 1) = log(Prob(h_i <- h_j))
//'     - s. Starting log-probability vector: 
//'             s[i - 1] = log(Prob(h_i <- h_0))
//'     - E. Emission log-probability matrix: 
//'             E(i - 1, j - 1) = log(Prob(o_i <- h_j))
//'     - P. P-matrix of Viterbi algorithm:
//'             P(i - 1, l - 1) = 
//'                     max log-Prob of a path of length l ending at i
//'     - X: X-matrix of Viterbi algorithm:
//'             X(i - 1, l - 1) = 
//'                     previous hidden state in the optimal path above 
//'

#include "viterbi.h"
#include <cmath>
#include <limits>
#include <iostream>

namespace viterbi {

        // Initialize the first column of the P-matrix from the given start and 
        // emission probabilities 
        void initialize(
                Matrix<double> & P,
                size_t y_1, 
                const Matrix<double> & E, 
                const std::vector<double> & s
        ) 
        {
                for (size_t i = 0; i < s.size(); ++i) {
                        P(i, 0) = E(y_1, i) + s[i];
                }
        } // viterbi::initialize

        // Fill P- and X- matrices recursively
        void forward_pass(
                Matrix<double> & P,
                Matrix<size_t> & X,
                const std::vector<size_t> & y,
                const Matrix<double> & T, 
                const Matrix<double> & E
        ) 
        {
                double m_inf = -std::numeric_limits<double>::infinity();
                size_t L = y.size(), H = X.nrow();
                double tmp;
                // P(i, l) = E(y[l], i) + max_j (T(i, j) + P(j, l - 1))
                // X(i, l) = argmax_j (T(i, j) + P(j, l - 1))
                for (size_t l = 1; l < L; ++l) {
                        for (size_t i = 0; i < H; ++i) {
                                P(i, l) = m_inf;
                                for (size_t j = 0; j < H; ++j) {
                                        tmp = T(i, j) + P(j, l - 1);
                                        if (tmp > P(i, l)) {
                                                P(i, l) = tmp;
                                                X(i, l) = j;
                                        }
                                }
                                P(i, l) += E(y[l], i);
                        }
                }
        } // viterbi::forward_pass

        void backward_pass(
                Matrix<double> & P,
                Matrix<size_t> & X,
                std::vector<size_t> & x
        )
        {
                size_t L = X.ncol(), H = X.nrow();
                double best_prob = -std::numeric_limits<double>::infinity();
                double tmp;
                
                // x(L) = argmax_i P(i, L)
                for (size_t i = 0; i < H; ++i) {
                        tmp = P(i, L - 1);
                        if (tmp > best_prob) {
                                best_prob = tmp;
                                x[L - 1] = i;
                        }
                }
                
                // x(l) = X(x(l + 1), l + 1)    (for all l < L) 
                for (size_t k = 1; k < L; ++k) {
                        x[L - k - 1] = X(x[L - k], L - k);
                }
        } // viterbi::backward_pass

        std::vector<size_t> optimal_path(
                const std::vector<size_t> & y,
                const Matrix<double> & T,
                const std::vector<double> & s,
                const Matrix<double> & E
        )
        {
                Matrix<double> P(T.nrow(), y.size());
                Matrix<size_t> X(T.nrow(), y.size());
                std::vector<size_t> x(y.size());
        
                initialize(P, y[0], E, s);
                forward_pass(P, X, y, T, E);
                backward_pass(P, X, x);
        
                return x;
        } // viterbi::optimal_path

} // namespace viterbi