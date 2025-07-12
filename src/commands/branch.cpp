#include "core/branch.hpp"
#include "core/repository.hpp"
#include <iostream>

using namespace std;

bool createBranch(const string& branchName) {
    mgit::Repository repo;
    if (!repo.isInitialized()) {
        cerr << "Repository not initialized.\n";
        return false;
    }
    mgit::Branch branch;
    return branch.createBranch(branchName);
}

bool checkout(const string& branchName) {
    mgit::Repository repo;
    if (!repo.isInitialized()) {
        cerr << "Repository not initialized.\n";
        return false;
    }
    mgit::Branch branch;
    return branch.checkout(branchName);
}

bool createAndCheckout(const string& branchName) {
    mgit::Repository repo;
    if (!repo.isInitialized()) {
        cerr << "Repository not initialized.\n";
        return false;
    }
    mgit::Branch branch;
    return branch.createAndCheckout(branchName);
}