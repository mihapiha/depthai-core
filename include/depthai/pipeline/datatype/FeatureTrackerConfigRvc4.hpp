#pragma once

#include <iostream>
#include <unordered_map>
#include <vector>

#include "depthai/pipeline/datatype/Buffer.hpp"

namespace dai {

/**
 * FeatureTrackerConfigRvc4 message. Carries config for feature tracking algorithm
 */
class FeatureTrackerConfigRvc4 : public Buffer {
   public:
    /**
     * Construct FeatureTrackerConfigRvc4 message.
     */
    FeatureTrackerConfigRvc4() = default;
    virtual ~FeatureTrackerConfigRvc4() = default;

    static constexpr const std::int32_t AUTO = 0;

    /**
     * Corner detector configuration structure.
     */
    struct CornerDetector {
        enum class Type : std::int32_t {
            /**
             * HARRIS corner detector.
             */
            HARRIS
        };
        /**
         * Corner detector algorithm type.
         */
        Type type = Type::HARRIS;

        /**
         * Hard limit for the maximum number of features that can be detected.
         */
        std::int32_t numMaxFeatures = 1024;

        /**
         * Gradient filter shift
         * It is one of the HCD HW exposed configs
         */
        std::int32_t gradientFilterShift = 1;

        /*
         * Descriptor LPF
         */
        bool descriptorLpf = true;

        std::array<std::uint8_t, 3> gradientFilterCoeffsX_3 = {1, 2, 1};
        std::array<std::uint8_t, 3> gradientFilterCoeffsY_3 = {1, 2, 1};
        std::array<std::uint8_t, 3> lowPassFilterCoeffs_3 = {1, 4, 6};

        std::array<std::array<std::uint8_t, 3>, 3> filterCoeffs = {{{1, 2, 1}, {1, 2, 1}, {1, 4, 6}}};

        /**
         * Threshold settings structure for corner detector.
         */
        struct Thresholds {
            float harrisScore = 25000;
            float robustness = 10;

            DEPTHAI_SERIALIZE(Thresholds, harrisScore, robustness);
        };

        /**
         * Threshold settings.
         * These are advanced settings, suitable for debugging/special cases.
         */
        Thresholds thresholds;

        DEPTHAI_SERIALIZE(CornerDetector, type, numMaxFeatures, gradientFilterShift, thresholds, filterCoeffs, descriptorLpf);
    };

    /**
     * Used for feature reidentification between current and previous features.
     */
    struct MotionEstimator {
        /**
         * Enable motion estimation or not.
         */
        bool enable = false;

        enum class Type : std::int32_t {
            /**
             * Using a dense motion estimation hardware block (Block matcher).
             */
            HW_MOTION_ESTIMATION
        };
        /**
         * Motion estimator algorithm type.
         */
        Type type = Type::HW_MOTION_ESTIMATION;

        /**
         * Optical flow configuration structure.
         */
        struct OpticalFlow {
            /**
             * Number of pyramid levels, only for optical flow.
             * AUTO means it's decided based on input resolution: 3 if image width <= 640, else 4.
             * Valid values are either 3/4 for VGA, 4 for 720p and above.
             */
            std::int32_t pyramidLevels = AUTO;

            /**
             * Image patch width used to track features.
             * Must be an odd number, maximum 9.
             * N means the algorithm will be able to track motion at most (N-1)/2 pixels in a direction per pyramid level.
             * Increasing this number increases runtime
             */
            std::int32_t searchWindowWidth = 5;
            /**
             * Image patch height used to track features.
             * Must be an odd number, maximum 9.
             * N means the algorithm will be able to track motion at most (N-1)/2 pixels in a direction per pyramid level.
             * Increasing this number increases runtime
             */
            std::int32_t searchWindowHeight = 5;

            /**
             * Feature tracking termination criteria.
             * Optical flow will refine the feature position on each pyramid level until
             * the displacement between two refinements is smaller than this value.
             * Decreasing this number increases runtime.
             */
            float epsilon = 0.01f;

            /**
             * Feature tracking termination criteria. Optical flow will refine the feature position maximum this many times
             * on each pyramid level. If the Epsilon criteria described in the previous chapter is not met after this number
             * of iterations, the algorithm will continue with the current calculated value.
             * Increasing this number increases runtime.
             */
            std::int32_t maxIterations = 9;

            DEPTHAI_SERIALIZE(OpticalFlow, pyramidLevels, searchWindowWidth, searchWindowHeight, epsilon, maxIterations);
        };

        /**
         * Optical flow configuration.
         * Takes effect only if MotionEstimator algorithm type set to LUCAS_KANADE_OPTICAL_FLOW.
         */
        OpticalFlow opticalFlow;

        DEPTHAI_SERIALIZE(MotionEstimator, enable, type, opticalFlow);
    };

    /**
     * FeatureMaintainer configuration structure.
     */
    struct FeatureMaintainer {
        /**
         * Enable feature maintaining or not.
         */
        bool enable = true;

        /**
         * Used to filter out detected feature points that are too close.
         * Requires sorting enabled in detector.
         * Unit of measurement is squared euclidean distance in pixels.
         */
        float minimumDistanceBetweenFeatures = 50;

        /**
         * Optical flow measures the tracking error for every feature.
         * If the point can’t be tracked or it’s out of the image it will set this error to a maximum value.
         * This threshold defines the level where the tracking accuracy is considered too bad to keep the point.
         */
        float lostFeatureErrorThreshold = 50000;

        /**
         * Once a feature was detected and we started tracking it, we need to update its Harris score on each image.
         * This is needed because a feature point can disappear, or it can become too weak to be tracked. This
         * threshold defines the point where such a feature must be dropped.
         * As the goal of the algorithm is to provide longer tracks, we try to add strong points and track them until
         * they are absolutely untrackable. This is why, this value is usually smaller than the detection threshold.
         */
        float trackedFeatureThreshold = 200000;

        int confidenceThreshold = 100;

        DEPTHAI_SERIALIZE(FeatureMaintainer, enable, minimumDistanceBetweenFeatures, lostFeatureErrorThreshold, trackedFeatureThreshold, confidenceThreshold);
    };

    /**
     * Set corner detector algorithm type.
     * @param cornerDetector Corner detector type, HARRIS
     */
    FeatureTrackerConfigRvc4& setCornerDetector(CornerDetector::Type cornerDetector);

    /**
     * Set corner detector full configuration.
     * @param config Corner detector configuration
     */
    FeatureTrackerConfigRvc4& setCornerDetector(CornerDetector config);

    /**
     * Set hardware accelerated motion estimation using block matching.
     * Faster than optical flow (software implementation) but might not be as accurate.
     */
    FeatureTrackerConfigRvc4& setHwMotionEstimation();

    /**
     * Set initial threshold for HARRIS Corner Detector
     */
    FeatureTrackerConfigRvc4& setHarrisCornerDetectorThreshold(std::int32_t cornerDetectorThreshold);

    /**
     * Set initial robustness for Harris Corner Detector
     */
    FeatureTrackerConfigRvc4& setHarrisCornerDetectorRobustness(std::int32_t cornerDetectorRobustness);


    /**
     * Set confidence for FeatureMaintainer
     */
    FeatureTrackerConfigRvc4& setConfidence(std::int32_t confidenceThreshold);

    /**
     * Set filter coeficients for Feature Tracker
     */
    FeatureTrackerConfigRvc4& setFilterCoeffs(std::array<std::array<std::uint8_t, 3>, 3> filterCoeffs);

    /**
     * Get filter coeficients for Feature Tracker
     */
    std::array<std::array<std::uint8_t, 3>, 3> getFilterCoeffs();  // TODO: add this

    /**
     * Set number of target features to detect.
     * @param numTargetFeatures Number of features
     */
    FeatureTrackerConfigRvc4& setNumMaxFeatures(std::int32_t numMaxFeatures);

    /**
     * Enable or disable motion estimator.
     * @param enable
     */
    FeatureTrackerConfigRvc4& setMotionEstimator(bool enable);

    /**
     * Set motion estimator full configuration.
     * @param config Motion estimator configuration
     */
    FeatureTrackerConfigRvc4& setMotionEstimator(MotionEstimator config);

    /**
     * Enable or disable feature maintainer.
     * @param enable
     */
    FeatureTrackerConfigRvc4& setFeatureMaintainer(bool enable);

    /**
     * Set feature maintainer full configuration.
     * @param config feature maintainer configuration
     */
    FeatureTrackerConfigRvc4& setFeatureMaintainer(FeatureMaintainer config);

   public:
    /**
     * Corner detector configuration.
     * Used for feature detection.
     */
    CornerDetector cornerDetector;

    /**
     * Motion estimator configuration.
     * Used for feature reidentification between current and previous features.
     */
    MotionEstimator motionEstimator;

    /**
     * FeatureMaintainer configuration.
     * Used for feature maintaining.
     */
    FeatureMaintainer featureMaintainer;

   public:
    void serialize(std::vector<std::uint8_t>& metadata, DatatypeEnum& datatype) const override {
        metadata = utility::serialize(*this);
        datatype = DatatypeEnum::FeatureTrackerConfigRvc4;
    };

    DEPTHAI_SERIALIZE(FeatureTrackerConfigRvc4, Buffer::sequenceNum, Buffer::ts, Buffer::tsDevice, cornerDetector, motionEstimator, featureMaintainer);
};

}  // namespace dai
