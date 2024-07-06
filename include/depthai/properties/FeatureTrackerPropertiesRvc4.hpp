#pragma once

#include <vector>

#include "depthai/common/optional.hpp"
#include "depthai/pipeline/datatype/FeatureTrackerConfigRvc4.hpp"
#include "depthai/properties/Properties.hpp"

namespace dai {

/**
 * Specify properties for FeatureTracker
 */
struct FeatureTrackerPropertiesRvc4 : PropertiesSerializable<Properties, FeatureTrackerPropertiesRvc4> {
    /**
     * Initial feature tracker config
     */
    FeatureTrackerConfigRvc4 initialConfig;
};

DEPTHAI_SERIALIZE_EXT(FeatureTrackerPropertiesRvc4, initialConfig);

}  // namespace dai
