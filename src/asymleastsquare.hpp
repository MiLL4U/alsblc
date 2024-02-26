#ifndef _ASYMLEASTSQUARE_HPP_
#define _ASYMLEASTSQUARE_HPP_
#ifndef _ASYMLEASTSQUARE_HPP_
#define _ASYMLEASTSQUARE_HPP_

#include <Eigen/Dense>
#include <Eigen/SparseCholesky>
#include <Eigen/SparseCore>

class AsymmetricLeastSquares {
    // parameters
    double m_lambda;
    double m_p;
    unsigned int m_iternum;
    unsigned int m_order;

    // setup
    size_t m_channels;

    // arrays used for computing
    Eigen::VectorXd m_spectrum, m_baseline, m_weights;
    Eigen::Vector<bool, Eigen::Dynamic> m_z_over_y;
    Eigen::SparseMatrix<double> m_W, m_lambDtD;

    // solver (Eigen)
    Eigen::SimplicialLDLT<Eigen::SparseMatrix<double>> m_solver;

    void init_arrays(const unsigned int &channels);
    void update_weights();
    void compute_baseline();

   public:
    AsymmetricLeastSquares(const double &lambda);
    AsymmetricLeastSquares(const double &lambda, const double &p,
                           const unsigned int &iteration,
                           const unsigned int &order);

    // properties
    double get_lambda() const;
    double get_p() const;
    unsigned int get_iteration() const;
    unsigned int get_order() const;
    unsigned long long get_channels() const;

    // public methods
    Eigen::VectorXd get_baseline(const Eigen::VectorXd &spectrum);
    Eigen::MatrixXd get_baselines(const Eigen::MatrixXd &spectra);
};

#endif /* _ASYMLEASTSQUARE_HPP_ */


#endif /* _ASYMLEASTSQUARE_HPP_ */
