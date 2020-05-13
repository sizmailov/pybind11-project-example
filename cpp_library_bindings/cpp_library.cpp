#include "cpp_library/Foo.h"
#include "cpp_library/sublibA/add.h"
#include "cpp_library/sublibA/ConsoleColors.h"

#include <pybind11/pybind11.h>

namespace py = pybind11;

PYBIND11_MODULE(cpp_library_bindings, m)
{
  auto pyFoo = py::class_<cpp_library::Foo>(m,"Foo");
  pyFoo
    .def(py::init<>())
    .def("f",&cpp_library::Foo::f);

  py::class_<cpp_library::Foo::Child> (pyFoo, "FooChild")
    .def(py::init<>())
    .def("g",&cpp_library::Foo::Child::g);

  auto sublibA = m.def_submodule("sublibA");
  sublibA.def("add", cpp_library::sublibA::add);

  py::enum_<cpp_library::sublibA::ConsoleForegroundColor> (sublibA, "ConsoleForegroundColor")
    .value("Green", cpp_library::sublibA::ConsoleForegroundColor::Green)
    .value("Yellow", cpp_library::sublibA::ConsoleForegroundColor::Yellow)
    .value("Blue", cpp_library::sublibA::ConsoleForegroundColor::Blue)
    .value("Magenta", cpp_library::sublibA::ConsoleForegroundColor::Magenta)
    .export_values();

  py::enum_<cpp_library::sublibA::ConsoleBackgroundColor> (sublibA, "ConsoleBackgroundColor")
    .value("Green", cpp_library::sublibA::Green)
    .value("Yellow", cpp_library::sublibA::Yellow)
    .value("Blue", cpp_library::sublibA::Blue)
    .value("Magenta", cpp_library::sublibA::Magenta)
    .export_values();


}