#ifndef BLOB_HPP
#define BLOB_HPP

#include <string>

namespace mgit {

class Blob {
public:
    static std::string create(const std::string& filepath);
};

} 

#endif
