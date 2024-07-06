#include "depthai/pipeline/datatype/FeatureTrackerConfigRvc4.hpp"

#include <iostream>

namespace dai {

FeatureTrackerConfigRvc4& FeatureTrackerConfigRvc4::setCornerDetector(FeatureTrackerConfigRvc4::CornerDetector::Type cornerDetector) {
    this->cornerDetector.type = cornerDetector;
    return *this;
}

FeatureTrackerConfigRvc4& FeatureTrackerConfigRvc4::setCornerDetector(FeatureTrackerConfigRvc4::CornerDetector config) {
    cornerDetector = config;
    return *this;
}

FeatureTrackerConfigRvc4& FeatureTrackerConfigRvc4::setMotionEstimator(bool enable) {
    motionEstimator.enable = enable;
    return *this;
}

FeatureTrackerConfigRvc4& FeatureTrackerConfigRvc4::setMotionEstimator(FeatureTrackerConfigRvc4::MotionEstimator config) {
    motionEstimator = config;
    return *this;
}

FeatureTrackerConfigRvc4& FeatureTrackerConfigRvc4::setHwMotionEstimation() {
    motionEstimator.type = FeatureTrackerConfigRvc4::MotionEstimator::Type::HW_MOTION_ESTIMATION;

    setMotionEstimator(true);
    return *this;
}

FeatureTrackerConfigRvc4& FeatureTrackerConfigRvc4::setHarrisCornerDetectorThreshold(std::int32_t cornerDetectorThreshold) {
    if(cornerDetectorThreshold >= 0 and cornerDetectorThreshold <= 25000) {
        cornerDetector.thresholds.harrisScore = cornerDetectorThreshold;
    }
    return *this;
}

FeatureTrackerConfigRvc4& FeatureTrackerConfigRvc4::setHarrisCornerDetectorRobustness(std::int32_t cornerDetectorRobustness) {
    if(cornerDetectorRobustness >= 0 and cornerDetectorRobustness <= 127) {
        cornerDetector.thresholds.robustness = cornerDetectorRobustness;
    }
    return *this;
}

FeatureTrackerConfigRvc4& FeatureTrackerConfigRvc4::setConfidence(std::int32_t confidenceThreshold) {
    if(confidenceThreshold >= 0 and confidenceThreshold <= 255) {
       featureMaintainer.confidenceThreshold = confidenceThreshold;
    }
    return *this;
}

FeatureTrackerConfigRvc4& FeatureTrackerConfigRvc4::setFilterCoeffs(std::array<std::array<std::uint8_t, 3>, 3> filterCoeffs) {
    cornerDetector.filterCoeffs = {{{filterCoeffs[0][0], filterCoeffs[0][1], filterCoeffs[0][2]},
                                    {filterCoeffs[1][0], filterCoeffs[1][1], filterCoeffs[1][2]},
                                    {filterCoeffs[2][0], filterCoeffs[2][1], filterCoeffs[2][2]}}};

    return *this;
}

FeatureTrackerConfigRvc4& FeatureTrackerConfigRvc4::setFeatureMaintainer(bool enable) {
    featureMaintainer.enable = enable;
    return *this;
}

FeatureTrackerConfigRvc4& FeatureTrackerConfigRvc4::setFeatureMaintainer(FeatureTrackerConfigRvc4::FeatureMaintainer config) {
    featureMaintainer = config;
    return *this;
}

FeatureTrackerConfigRvc4& FeatureTrackerConfigRvc4::setNumMaxFeatures(std::int32_t numMaxFeatures) {
    cornerDetector.numMaxFeatures = numMaxFeatures;
    return *this;
}

}  // namespace dai
