#include "core/file_io.hpp"
#include <fstream>
#include <sstream>
#include "utils/file_io.hpp"
#include <chrono>
#include <ctime>
#include <iomanip>

namespace mgit {

std::string getCurrentTimeStamp() {
    auto now = std::chrono::system_clock::now();
    std::time_t t = std::chrono::system_clock::to_time_t(now);

    std::stringstream ss;
    ss << std::put_time(std::localtime(&t), "%Y-%m-%d %H:%M:%S");
    return ss.str();
}

}


std::string readFile(const std::string& filepath) {
    std::ifstream in(filepath);
    std::stringstream ss;
    ss << in.rdbuf();
    return ss.str();
}
