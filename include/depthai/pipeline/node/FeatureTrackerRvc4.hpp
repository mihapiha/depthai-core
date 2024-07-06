#pragma once

#include <depthai/pipeline/DeviceNode.hpp>

// standard
#include <fstream>

// shared
#include <depthai/properties/FeatureTrackerPropertiesRvc4.hpp>

#include "depthai/pipeline/datatype/FeatureTrackerConfigRvc4.hpp"

namespace dai {
namespace node {

/**
 * @brief FeatureTrackerRvc4 node.
 * Performs feature tracking and reidentification using motion estimation between 2 consecutive frames.
 */
class FeatureTrackerRvc4 : public DeviceNodeCRTP<DeviceNode, FeatureTrackerRvc4, FeatureTrackerPropertiesRvc4> {
   public:
    constexpr static const char* NAME = "FeatureTrackerRvc4";
    using DeviceNodeCRTP::DeviceNodeCRTP;

   protected:
    Properties& getProperties();

   public:
    FeatureTrackerRvc4() = default;
    FeatureTrackerRvc4(std::unique_ptr<Properties> props);

    std::shared_ptr<FeatureTrackerRvc4> build() {
        return std::static_pointer_cast<FeatureTrackerRvc4>(shared_from_this());
    }
    /**
     * Initial config to use for feature tracking.
     */
    FeatureTrackerConfigRvc4 initialConfig;

    /**
     * Input FeatureTrackerConfigRvc4 message with ability to modify parameters in runtime.
     * Default queue is non-blocking with size 4.
     */
    Input inputConfig{*this, {.name = "inputConfig", .blocking = false, .queueSize = 4, .types = {{DatatypeEnum::FeatureTrackerConfigRvc4, false}}}};

    /**
     * Input message with frame data on which feature tracking is performed.
     * Default queue is non-blocking with size 4.
     */
    Input inputImage{*this, {.name = "inputImage", .blocking = false, .queueSize = 4, .types = {{DatatypeEnum::ImgFrame, false}}, .waitForMessage = true}};

    /**
     * Outputs TrackedFeatures message that carries tracked features results.
     */
    Output outputFeatures{*this, {.name = "outputFeatures", .types = {{DatatypeEnum::TrackedFeatures, false}}}};

    /**
     * Passthrough message on which the calculation was performed.
     * Suitable for when input queue is set to non-blocking behavior.
     */
    Output passthroughInputImage{*this, {.name = "passthroughInputImage", .types = {{DatatypeEnum::ImgFrame, false}}}};
    // Functions to set properties
    /**
     * Specify whether or not wait until configuration message arrives to inputConfig Input.
     * @param wait True to wait for configuration message, false otherwise.
     */
    [[deprecated("Use 'inputConfig.setWaitForMessage()' instead")]] void setWaitForConfigInput(bool wait);

    /**
     * @see setWaitForConfigInput
     * @returns True if wait for inputConfig message, false otherwise
     */
    [[deprecated("Use 'inputConfig.setWaitForMessage()' instead")]] bool getWaitForConfigInput() const;
};

}  // namespace node
}  // namespace dai
