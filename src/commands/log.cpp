#include "core/commit.hpp"
#include "core/repository.hpp"
#include <iostream>

int logCommits()
{
    mgit::Repository repo;
    mgit::Commit commit;

    if (!repo.isInitialized())
    {
        std::cerr << "Repository not initialized.\n";
        return 1;
    }

    mgit::CommitStruct current = commit.getHeadCommit();
    while (!current.hash.empty())
    {
        std::cout << "commit: " << current.hash << "\n";
        std::cout << "Date: " << current.timestamp << "\n";
        std::cout << "Message: " << current.message << "\n";
        std::cout << "Files:\n";
        for (const auto &[filename, blob] : current.files)
        {
            std::cout << "  " << filename << "\n";
        }
        std::cout << "\n";

        if (current.parent.empty())
            break;

        current = commit.getCommitById(current.parent);
    }

    return 0;
}
