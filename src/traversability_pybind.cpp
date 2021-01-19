#include <pybind11/pybind11.h>
#include <pybind11/eigen.h>
#include <pybind11/stl.h>
#include <opencv2/core/eigen.hpp>
#include "../perception-traversability/src/traversability.hpp"

#define STRINGIFY(x) #x
#define MACRO_STRINGIFY(x) STRINGIFY(x)


namespace py = pybind11;

class TraversabilityPython : public traversability::Traversability {
    // Eigen::Map<Eigen::Matrix<float, Eigen::Dynamic, Eigen::RowMajor>> big_mat = Eigen::MatrixXd::Zero(10000, 10000);
public:
    /* we need to provide an alternative method as the conversion from CV in C to numpy in Python is quite hard
       while the conversion from eigen to numpy is quite easy */
    Eigen::Map<Eigen::Matrix<float, Eigen::Dynamic, Eigen::RowMajor>> &computeTraversabilityEigen() {
        cv::Mat traversability_cv = computeTraversability();
        // std::cout << "cv rows " << traversability_cv.rows << " columns " << traversability_cv.cols << "/newline";
        Eigen::Map<Eigen::Matrix<float, Eigen::Dynamic, Eigen::RowMajor>> traversability_eigen(traversability_cv.ptr<float>(), traversability_cv.rows, traversability_cv.cols);
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
        .def("compute_traversability_eigen", &TraversabilityPython::computeTraversabilityEigen, py::return_value_policy::reference_internal)
        .def("local_2_global_orientation", &TraversabilityPython::local2globalOrientation)
        .def("local_2_global_orientation_legacy", &TraversabilityPython::local2globalOrientation_legacy)
    ;

#ifdef VERSION_INFO
    m.attr("__version__") = MACRO_STRINGIFY(VERSION_INFO);
#else
    m.attr("__version__") = "dev";
#endif
}