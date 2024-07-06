#include "depthai/pipeline/node/FeatureTrackerRvc4.hpp"

#include "spdlog/fmt/fmt.h"

namespace dai {
namespace node {

FeatureTrackerRvc4::FeatureTrackerRvc4(std::unique_ptr<Properties> props) : DeviceNodeCRTP<DeviceNode, FeatureTrackerRvc4, FeatureTrackerPropertiesRvc4>(std::move(props)) {}

FeatureTrackerRvc4::Properties& FeatureTrackerRvc4::getProperties() {
    properties.initialConfig = initialConfig;
    return properties;
}

// Node properties configuration
void FeatureTrackerRvc4::setWaitForConfigInput(bool wait) {
    inputConfig.setWaitForMessage(wait);
}

bool FeatureTrackerRvc4::getWaitForConfigInput() const {
    return inputConfig.getWaitForMessage();
}

}  // namespace node
}  // namespace dai
