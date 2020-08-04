#include "cpp_library/Foo.h"
#include "cpp_library/sublibA/add.h"
#include "cpp_library/sublibA/ConsoleColors.h"
#include "cpp_library/NestedClasses.h"
#include "cpp_library/Inheritance.h"

#include <pybind11/pybind11.h>

namespace py = pybind11;

PYBIND11_MODULE(_core, m)
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


  auto pyOuter = py::class_<cpp_library::Outer> (m, "Outer");
  auto pyInner = py::class_<cpp_library::Outer::Inner> (pyOuter, "Inner");

  py::enum_<cpp_library::Outer::Inner::NestedEnum> (pyInner, "NestedEnum")
    .value("ONE", cpp_library::Outer::Inner::NestedEnum::ONE)
    .value("TWO", cpp_library::Outer::Inner::NestedEnum::TWO)
    ;

  py::class_<cpp_library::Base> pyBase(m, "Base");

  pyBase
    .def_readwrite("name", &cpp_library::Base::name);

  py::class_<cpp_library::Base::Inner>(pyBase, "Inner");

  py::class_<cpp_library::Derived, cpp_library::Base> (m, "Derived")
    .def_readwrite("count", &cpp_library::Derived::count);

  pyInner
    .def_readwrite("value", &cpp_library::Outer::Inner::value );

  pyOuter
    .def_readwrite("inner", &cpp_library::Outer::inner);

  py::register_exception<cpp_library::CppException>(m, "CppException");

}