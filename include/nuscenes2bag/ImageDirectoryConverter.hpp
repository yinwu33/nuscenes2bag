#pragma once

#include <cv_bridge/cv_bridge.h>

#include <boost/optional.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>

#include "nuscenes2bag/Filesystem.hpp"
#include "sensor_msgs/Image.h"

namespace nuscenes2bag {

boost::optional<sensor_msgs::Image> readImageFile(
    const fs::path& filePath) noexcept;

}
