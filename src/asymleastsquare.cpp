#include "asymleastsquare.hpp"

#include <cassert>

#include "diff.hpp"

static const double DEFAULT_P = 0.001;
static const unsigned int DEFAULT_ITERATION = 10;
static const unsigned int DEFAULT_ORDER = 2;

// constructors
AsymmetricLeastSquares::AsymmetricLeastSquares(const double &lambda)
    : m_lambda(lambda),
      m_p(DEFAULT_P),
      m_iternum(DEFAULT_ITERATION),
      m_order(DEFAULT_ORDER) {}

AsymmetricLeastSquares::AsymmetricLeastSquares(const double &lambda,
                                               const double &p,
                                               const unsigned int &iteration,
                                               const unsigned int &order)
    : m_lambda(lambda), m_p(p), m_iternum(iteration), m_order(order) {}

// getters
double AsymmetricLeastSquares::get_lambda() const { return m_lambda; }
double AsymmetricLeastSquares::get_p() const { return m_p; }
unsigned int AsymmetricLeastSquares::get_iteration() const { return m_iternum; }
unsigned int AsymmetricLeastSquares::get_order() const { return m_order; }
unsigned long long AsymmetricLeastSquares::get_channels() const {
    return m_channels;
}

void AsymmetricLeastSquares::init_arrays(const unsigned int &channels) {
    m_channels = channels;

    // generate differentiation matrix
    Eigen::SparseMatrix<double> I, D;

    I.resize(m_channels, m_channels);
    I.setIdentity();
    D = Diff(I, m_order);
    m_lambDtD = m_lambda * (D.transpose() * D);
}

void AsymmetricLeastSquares::update_weights() {
    m_z_over_y = m_baseline.array() > m_spectrum.array();
    m_weights = (m_z_over_y.cast<double>().array() - m_p).cwiseAbs();
}

void AsymmetricLeastSquares::compute_baseline() {
    m_weights = Eigen::VectorXd::Ones(m_channels);  // initialize weights to 1
    for (int i = 0; i < m_iternum; i++) {           // compute ALS
        m_W = m_weights.asDiagonal();
        m_solver.compute(m_W + m_lambDtD);  // get argmin
        assert(m_solver.info() == Eigen::Success);

        m_baseline = m_solver.solve(m_W * m_spectrum);  // update baseline
        update_weights();
    }
}

// public methods
Eigen::VectorXd AsymmetricLeastSquares::get_baseline(
    const Eigen::VectorXd &spectrum) {
    size_t channels = spectrum.size();

    // initialize member variables if channel number of spectrum (y) changed
    if (channels != m_channels) {
        init_arrays(channels);
    }
    m_spectrum = spectrum;
    compute_baseline();

    return m_baseline;
}

Eigen::MatrixXd AsymmetricLeastSquares::get_baselines(
    const Eigen::MatrixXd &spectra) {
    size_t spectra_num = spectra.rows();
    size_t channels = spectra.cols();

    // initialize member variables if channel number of spectrum (y) changed
    if (channels != m_channels) {
        init_arrays(channels);
    }

    // calculate
    Eigen::MatrixXd res(spectra_num, channels);
    for (int row = 0; row < spectra_num; row++) {
        m_spectrum = spectra.row(row);
        compute_baseline();
        res.row(row) = m_baseline;
    }
    return res;
}
