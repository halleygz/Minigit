#include "core/repository.hpp"
#include <iostream>

int addCommand(const std::string& file) {
    mgit::Repository::add(file);
    return 0;
}
