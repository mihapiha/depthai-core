#include "depthai/device/CalibrationHandler.hpp"
#include "rtabmap/core/StereoCameraModel.h"

namespace dai {
rtabmap::StereoCameraModel CalibrationHandler::getRTABMapCameraModel(CameraBoardSocket cameraId, int width, int height,const rtabmap::Transform& localTransform, float alphaScaling) {
    cv::Mat cameraMatrix, distCoeffs, newCameraMatrix;
    std::vector<std::vector<float> > matrix = getCameraIntrinsics(cameraId, width, height);
    cameraMatrix = (cv::Mat_<double>(3, 3) << matrix[0][0],
                    matrix[0][1],
                    matrix[0][2],
                    matrix[1][0],
                    matrix[1][1],
                    matrix[1][2],
                    matrix[2][0],
                    matrix[2][1],
                    matrix[2][2]);

    std::vector<float> coeffs = getDistortionCoefficients(cameraId);
	if(getDistortionModel(cameraId) == dai::CameraModel::Perspective)
		distCoeffs = (cv::Mat_<double>(1,8) << coeffs[0], coeffs[1], coeffs[2], coeffs[3], coeffs[4], coeffs[5], coeffs[6], coeffs[7]);

	if(alphaScaling>-1.0f)
		newCameraMatrix = cv::getOptimalNewCameraMatrix(cameraMatrix, distCoeffs, cv::Size(width, height), alphaScaling);
	else
		newCameraMatrix = cameraMatrix;
    double fx = newCameraMatrix.at<double>(0, 0);
    double fy = newCameraMatrix.at<double>(1, 1);
    double cx = newCameraMatrix.at<double>(0, 2);
    double cy = newCameraMatrix.at<double>(1, 2);
    double baseline = getBaselineDistance(dai::CameraBoardSocket::CAM_C, dai::CameraBoardSocket::CAM_B) / 100.0;
    
    rtabmap::Transform poseToCamera;
    if(cameraId == dai::CameraBoardSocket::CAM_A)
        poseToCamera = localTransform;
    else
        poseToCamera = localTransform * rtabmap::Transform(-getBaselineDistance(dai::CameraBoardSocket::CAM_A) / 100.0, 0, 0);


    return rtabmap::StereoCameraModel(eepromData.boardName, fx, fy, cx, cy, baseline, poseToCamera, cv::Size(width, height));
}
}  // namespace dai