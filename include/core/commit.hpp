#ifndef COMMIT_HPP
#define COMMIT_HPP

#include <string>
#include <map>
#include <vector>

namespace mgit
{
    struct CommitStruct
    {
        std::string hash;
        std::string parent;
        std::string message;
        std::string timestamp;
        std::map<std::string, std::string> files;

        std::string serialize() const;
        static CommitStruct deserialize(const std::string &content);
    };
    class Commit
    {
    private:
        std::string mgitDir;
        std::string commitsDir;
        std::string headFile;
        std::string branchesDir;

        std::string readFile(const std::string &path) const;
        CommitStruct loadCommitFromFile(const std::string &path) const;

    public:
        Commit();
        CommitStruct getHeadCommit();
        CommitStruct getCommitById(const std::string &hash);
        std::string getHeadBranch();
        int commit(const std::string &message);
        int logCommits();
    };

}

#endif