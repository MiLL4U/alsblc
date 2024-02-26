#ifndef _DIFF_HPP_
#define _DIFF_HPP_
#ifndef _EIGEN_DIFF_H_
#define _EIGEN_DIFF_H_

#include <Eigen/Dense>
#include <Eigen/SparseCore>

template <typename Derived>
const typename Derived::PlainObject Diff(  // for dense matrix
    const Eigen::MatrixBase<Derived>& src_m, const unsigned int order = 1,
    const int dim = 0) {
    typename Derived::PlainObject res = src_m;
    int rows = src_m.rows(), cols = src_m.cols();
    if (dim == 1) {  // differentiate by columns
        for (int i = 0; i < order; i++) {
            int valid_cols = cols - i - 1;
            res.leftCols(valid_cols) =
                res.block(0, 1, rows, valid_cols) - res.leftCols(valid_cols);
        }

        return res.leftCols(cols - order);

    } else {  // differentiate by rows (default)
        for (int i = 0; i < order; i++) {
            int valid_rows = rows - i - 1;
            res.topRows(valid_rows) =
                res.block(1, 0, valid_rows, cols) - res.topRows(valid_rows);
        }
        return res.topRows(rows - order);
    }
}

template <typename Derived>
const typename Derived::PlainObject Diff(  // for sparse matrix
    const Eigen::SparseMatrixBase<Derived>& src_m, const unsigned int order = 1,
    const int dim = 0) {
    typename Derived::PlainObject res = src_m;
    if (dim == 1) {  // differentiate by columns
        int cols;
        for (int i = 0; i < order; i++) {
            cols = res.cols();
            res = (res.rightCols(cols - 1) - res.leftCols(cols - 1)).eval();
        }
    } else {  // differentiate by rows (default)
        int rows;
        for (int i = 0; i < order; i++) {
            rows = res.rows();
            res = (res.bottomRows(rows - 1) - res.topRows(rows - 1)).eval();
        }
    }

    return res;
}

#endif /* _EIGEN_DIFF_H_ */


#endif /* _DIFF_HPP_ */
