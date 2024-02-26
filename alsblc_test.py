from alsblc import ALSBaselineCorrection
import numpy as np
import datetime


def make_test_data(spectrum: np.ndarray, size: int) -> np.ndarray:
    coefs = np.random.rand(size)
    res = np.tile(spectrum, (size, 1))
    res *= coefs.reshape((size, 1))
    return res


if __name__ == '__main__':
    PARAM_LAMBDA = 100000
    PARAM_P = 0.001
    PARAM_ITERATION = 10
    TEST_SIZE = 200

    spectrum = np.load("./test/example.npy")

    spectra = make_test_data(spectrum, TEST_SIZE)
    als_eigen = ALSBaselineCorrection(
        PARAM_LAMBDA, PARAM_P, PARAM_ITERATION)
    print(f"Eigen single ({TEST_SIZE} spectra):")
    dt_start = datetime.datetime.now()
    for spectrum in spectra:
        baseline = als_eigen.get_baseline(spectrum)
    dt_delta = datetime.datetime.now() - dt_start
    time_single = dt_delta / TEST_SIZE
    print(time_single, "s/spectrum\n")

    als_eigen = ALSBaselineCorrection(
        PARAM_LAMBDA, PARAM_P, PARAM_ITERATION)
    print(f"Eigen multi ({TEST_SIZE} spectra):")
    dt_start = datetime.datetime.now()
    baselines = als_eigen.get_baselines(spectra)
    dt_delta = datetime.datetime.now() - dt_start
    time_single = dt_delta / TEST_SIZE
    print(time_single, "s/spectrum\n")
