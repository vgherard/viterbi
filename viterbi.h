# ifndef VITERBI_H
# define VITERBI_H

#include <vector>
#include "Matrix.h"

namespace viterbi {
        void initialize(
                Matrix<double> &,
                Matrix<size_t> &, 
                size_t, 
                const Matrix<double> &, 
                const std::vector<double> &
        );

        void forward_pass(
                Matrix<double> &,
                Matrix<size_t> &,
                const std::vector<size_t> &,
                const Matrix<double> &, 
                const Matrix<double> &
        ); 
        
        std::vector<size_t> optimal_path(
                        const std::vector<size_t> &,
                        const Matrix<double> &,
                        const std::vector<double> &,
                        const Matrix<double> &
                        );
} // namespace viterbi

#endif // VITERBI_H