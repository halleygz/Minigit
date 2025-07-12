#include <string>
#include <iostream>
#include <fstream>
#include <filesystem>
#include "core/merge.hpp"
#include "core/commit.hpp"
#include "core/repository.hpp"

using namespace std;
namespace fs = filesystem;

namespace mgit
{
    Repository repo;
    Commit commit;
    
    Merge::Merge()
    {
        mgitDir = ".minigit";
        branchesDir = mgitDir + "/branches";
        commitsDir = mgitDir + "/commits";
    }

    string Merge::readFile(const string &path)
    {
        ifstream in(path);
        if (!in)
            return "";
        string content((istreambuf_iterator<char>(in)), istreambuf_iterator<char>());
        return content;
    }

    bool Merge::branchExists(const string &branchName)
    {
        string path = branchesDir + "/" + branchName;
        return fs::exists(path);
    }

    bool Merge::backTrackCheck(const string &fromCommitHash, const string &toCommitHash)
    {
        CommitStruct current = commit.getCommitById(fromCommitHash);

        while (!current.hash.empty())
        {
            if (current.hash == toCommitHash)
            {
                return true;
            }
        current = commit.getCommitById(current.parent);
        }
        return false;
    }

    bool Merge::merge(const string &branchName)
    {
        if (!branchExists(branchName))
        {
            cout << "branch named '" << branchName << "' doesn't exist, please enter a valid branch name. \n";
        }

        string headPath = mgitDir + "/" + "HEAD";
        string headBranch = readFile(headPath);

        string branchPath = branchesDir + "/" + headBranch;
        string commitOnHeadBranch = readFile(branchPath);
        string commitOnMergeBranch = readFile(branchesDir + "/" + branchName);

        if(backTrackCheck(commitOnHeadBranch, commitOnMergeBranch)){
            cout<<"merging from '"<<headBranch<<"' to '"<<branchName<<"' \n";

            ofstream(branchesDir + "/" + branchName)<<commitOnHeadBranch;

            cout<<"merged branches '"<<headBranch<<"' and '"<<branchName<<"/n";

            return true;
        } else {
            cout<<"failed to merge branches '"<<headBranch<<"' and '"<<branchName<<". No matching commits found";
            return false;
        }

        cout<<"Unknown Error occured while merging branches";
        return false;

    }

    bool Merge::pull(const string &branchName)
    {
        if (!branchExists(branchName))
        {
            cout << "branch named '" << branchName << "' doesn't exist, please enter a valid branch name. \n";
        }

        string headPath = mgitDir + "/" + "HEAD";
        string headBranch = readFile(headPath);

        string branchPath = branchesDir + "/" + headBranch;
        string commitOnHeadBranch = readFile(branchPath);
        string commitOnMergeBranch = readFile(branchesDir + "/" + branchName);

        if(backTrackCheck(commitOnMergeBranch, commitOnHeadBranch)){
            cout<<"merging from '"<<branchName<<"' to '"<<headBranch<<"' \n";

            ofstream(branchesDir + "/" + headBranch)<<commitOnHeadBranch;

            cout<<"merged branches '"<<branchName<<"' and '"<<headBranch<<"/n";

            return true;
        } else {
            cout<<"failed to merge branches '"<<branchName<<"' and '"<<headBranch<<". No matching commits found";
            return false;
        }

        cout<<"Unknown Error occured while merging branches";
        return false;
    }

    // bool Merge::mergeFromTo(const string &fromBranch, const string &toBranch)
    // {
    // }
}