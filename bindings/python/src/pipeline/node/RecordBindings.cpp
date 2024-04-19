#include "Common.hpp"

#include "depthai/pipeline/node/host/Record.hpp"

void bind_record(pybind11::module& m, void* pCallstack){

    using namespace dai;
    using namespace node;

    auto record = ADD_NODE_DERIVED(Record, HostNode);

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
    // Node
    record.def_readonly("in", &Record::in, DOC(dai, node, Record, in))
        .def("setRecordFile", &Record::setRecordFile, py::arg("recordFile"), DOC(dai, node, Record, setRecordFile))
        .def("setCompressionLevel", &Record::setCompressionLevel, py::arg("compressionLevel"), DOC(dai, node, Record, setCompressionLevel));

}