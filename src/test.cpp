#include <Eigen/Core>
#include <iostream>

#include "asymleastsquare.hpp"

int main() {
    Eigen::VectorXd s(10);
    s << 0.1, 5, 10, 14, 26, 35, 47, 67, 78, 103;
    std::cout << s << std::endl << std::endl;

    Eigen::MatrixXd m(3, 9);
    m << 0.1, 5, 10, 14, 26, 35, 47, 67, 78, 0.2, 10, 20, 28, 52, 70, 94, 134,
        156, 0.3, 15, 30, 42, 78, 105, 141, 201, 234;
    Eigen::VectorXd b = m.row(1);

    AsymmetricLeastSquares als(5, 0.001, 10, 2);
    std::cout << als.get_baseline(s) << std::endl;
    std::cout << als.get_baselines(m) << std::endl;

    /*
    als.get_baseline(s);
    auto res = als.get_baseline(s);
    std::cout << res << std::endl;
    */

    return 0;
}