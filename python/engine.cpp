#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "../src/engine.hpp"

namespace py = pybind11;

void init_suit(py::module& m) {
    py::enum_<engine::Suit>(m, "Suit")
        .value("Spades", engine::Suit::Spades)
        .value("Hearts", engine::Suit::Hearts)
        .value("Clubs", engine::Suit::Clubs)
        .value("Diamonds", engine::Suit::Diamonds)
        .export_values();
}

//void init_card(py::module& m) {
//    py::class_<engine::Card>(m, "Card")
//        .def(py::init<std::string>(), py::arg("name"))
//        .def("get_name",
//            py::overload_cast<>(&vehicles::Motorcycle::get_name, py::const_))
//        .def("ride",
//            py::overload_cast<std::string>(&vehicles::Motorcycle::ride, py::const_),
//            py::arg("road"));
//}*/

namespace mcl {

    PYBIND11_MODULE(blackjackplusplus, m) {
        // Optional docstring
        m.doc() = "The blackjack-plusplus engine library";

        init_suit(m);
        //init_card(m);
    }
}