#include <pybind11/pybind11.h>
#include <pybind11/eigen.h>
#include <pybind11/stl.h>
#include <opencv2/core/eigen.hpp>
#include "../perception-traversability/src/traversability.hpp"

#define STRINGIFY(x) #x
#define MACRO_STRINGIFY(x) STRINGIFY(x)


namespace py = pybind11;

class TraversabilityPython : public traversability::Traversability {
    Eigen::MatrixXf traversability_map_eigen;
public:
    /* we need to provide an alternative method as the conversion from CV in C to numpy in Python is quite hard
       while the conversion from eigen to numpy is rather easy */
    void setElevationMapEigen(Eigen::MatrixXf elevation_map_eigen) {
        eigen2cv(elevation_map_eigen, elevation_map);
    }
    Eigen::MatrixXf getTraversabilityMapEigen() {
        cv2eigen(traversability_map, traversability_map_eigen);
        return traversability_map_eigen;
    }
};


PYBIND11_MODULE(traversability_pybind, m) {
    m.doc() = R"pbdoc(
        Pybind11 plugin for rock perception-traversability component
        -----------------------
        .. currentmodule:: traversability_pybind
        .. autosummary::
           __init__
           configure_traversability
           set_elevation_map_eigen
           compute_traversability
           get_traversability_map_eigen
    )pbdoc";

    py::class_<TraversabilityPython>(m, "Traversability")
        .def(py::init<>())
        .def("configure_traversability", &TraversabilityPython::configureTraversability)
        .def("set_elevation_map_std_vector", &TraversabilityPython::setElevationMapStdVector)
        .def("set_elevation_map_eigen", &TraversabilityPython::setElevationMapEigen)
        .def("compute_traversability", &TraversabilityPython::computeTraversability)
        .def("get_traversability_map_eigen", &TraversabilityPython::getTraversabilityMapEigen,
             py::return_value_policy::reference_internal)
        .def_readwrite("use_global_path_planner_convention", &TraversabilityPython::use_global_path_planner_convention)
        .def("local_2_global_orientation", &TraversabilityPython::local2globalOrientation)
        .def("local_2_global_orientation_legacy", &TraversabilityPython::local2globalOrientation_legacy)
        .def("show_traversability", &TraversabilityPython::showTraversability)
    ;

#ifdef VERSION_INFO
    m.attr("__version__") = MACRO_STRINGIFY(VERSION_INFO);
#else
    m.attr("__version__") = "dev";
#endif
}