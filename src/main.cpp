#include <boost/program_options.hpp>
#include <iostream>

#include "nuscenes2bag/MetaDataReader.hpp"
#include "nuscenes2bag/NuScenes2Bag.hpp"

using namespace boost::program_options;
using namespace nuscenes2bag;

int main(const int argc, const char* argv[]) {
  try {
    std::string data_root;
    std::string metadata_folder;
    std::string version = "v1.0-mini";
    std::string outputBagName;
    int32_t threadNumber = -1;
    int32_t sceneNumber = -1;

    options_description desc{"Options"};
    desc.add_options()("help,h", "show help");

    options_description inputDesc{"input"};
    // clang-format off
    inputDesc.add_options()(
        "scene_number,n", value<int32_t>(&sceneNumber), "only convert a given scene")(
        "data_folder,s", value<std::string>(&data_root)->required(),
        "Path to root of dataset containing 'maps', 'samples', 'sweeps'")(
        "version", value<std::string>(&version),
        "Version string (default = 'v1.0-mini')")(
        "out,o", value<std::string>(&outputBagName), "output bag name")(
        "jobs,j", value<int32_t>(&threadNumber),
        "number of jobs (thread number)")(
        "metadata_folder,m", value<std::string>(&metadata_folder)->required(),
        "Path to root of metadata"
    );
    // clang-format on
    variables_map vm;

    desc.add(inputDesc);

    store(parse_command_line(argc, argv, desc), vm);
    notify(vm);

    if (vm.count("help")) {
      std::cout << desc << '\n';
    } else {
      NuScenes2Bag converter{};

      fs::path sampleDirPath(data_root);

      boost::optional<int32_t> sceneNumberOpt;
      if (sceneNumber > 0) {
        sceneNumberOpt = sceneNumber;
      }
      converter.convertDirectory(sampleDirPath, metadata_folder, version,
                                 outputBagName, threadNumber, sceneNumberOpt);
    }
  } catch (const error& ex) {
    std::cerr << ex.what() << '\n';
  }

  return 0;
}