#include "json.hpp"

Json::Json(){};
Json::~Json(){};

bool Json::parse_file(std::string file_path) {
    file.open(file_path, std::ios::in);
    if (!file.good()) {
        std::cerr << "Error opening file " << file_path << std::endl;
        return false;
    }


    return true;
}
