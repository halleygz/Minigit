#ifndef HASHING_HPP
#define HASHING_HPP

#include <string>
#include <openssl/sha.h>
#include <iomanip>

namespace mgit {
    std::string generateHash(const std::string& content);
}

#endif
