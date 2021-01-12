#ifndef MATRIX_H
#define MATRIX_H

#include <vector>

template<class T>
class Matrix {
        size_t nrow_, ncol_;
        std::vector<T> mat_;
public:
        Matrix (size_t nrow = 0, size_t ncol = 0)
                : nrow_(nrow), ncol_(ncol), mat_(std::vector<T>(nrow * ncol)) {}
        Matrix (std::vector<T>, size_t nrow, size_t ncol, bool byrow = false);
        T& operator ()(size_t i, size_t j) {
                if (i > nrow_ - 1) throw; 
                if (j > ncol_ - 1) throw;
                return mat_[i + nrow_ * j];
        }
        const T& operator ()(size_t i, size_t j) const {
                if (i > nrow_ - 1) throw; 
                if (j > ncol_ - 1) throw;
                return mat_[i + nrow_ * j];
        }
        size_t nrow() const {return nrow_;}
        size_t ncol() const {return ncol_;}
        Matrix transpose () const {return Matrix(mat_, ncol_, nrow_, true);}
};

template<class T>
Matrix<T>::Matrix (std::vector<T> x, size_t nrow, size_t ncol, bool byrow) 
        : nrow_(nrow), ncol_(ncol), mat_(nrow * ncol)
{
        if (x.size() != nrow * ncol) throw;
        
        // Define a mapping between (i, j) -> x[ROW * i + COL * j]
        size_t ROW = 1, COL = nrow;
        if (byrow) 
                ROW = ncol, COL = 1;
        for (size_t i = 0; i < nrow; ++i)
                for (size_t j = 0; j < ncol; ++j)
                        // mat_[i + nrow * j] will be m(i, j)
                        mat_[i + nrow * j] = x[ROW * i + COL * j];
}

#endif // MATRIX_H