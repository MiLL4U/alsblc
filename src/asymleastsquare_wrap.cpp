#include <pybind11/eigen.h>
#include <pybind11/pybind11.h>

#include "asymleastsquare.hpp"

namespace py = pybind11;

PYBIND11_MODULE(alsblc, m) {
    py::class_<AsymmetricLeastSquares>(m, "AsymmetricLeastSquares")
        .def(py::init<float, float, int, int>())
        .def(py::init<float>())
        .def_property_readonly("lambda_", &AsymmetricLeastSquares::get_lambda)
        .def_property_readonly("p", &AsymmetricLeastSquares::get_p)
        .def_property_readonly("iteration", &AsymmetricLeastSquares::get_iteration)
        .def_property_readonly("order", &AsymmetricLeastSquares::get_order)
        .def_property_readonly("channels", &AsymmetricLeastSquares::get_channels)
        .def("get_baseline", &AsymmetricLeastSquares::get_baseline)
        .def("get_baselines", &AsymmetricLeastSquares::get_baselines);
}
