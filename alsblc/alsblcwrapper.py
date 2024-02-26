import numpy as np

from .alsblc import AsymmetricLeastSquares as CAsymmetricLeastSquares


class ALSBaselineCorrection:
    DEFAULT_P = 0.001
    DEFAULT_ITERATION = 10
    DEFAULT_ORDER = 2
    DTYPE = np.float64

    def __init__(self, lambda_: float,
                 p: float = DEFAULT_P,
                 iteration: int = DEFAULT_ITERATION,
                 order: int = DEFAULT_ORDER) -> None:
        self.__casymls = CAsymmetricLeastSquares(
            lambda_, p, iteration, order)

    @property
    def lambda_(self) -> float:
        return self.__casymls.lambda_

    @property
    def p(self) -> float:
        return self.__casymls.p

    @property
    def iteration(self) -> int:
        return self.__casymls.iteration

    @property
    def order(self) -> int:
        return self.__casymls.order

    @property
    def channels(self) -> int:
        return self.__casymls.channels

    def get_baseline(self, spectrum: np.ndarray) -> np.ndarray:
        if spectrum.ndim != 1:
            raise TypeError("spectrum must be 1-dimensional array (vector)")
        return self.__casymls.get_baseline(spectrum.astype(self.DTYPE))

    def get_baselines(self, spectra: np.ndarray) -> np.ndarray:
        if spectra.ndim != 2:
            raise TypeError(
                "spectra must be 2-dimensional array (array of vector)")
        return self.__casymls.get_baselines(spectra.astype(self.DTYPE))
