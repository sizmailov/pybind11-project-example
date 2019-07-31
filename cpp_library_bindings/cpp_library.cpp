#include "cpp_library/Foo.h"
#include <pybind11/pybind11.h>

namespace py = pybind11;

PYBIND11_MODULE(cpp_library_bindings, m)
{
  py::class_<cpp_library::Foo> (m,"Foo")
    .def(py::init<>())
    .def("f",&cpp_library::Foo::f);

}