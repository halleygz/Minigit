#include "core/commit.hpp"
#include <nlohmann/json.hpp>
#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>

using json = nlohmann::json;
using namespace std;
namespace fs = filesystem;

namespace mgit
{
    string getCurrentTimeStamp();
    string generateHash(const string& content);
   

    Commit::Commit()
    {
        mgitDir = ".minigit";
        branchesDir = mgitDir + "/branches";
        commitsDir = mgitDir + "/commits";
        headFile = mgitDir + "/HEAD";
    };

    string CommitStruct::serialize() const
    {
        json j;
        j["hash"] = hash;
        j["parent"] = parent;
        j["message"] = message;
        j["timestamp"] = timestamp;
        j["files"] = files;
        return j.dump(4);
    }

    CommitStruct CommitStruct::deserialize(const string &content)
    {
        CommitStruct c;
        json j = json::parse(content);
        c.hash = j["hash"];
        c.parent = j["parent"];
        c.message = j["message"];
        c.timestamp = j["timestamp"];
        c.files = j["files"].get<map<string, string>>();
        return c;
    }

    CommitStruct Commit::getHeadCommit()
    {
        string headB = getHeadBranch();
        if (headB.empty())
        {
            return {};
        }

        string headId = readFile(headB);
        string path = commitsDir + "/" + headId + ".json";
        return fs::exists(path) ? loadCommitFromFile(path) : CommitStruct{};
    }

    string Commit::getHeadBranch()
    {
        if (!fs::exists(headFile))
        {
            return "";
        }

        string headBranch = readFile(headFile);
        if (headBranch.empty())
        {
            return "";
        }

        string path = branchesDir + "/" + headBranch;
        return path;
    }

    CommitStruct Commit::getCommitById(const string &hash)
    {
        string path = commitsDir + "/" + hash + ".json";
        return fs::exists(path) ? loadCommitFromFile(path) : CommitStruct{};
    }

    string Commit::readFile(const string &path) const
    {
        ifstream in(path);
        if (!in)
            return "";
        string content((istreambuf_iterator<char>(in)), istreambuf_iterator<char>());
        return content;
    }

    CommitStruct Commit::loadCommitFromFile(const string &path) const
    {
        ifstream in(path);
        if (!in)
            return CommitStruct{};

        string content((istreambuf_iterator<char>(in)), istreambuf_iterator<char>());
        return CommitStruct::deserialize(content);
    }

    int Commit::commit(const string& message)
    {
        CommitStruct currHEAD = getHeadCommit();
        string currHEADHash = currHEAD.hash;
        string currentBranch = getHeadBranch();

        ifstream staging(".minigit/staging_area.json");
        json staged_files;
        staging>>staged_files;

        map<string, string> files;
        for(auto &[fname, blob] : staged_files.items()){
            files[fname] = blob;
        }

        CommitStruct commit;
        commit.parent = currHEADHash;
        commit.message = message;
        commit.timestamp = getCurrentTimeStamp();
        commit.files = files;

        string content = commit.serialize();
        commit.hash = generateHash(content);

        content = commit.serialize();

        ofstream(currentBranch)<<commit.hash;
        ofstream(commitsDir + "/" + commit.hash + ".json")<<content;

        ofstream(mgitDir + "/staging_area.json")<< "{}";

        cout << "Committed as " << commit.hash << "\n";
        return 0;
    }

}