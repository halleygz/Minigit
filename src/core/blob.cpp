#include "core/blob.hpp"
#include "core/hashing.hpp"
#include "core/file_io.hpp"

#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

namespace mgit {

std::string Blob::create(const std::string& filepath) {
    std::string content = readFile(filepath);  // read content
    std::string hash = sha1(content);          // generate hash

    fs::path blob_path = ".minigit/blobs/" + hash;
    if (!fs::exists(blob_path)) {
        std::ofstream(blob_path) << content;
    }

    return hash;
}

}
