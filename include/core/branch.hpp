#ifndef BRANCH_HPP
#define BRANCH_HPP

#include <string>
namespace mgit{
    class Branch {
        public:
            Branch();
            bool createBranch(const std::string& branchName);
            bool checkout(const std::string& branchName);
            bool branchExists(const std::string& branchName);
            bool createAndCheckout(const std::string& branchName);

        private: 
            std::string branchesDir;
            std::string mgitDir;
            std::string readFile(const std::string& path);
    };

}


#endif