#pragma once

#include <rosbag/bag.h>

#include <boost/optional.hpp>

#include "nuscenes2bag/DatasetTypes.hpp"
#include "nuscenes2bag/Filesystem.hpp"

namespace nuscenes2bag {

struct NuScenes2Bag {
public:
  NuScenes2Bag();

  void convertDirectory(const fs::path &inDatasetPath,
                        const fs::path &metadataPath,
                        const std::string &version,
                        const fs::path &outputRosbagPath, int32_t threadNumber,
                        boost::optional<int32_t> sceneNumberOpt);

private:
  std::string inDatasetPathString;
};

}  // namespace nuscenes2bag