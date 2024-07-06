#include "NodeBindings.hpp"
#include "Common.hpp"

#include "depthai/pipeline/Pipeline.hpp"
#include "depthai/pipeline/Node.hpp"
#include "depthai/pipeline/node/FeatureTrackerRvc4.hpp"


void bind_featuretrackerRvc4(pybind11::module& m, void* pCallstack){

    using namespace dai;
    using namespace dai::node;

    // Node and Properties declare upfront
    py::class_<FeatureTrackerPropertiesRvc4> featureTrackerProperties(m, "FeatureTrackerPropertiesRvc4", DOC(dai, FeatureTrackerPropertiesRvc4));
    auto featureTracker = ADD_NODE(FeatureTrackerRvc4);

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

    // FeatureTrackerRvc4 properties
    featureTrackerProperties
        .def_readwrite("initialConfig", &FeatureTrackerPropertiesRvc4::initialConfig, DOC(dai, FeatureTrackerPropertiesRvc4, initialConfig))
        ;

    // FeatureTrackerRvc4 Node
    featureTracker
        .def_readonly("inputConfig", &FeatureTrackerRvc4::inputConfig, DOC(dai, node, FeatureTrackerRvc4, inputConfig))
        .def_readonly("inputImage", &FeatureTrackerRvc4::inputImage, DOC(dai, node, FeatureTrackerRvc4, inputImage))
        .def_readonly("outputFeatures", &FeatureTrackerRvc4::outputFeatures, DOC(dai, node, FeatureTrackerRvc4, outputFeatures))
        .def_readonly("passthroughInputImage", &FeatureTrackerRvc4::passthroughInputImage, DOC(dai, node, FeatureTrackerRvc4, passthroughInputImage))
        .def_readonly("initialConfig", &FeatureTrackerRvc4::initialConfig, DOC(dai, node, FeatureTrackerRvc4, initialConfig))

        .def("setWaitForConfigInput", [](FeatureTrackerRvc4& obj, bool wait){
            // Issue a deprecation warning
            PyErr_WarnEx(PyExc_DeprecationWarning, "Use 'inputConfig.setWaitForMessage()' instead", 1);
            HEDLEY_DIAGNOSTIC_PUSH
            HEDLEY_DIAGNOSTIC_DISABLE_DEPRECATED
            obj.setWaitForConfigInput(wait);
            HEDLEY_DIAGNOSTIC_POP
        }, py::arg("wait"), DOC(dai, node, FeatureTrackerRvc4, setWaitForConfigInput))

        .def("getWaitForConfigInput", [](FeatureTrackerRvc4& obj){
            // Issue a deprecation warning
            PyErr_WarnEx(PyExc_DeprecationWarning, "Use 'inputConfig.setWaitForMessage()' instead", 1);
            HEDLEY_DIAGNOSTIC_PUSH
            HEDLEY_DIAGNOSTIC_DISABLE_DEPRECATED
            return obj.getWaitForConfigInput();
            HEDLEY_DIAGNOSTIC_POP
        }, DOC(dai, node, FeatureTrackerRvc4, getWaitForConfigInput))

        ;
    daiNodeModule.attr("FeatureTrackerRvc4").attr("Properties") = featureTrackerProperties;

}
