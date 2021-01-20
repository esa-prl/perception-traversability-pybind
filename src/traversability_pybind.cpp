#include <pybind11/pybind11.h>
#include <pybind11/eigen.h>
#include <pybind11/stl.h>
#include <opencv2/core/eigen.hpp>
#include "../perception-traversability/src/traversability.hpp"

#define STRINGIFY(x) #x
#define MACRO_STRINGIFY(x) STRINGIFY(x)


namespace py = pybind11;

class TraversabilityPython : public traversability::Traversability {
    Eigen::MatrixXf traversability_eigen;
public:
    /* we need to provide an alternative method as the conversion from CV in C to numpy in Python is quite hard
       while the conversion from eigen to numpy is rather easy */
    Eigen::MatrixXf &computeTraversabilityEigen() {
        cv::Mat traversability_cv = computeTraversability();
        cv2eigen(traversability_cv, traversability_eigen);
        return traversability_eigen;
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
           set_elevation_map
           compute_traversability
    )pbdoc";

    py::class_<TraversabilityPython>(m, "Traversability")
        .def(py::init<>())
        .def("configure_traversability", &TraversabilityPython::configureTraversability)
        .def("set_elevation_map", &TraversabilityPython::setElevationMap)
        .def("elevation_map_interpolate", &TraversabilityPython::elevationMapInterpolate)
        .def("elevation_map_2_slope_map", &TraversabilityPython::elevationMap2SlopeMap)
        .def("threshold_slope_map", &TraversabilityPython::thresholdSlopeMap)
        .def("dilate_traversability", &TraversabilityPython::dilateTraversability)
        .def("compute_traversability", &TraversabilityPython::computeTraversability)
        .def("compute_traversability_eigen", &TraversabilityPython::computeTraversabilityEigen,
             py::return_value_policy::reference_internal)
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