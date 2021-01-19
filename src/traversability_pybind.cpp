#include <pybind11/pybind11.h>
#include <pybind11/eigen.h>
#include <pybind11/stl.h>
#include "../perception-traversability/src/traversability.hpp"

#define STRINGIFY(x) #x
#define MACRO_STRINGIFY(x) STRINGIFY(x)


namespace py = pybind11;

PYBIND11_MODULE(traversability_pybind, m) {
    m.doc() = R"pbdoc(
        Pybind11 plugin for rock perception-traversability component
        -----------------------
        .. currentmodule:: traversability_pybind
        .. autosummary::
           __init__
           configure_traversability
           set_elevation_map
           compute_traversability
    )pbdoc";

    py::class_<traversability::Traversability>(m, "Traversability")
        .def(py::init<>())
        .def("configure_traversability", &traversability::Traversability::configureTraversability)
        .def("set_elevation_map", &traversability::Traversability::setElevationMap)
        .def("elevation_map_interpolate", &traversability::Traversability::elevationMapInterpolate)
        .def("elevation_map_2_slope_map", &traversability::Traversability::elevationMap2SlopeMap)
        .def("threshold_slope_map", &traversability::Traversability::thresholdSlopeMap)
        .def("dilate_traversability", &traversability::Traversability::dilateTraversability)
        .def("compute_traversability", &traversability::Traversability::computeTraversability)
        .def("local_2_global_orientation", &traversability::Traversability::local2globalOrientation)
        .def("local_2_global_orientation_legacy", &traversability::Traversability::local2globalOrientation_legacy);

#ifdef VERSION_INFO
    m.attr("__version__") = MACRO_STRINGIFY(VERSION_INFO);
#else
    m.attr("__version__") = "dev";
#endif
}