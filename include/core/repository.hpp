#pragma once

#include "core/commit.hpp"
#include <string>
#ifndef REPOSITORY_HPP
#define REPOSITORY_HPP

namespace mgit
{

    class Repository
    {
    public:
        Repository();

        bool isInitialized();
        Commit getHeadCommit();
        Commit getCommitById(const std::string& hash);
        std::string getHeadBranch();
        
    public:
        static void init();
    public:
        static void add(const std::string& file);
    public:
        static int commit(const std::string& message);
    public:
        static int logCommits();
    
    private:
        std::string mgitDir;
        std:: string commitsDir;
        std::string headFile;
        std::string branchesDir;

        std::string readFile(const std::string& path) const;
        Commit loadCommitFromFile(const std::string& path) const;
    
    };
}

#endif