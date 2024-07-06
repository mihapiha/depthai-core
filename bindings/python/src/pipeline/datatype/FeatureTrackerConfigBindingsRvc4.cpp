#include "DatatypeBindings.hpp"
#include "pipeline/CommonBindings.hpp"
#include <unordered_map>
#include <memory>

// depthai
#include "depthai/pipeline/datatype/FeatureTrackerConfigRvc4.hpp"

//pybind
#include <pybind11/chrono.h>
#include <pybind11/numpy.h>

// #include "spdlog/spdlog.h"

void bind_featuretrackerconfigRvc4(pybind11::module& m, void* pCallstack){

    using namespace dai;

    // py::class_<RawFeatureTrackerConfig, RawBuffer, std::shared_ptr<RawFeatureTrackerConfig>> rawFeatureTrackerConfig(m, "RawFeatureTrackerConfig", DOC(dai, RawFeatureTrackerConfig));
    py::class_<FeatureTrackerConfigRvc4, Py<FeatureTrackerConfigRvc4>, Buffer, std::shared_ptr<FeatureTrackerConfigRvc4>> featureTrackerConfigRvc4(m, "FeatureTrackerConfigRvc4", DOC(dai, FeatureTrackerConfigRvc4));
    py::class_<FeatureTrackerConfigRvc4::CornerDetector> cornerDetector(featureTrackerConfigRvc4, "CornerDetector", DOC(dai, FeatureTrackerConfigRvc4, CornerDetector));
    py::enum_<FeatureTrackerConfigRvc4::CornerDetector::Type> cornerDetectorType(cornerDetector, "Type", DOC(dai, FeatureTrackerConfigRvc4, CornerDetector, Type));
    py::class_<FeatureTrackerConfigRvc4::CornerDetector::Thresholds> cornerDetectorThresholds(cornerDetector, "Thresholds", DOC(dai, FeatureTrackerConfigRvc4, CornerDetector, Thresholds));
    py::class_<FeatureTrackerConfigRvc4::MotionEstimator> motionEstimator(featureTrackerConfigRvc4, "MotionEstimator", DOC(dai, FeatureTrackerConfigRvc4, MotionEstimator));
    py::enum_<FeatureTrackerConfigRvc4::MotionEstimator::Type> motionEstimatorType(motionEstimator, "Type", DOC(dai, FeatureTrackerConfigRvc4, MotionEstimator, Type));
    py::class_<FeatureTrackerConfigRvc4::MotionEstimator::OpticalFlow> motionEstimatorOpticalFlow(motionEstimator, "OpticalFlow", DOC(dai, FeatureTrackerConfigRvc4, MotionEstimator, OpticalFlow));
    py::class_<FeatureTrackerConfigRvc4::FeatureMaintainer> featureMaintainer(featureTrackerConfigRvc4, "FeatureMaintainer", DOC(dai, FeatureTrackerConfigRvc4, FeatureMaintainer));

    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    // Call the rest of the type defines, then perform the actual bindings
    Callstack* callstack = (Callstack*) pCallstack;
    auto cb = callstack->top();
    callstack->pop();
    cb(m, pCallstack);
    // Actual bindings
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////

    // // Metadata / raw
    // rawFeatureTrackerConfig
    //     .def(py::init<>())
    //     .def_readwrite("cornerDetector", &FeatureTrackerConfigRvc4::cornerDetector, DOC(dai, FeatureTrackerConfigRvc4, cornerDetector))
    //     .def_readwrite("motionEstimator", &FeatureTrackerConfigRvc4::motionEstimator, DOC(dai, FeatureTrackerConfigRvc4, motionEstimator))
    //     .def_readwrite("featureMaintainer", &FeatureTrackerConfigRvc4::featureMaintainer, DOC(dai, FeatureTrackerConfigRvc4, featureMaintainer))
    //     ;

    cornerDetectorType
        .value("HARRIS", FeatureTrackerConfigRvc4::CornerDetector::Type::HARRIS)
    ;

    cornerDetectorThresholds
        .def(py::init<>())
        .def_readwrite("harrisScore", &FeatureTrackerConfigRvc4::CornerDetector::Thresholds::harrisScore, DOC(dai, FeatureTrackerConfigRvc4, CornerDetector, Thresholds, harrisScore))
        .def_readwrite("robustness", &FeatureTrackerConfigRvc4::CornerDetector::Thresholds::robustness, DOC(dai, FeatureTrackerConfigRvc4, CornerDetector, Thresholds, robustness))
        ;

    cornerDetector
        .def(py::init<>())
        .def_readwrite("type", &FeatureTrackerConfigRvc4::CornerDetector::type, DOC(dai, FeatureTrackerConfigRvc4, CornerDetector, type))
        .def_readwrite("numMaxFeatures", &FeatureTrackerConfigRvc4::CornerDetector::numMaxFeatures, DOC(dai, FeatureTrackerConfigRvc4, CornerDetector, numMaxFeatures))
        .def_readwrite("gradientFilterShift", &FeatureTrackerConfigRvc4::CornerDetector::gradientFilterShift, DOC(dai, FeatureTrackerConfigRvc4, CornerDetector, gradientFilterShift))
        .def_readwrite("descriptorLpf", &FeatureTrackerConfigRvc4::CornerDetector::descriptorLpf, DOC(dai, FeatureTrackerConfigRvc4, CornerDetector, descriptorLpf))
        .def_readwrite("thresholds", &FeatureTrackerConfigRvc4::CornerDetector::thresholds, DOC(dai, FeatureTrackerConfigRvc4, CornerDetector, thresholds))
        ;

    motionEstimatorType
        .value("HW_MOTION_ESTIMATION", FeatureTrackerConfigRvc4::MotionEstimator::Type::HW_MOTION_ESTIMATION)
    ;

    motionEstimatorOpticalFlow
        .def(py::init<>())
        .def_readwrite("pyramidLevels", &FeatureTrackerConfigRvc4::MotionEstimator::OpticalFlow::pyramidLevels, DOC(dai, FeatureTrackerConfigRvc4, MotionEstimator, OpticalFlow, pyramidLevels))
        .def_readwrite("searchWindowWidth", &FeatureTrackerConfigRvc4::MotionEstimator::OpticalFlow::searchWindowWidth, DOC(dai, FeatureTrackerConfigRvc4, MotionEstimator, OpticalFlow, searchWindowWidth))
        .def_readwrite("searchWindowHeight", &FeatureTrackerConfigRvc4::MotionEstimator::OpticalFlow::searchWindowHeight, DOC(dai, FeatureTrackerConfigRvc4, MotionEstimator, OpticalFlow, searchWindowHeight))
        .def_readwrite("epsilon", &FeatureTrackerConfigRvc4::MotionEstimator::OpticalFlow::epsilon, DOC(dai, FeatureTrackerConfigRvc4, MotionEstimator, OpticalFlow, epsilon))
        .def_readwrite("maxIterations", &FeatureTrackerConfigRvc4::MotionEstimator::OpticalFlow::maxIterations, DOC(dai, FeatureTrackerConfigRvc4, MotionEstimator, OpticalFlow, maxIterations))
        ;

    motionEstimator
        .def(py::init<>())
        .def_readwrite("enable", &FeatureTrackerConfigRvc4::MotionEstimator::enable, DOC(dai, FeatureTrackerConfigRvc4, MotionEstimator, enable))
        .def_readwrite("type", &FeatureTrackerConfigRvc4::MotionEstimator::type, DOC(dai, FeatureTrackerConfigRvc4, MotionEstimator, type))
        .def_readwrite("opticalFlow", &FeatureTrackerConfigRvc4::MotionEstimator::opticalFlow, DOC(dai, FeatureTrackerConfigRvc4, MotionEstimator, opticalFlow))
        ;

    featureMaintainer
        .def(py::init<>())
        .def_readwrite("enable", &FeatureTrackerConfigRvc4::FeatureMaintainer::enable, DOC(dai, FeatureTrackerConfigRvc4, FeatureMaintainer, enable))
        .def_readwrite("minimumDistanceBetweenFeatures", &FeatureTrackerConfigRvc4::FeatureMaintainer::minimumDistanceBetweenFeatures, DOC(dai, FeatureTrackerConfigRvc4, FeatureMaintainer, minimumDistanceBetweenFeatures))
        .def_readwrite("lostFeatureErrorThreshold", &FeatureTrackerConfigRvc4::FeatureMaintainer::lostFeatureErrorThreshold, DOC(dai, FeatureTrackerConfigRvc4, FeatureMaintainer, lostFeatureErrorThreshold))
        .def_readwrite("trackedFeatureThreshold", &FeatureTrackerConfigRvc4::FeatureMaintainer::trackedFeatureThreshold, DOC(dai, FeatureTrackerConfigRvc4, FeatureMaintainer, trackedFeatureThreshold))
        .def_readwrite("confidenceThreshold", &FeatureTrackerConfigRvc4::FeatureMaintainer::confidenceThreshold, DOC(dai, FeatureTrackerConfigRvc4, FeatureMaintainer, confidenceThreshold))
        ;

    // Message
    featureTrackerConfigRvc4
        .def(py::init<>())
        // .def(py::init<std::shared_ptr<FeatureTrackerConfigRvc4>>())

        .def("setCornerDetector", static_cast<FeatureTrackerConfigRvc4&(FeatureTrackerConfigRvc4::*)(dai::FeatureTrackerConfigRvc4::CornerDetector::Type)>(&FeatureTrackerConfigRvc4::setCornerDetector), py::arg("cornerDetector"), DOC(dai, FeatureTrackerConfigRvc4, setCornerDetector))
        .def("setCornerDetector", static_cast<FeatureTrackerConfigRvc4&(FeatureTrackerConfigRvc4::*)(dai::FeatureTrackerConfigRvc4::CornerDetector)>(&FeatureTrackerConfigRvc4::setCornerDetector), py::arg("config"), DOC(dai, FeatureTrackerConfigRvc4, setCornerDetector, 2))
        .def("setMotionEstimator", static_cast<FeatureTrackerConfigRvc4&(FeatureTrackerConfigRvc4::*)(bool)>(&FeatureTrackerConfigRvc4::setMotionEstimator), py::arg("enable"), DOC(dai, FeatureTrackerConfigRvc4, setMotionEstimator))
        .def("setMotionEstimator", static_cast<FeatureTrackerConfigRvc4&(FeatureTrackerConfigRvc4::*)(dai::FeatureTrackerConfigRvc4::MotionEstimator)>(&FeatureTrackerConfigRvc4::setMotionEstimator), py::arg("config"), DOC(dai, FeatureTrackerConfigRvc4, setMotionEstimator, 2))
        .def("setHwMotionEstimation", &FeatureTrackerConfigRvc4::setHwMotionEstimation, DOC(dai, FeatureTrackerConfigRvc4, setHwMotionEstimation))
        .def("setFeatureMaintainer", static_cast<FeatureTrackerConfigRvc4&(FeatureTrackerConfigRvc4::*)(bool)>(&FeatureTrackerConfigRvc4::setFeatureMaintainer), py::arg("enable"), DOC(dai, FeatureTrackerConfigRvc4, setFeatureMaintainer))
        .def("setFeatureMaintainer", static_cast<FeatureTrackerConfigRvc4&(FeatureTrackerConfigRvc4::*)(dai::FeatureTrackerConfigRvc4::FeatureMaintainer)>(&FeatureTrackerConfigRvc4::setFeatureMaintainer), py::arg("config"), DOC(dai, FeatureTrackerConfigRvc4, setFeatureMaintainer, 2))
        .def("setNumMaxFeatures", &FeatureTrackerConfigRvc4::setNumMaxFeatures, py::arg("numMaxFeatures"), DOC(dai, FeatureTrackerConfigRvc4, setNumMaxFeatures))
        .def("setHarrisCornerDetectorThreshold", &FeatureTrackerConfigRvc4::setHarrisCornerDetectorThreshold, py::arg("cornerDetectorThreshold"), DOC(dai, FeatureTrackerConfigRvc4, setHarrisCornerDetectorThreshold))
        .def("setHarrisCornerDetectorRobustness", &FeatureTrackerConfigRvc4::setHarrisCornerDetectorRobustness, py::arg("cornerDetectorRobustness"), DOC(dai, FeatureTrackerConfigRvc4, setHarrisCornerDetectorRobustness))
        .def("setConfidence", &FeatureTrackerConfigRvc4::setConfidence, py::arg("confidenceThreshold"), DOC(dai, FeatureTrackerConfigRvc4, setConfidence))
        .def("setFilterCoeffs", &FeatureTrackerConfigRvc4::setFilterCoeffs, py::arg("filterCoeffs"), DOC(dai, FeatureTrackerConfigRvc4, setFilterCoeffs))


        // .def("set", &FeatureTrackerConfigRvc4::set, py::arg("config"), DOC(dai, FeatureTrackerConfigRvc4, set))
        // .def("get", &FeatureTrackerConfigRvc4::get, DOC(dai, FeatureTrackerConfigRvc4, get))
        ;

    // add aliases
    m.attr("FeatureTrackerConfigRvc4").attr("CornerDetector") = m.attr("FeatureTrackerConfigRvc4").attr("CornerDetector");
    m.attr("FeatureTrackerConfigRvc4").attr("MotionEstimator") = m.attr("FeatureTrackerConfigRvc4").attr("MotionEstimator");
    m.attr("FeatureTrackerConfigRvc4").attr("FeatureMaintainer") = m.attr("FeatureTrackerConfigRvc4").attr("FeatureMaintainer");

}
