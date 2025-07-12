#include "core/merge.hpp"
#include "core/repository.hpp"
#include <iostream>

using namespace std;

bool merge(const string& branchName) {
    mgit::Repository repo;

    if(!repo.isInitialized()){
        cerr<<"Repository not intialized. \n";
        return false;
    }

    mgit::Merge merge;
    return merge.merge(branchName);
}

bool pull(const string& branchName) {
    mgit::Repository repo;
    
    if(!repo.isInitialized()){
        cerr<<"Repository not intialized. \n";
        return false;
    }
    
    mgit::Merge merge;
    return merge.pull(branchName);
}