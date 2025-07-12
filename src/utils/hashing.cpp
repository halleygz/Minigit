#include <openssl/sha.h>
#include <iomanip>
#include <sstream>
#include "core/hashing.hpp"

namespace mgit {

std::string generateHash(const std::string& content) {
    unsigned char hash[SHA_DIGEST_LENGTH];
    SHA1(reinterpret_cast<const unsigned char*>(content.c_str()), content.size(), hash);

    std::stringstream ss;
    for (int i = 0; i < SHA_DIGEST_LENGTH; ++i)
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    return ss.str();
}

}

std::string sha1(const std::string& input) {
    unsigned char hash[SHA_DIGEST_LENGTH];
    SHA1(reinterpret_cast<const unsigned char*>(input.c_str()), input.size(), hash);

    std::stringstream ss;
    for (int i = 0; i < SHA_DIGEST_LENGTH; ++i)
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    return ss.str();
}