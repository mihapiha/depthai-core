#include <rerun.hpp>

#include "depthai/basalt/BasaltVIO.hpp"
#include "depthai/depthai.hpp"
#include "depthai/pipeline/node/host/HostNode.hpp"
#include "depthai/pipeline/datatype/TransformData.hpp"


rerun::Collection<rerun::TensorDimension> tensorShape(const cv::Mat& img) {
    return {img.rows, img.cols, img.channels()};
};
class RerunStreamer : public dai::NodeCRTP<dai::node::ThreadedHostNode, RerunStreamer> {
   public:
    constexpr static const char* NAME = "RerunStreamer";

   public:
    void build() {}

    /**
     * Input for any ImgFrame messages
     * Default queue is blocking with size 8
     */
    Input inputTrans{*this, {.name = "inTrans", .types = {{dai::DatatypeEnum::TransformData, true}}}};
    Input inputImg{*this, {.name = "inImg", .types = {{dai::DatatypeEnum::ImgFrame, true}}}};
    void run() override {
        const auto rec = rerun::RecordingStream("rerun");
        rec.spawn().exit_on_failure();
        rec.log_timeless("world", rerun::ViewCoordinates::FLU);
        rec.log("world/ground", rerun::Boxes3D::from_half_sizes({{3.f, 3.f, 0.00001f}}));

        while(isRunning()) {
            std::shared_ptr<dai::TransformData> transData = inputTrans.get<dai::TransformData>();
            auto imgFrame = inputImg.get<dai::ImgFrame>();
            if(transData != nullptr) {
                double x, y, z, qx, qy, qz, qw;
                transData->getTranslation(x, y, z);
                transData->getQuaternion(qx, qy, qz, qw);
                auto position = rerun::Vec3D(x, y, z);
                rec.log("world/camera", rerun::Transform3D(position, rerun::datatypes::Quaternion::from_xyzw(qx, qy, qz, qw)));
                positions.push_back(position);
                rerun::LineStrip3D lineStrip(positions);
                rec.log("world/trajectory", rerun::LineStrips3D(lineStrip));
                rec.log("world/camera/image", rerun::Pinhole::from_focal_length_and_resolution({398.554f, 398.554f}, {640.0f, 400.0f}).with_camera_xyz(rerun::components::ViewCoordinates::FLU));
                rec.log("world/camera/image/rgb",
                        rerun::Image(tensorShape(imgFrame->getCvFrame()), reinterpret_cast<const uint8_t*>(imgFrame->getCvFrame().data)));
            }
        }
    }
    std::vector<rerun::Vec3D> positions;
};

int main() {
    using namespace std;

    // Create pipeline
    dai::Pipeline pipeline;
    int fps = 60;
    int width = 640;
    int height = 400;
    // Define sources and outputs
    auto left = pipeline.create<dai::node::MonoCamera>()->build();
    auto right = pipeline.create<dai::node::MonoCamera>()->build();
    auto imu = pipeline.create<dai::node::IMU>()->build();
    auto odom = pipeline.create<dai::node::BasaltVIO>()->build();

    auto rerun = pipeline.create<RerunStreamer>();
    imu->enableIMUSensor({dai::IMUSensor::ACCELEROMETER_RAW, dai::IMUSensor::GYROSCOPE_RAW}, 200);
    imu->setBatchReportThreshold(1);
    imu->setMaxBatchReports(10);

    left->setCamera("left");
    left->setResolution(dai::MonoCameraProperties::SensorResolution::THE_400_P);
    left->setFps(fps);
    right->setCamera("right");
    right->setResolution(dai::MonoCameraProperties::SensorResolution::THE_400_P);
    right->setFps(fps);

    // Linking

    left->out.link(odom->inLeft);
    right->out.link(odom->inRight);
    imu->out.link(odom->inputImu);
    odom->transform.link(rerun->inputTrans);
    odom->passthrough.link(rerun->inputImg);

    pipeline.start();
    pipeline.wait();
}