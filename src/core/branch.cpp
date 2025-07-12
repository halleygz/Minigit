#include <string>
#include <iostream>
#include <filesystem>
#include <fstream>
#include "core/branch.hpp"

using namespace std;
namespace fs = std::filesystem;


namespace mgit {
    Branch::Branch() {
        mgitDir = ".minigit";
        branchesDir = mgitDir + "/branches";
    } 

    string Branch::readFile(const string& path){
        ifstream in(path);
        if(!in) return "";
        string content((istreambuf_iterator<char>(in)), istreambuf_iterator<char>());
        return content;
    }

    bool Branch::branchExists(const string& branchName){
        string path = branchesDir + "/" + branchName;
        return fs::exists(path);
    }

    bool Branch::createBranch(const string& branchName) {
        if(branchExists(branchName)){
            cout<< "branch named '"<<branchName<<"' already exists. Please use a different Name";
            return false;
        }
        string headPath = mgitDir + "/" + "HEAD";
        string headBranch = readFile(headPath);

        string branchPath = branchesDir + "/" + headBranch;
        string commitOnHeadBranch = readFile(branchPath);

        ofstream(branchesDir + "/" + branchName)<<commitOnHeadBranch;
        cout<<"Written commit hash from '"<<headBranch<<"' to '"<<branchName<<"' \n";
        cout<<"Branch creation success!"<<"\n";
        return true;
    }

    bool Branch::checkout(const string& branchName) {
        if(!branchExists(branchName)) {
            cout<<"branch name '"<<branchName<<"' doesn't exist. \n";
            return false;
        }

        ofstream(mgitDir + "/HEAD")<<branchName;
        cout<<"You have checked out to '"<<branchName<<"' \n";
        return true;
    }

    bool Branch::createAndCheckout(const string& branchName){
        bool branchCreated = createBranch(branchName);

        if(branchCreated){
            return checkout(branchName);
        } else {
            return false;
        }
    }
}