# ifndef VITERBI_H
# define VITERBI_H

#include <vector>
#include "Matrix.h"

namespace viterbi {
        std::vector<size_t> optimal_path(
                        const std::vector<size_t> &,
                        const Matrix<double> &,
                        const std::vector<double> &,
                        const Matrix<double> &
                        );
} // namespace viterbi

#endif // VITERBI_H