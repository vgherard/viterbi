#include "viterbi.h"
#include <iostream>
#include <cmath>

using std::cout;
using std::cin;
using std::vector;

int main() {
        size_t H;
        cout << "Enter dimension 'H' of hidden state space.\n" << "H: > ";
        cin >> H;
        cout << "Hidden state space: {h_1, h_2, ..., h_" << H << "}\n"; 
        
        cout << "\nEnter transition probabilities.\n";
        Matrix<double> T(H, H);
        double p;
        for (size_t j = 0; j < H; ++j) {
                for (size_t i = 0; i < H; ++i) {
                        cout << "Pr(h_" << i + 1 << " <- h_" << j + 1 << ")" <<
                                ": > ";
                        cin >> p;
                        T(i, j) = log(p);
                }
        }
        
        cout << "\nEnter starting probabilities.\n";
        vector<double> s(H);
        for (size_t i = 0; i < H; ++i) {
                cout << "Pr(h_" << i + 1 << " <- .): > ";
                cin >> p;
                s[i] = log(p);
        }
        
        
        size_t O;
        cout << "\nEnter dimension 'O' of observable state space.\n" << "O: > ";
        cin >> O;
        cout << "Observable state space: {o_1, o_2, ..., o_" << O << "}\n";
        
        cout << "\nEnter emission probabilities.\n";
        Matrix<double> E(O, H);
        for (size_t j = 0; j < H; ++j) {
                for (size_t i = 0; i < O; ++i) {
                        cout << "Pr(o_" << i + 1 << " <- h_" << j + 1 << ")" <<
                                ": > ";
                        cin >> p;
                        E(i, j) = log(p);
                }
        }
        
        size_t L;
        cout << "\nEnter length of path in observable space.\n" << "L: > ";
        cin >> L;
        
        size_t y_tmp;
        vector<size_t> y(L);
        cout << "\nEnter path in observable space.\n";
        for (size_t l = 0; l < L; ++l) {
                cout << "y(" << l + 1 << ") > ";
                cin >> y_tmp;
                while (y_tmp > O) {
                        cout << "Error: input is larger than " << O << ".\n";
                        cout << "y(" << l + 1 << "): > ";
                        cin >> y_tmp;
                }
                y[l] = y_tmp - 1;
        }
        
        cout << "\nComputing optimal path in hidden space...\n";
        vector<size_t> x = viterbi::optimal_path(y, T, s, E);
        cout << "\nx = (";
        for (size_t l = 0; l < L - 1; ++l) {
                cout << x[l] + 1 << ", ";
        }
        cout << x[L - 1] + 1 << ")\n";
        return 0;
}