#include <pybind11/pybind11.h>

#include "person.hpp"

namespace py = pybind11;

PYBIND11_MODULE(mymodule, m) {
    py::class_<Person>(m, "Person")
        .def(py::init<std::string, double, double>())
        .def_property("name", &Person::get_name, &Person::set_name)
        .def_property("height", &Person::get_height, &Person::set_height)
        .def_property("weight", &Person::get_weight, &Person::set_weight)
        .def("get_bmi", &Person::get_bmi)
        .def("set_name", &Person::set_name);
}
