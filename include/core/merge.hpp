#ifndef MERGE_HPP
#define MERGE_HPP

#include <string>
namespace mgit {
    class Merge {
        public:
            Merge();
            bool merge(const std::string& branchName);
            bool pull(const std::string& branchName);
            bool branchExists(const std::string& branchName);
            bool mergeFromTo(const std::string& fromBranch, const std::string& toBranch);
            bool backTrackCheck(const std::string& fromCommitHash, const std::string& toCommitHash);
        
        private: 
            std::string branchesDir;
            std::string mgitDir;
            std::string commitsDir;
            std::string readFile(const std::string& path);
    };
}


#endif