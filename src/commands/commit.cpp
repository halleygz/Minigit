#include "core/repository.hpp"
#include "core/commit.hpp"
#include <iostream>

using namespace std;


int commitCommand(const string& message){
    mgit::Repository repo;
    if (!repo.isInitialized()) {
        cerr << "Repository not initialized.\n";
        return 1;
    }
    mgit::Commit commit;
    return commit.commit(message);
}