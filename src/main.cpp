#include <iostream>
#include <string>


int initCommand();
int addCommand(const std::string& filename);
int commitCommand(const std::string& message);
int logCommits();
bool createBranch(const std::string& branchName);
bool checkout(const std::string& branchName);
bool createAndCheckout(const std::string& branchName);
bool merge(const std::string& branchName);
bool pull(const std::string& branchName);

int main(int argc, char *argv[])
{
    
    if (argc < 2)
    {
        std::cout << "Usage: minigit <command>\n";
        return 1;
    }
    
    std::string command = argv[1];
    if (command == "init")
    {
        return initCommand();
    } else if (command == "add"){
        if(argc < 3) {
            std::cerr<< "Usage: minigit add <file>\n";
            return 1;
        }

        return addCommand(argv[2]);
    } else if(command == "commit"){
        std::string message;
        if(argc >= 4 && std::string(argv[2]) == "-m"){
            message = argv[3];
        } else {
            std:: cerr << "Usage: minigit commit -m \"message\"\n";
            return 1;
        }
        return commitCommand(message);
    } else if (command == "log") {
        return logCommits();
    } else if(command == "branch") {
         if(argc < 3) {
            std::cerr<< "Usage: minigit branch <branchName>\n";
            return 1;
        }
        return createBranch(argv[2]);       
    } else if (command == "checkout") {
        if (argc >= 4 && std::string(argv[2]) == "-b") {
            return createAndCheckout(argv[3]);
        } else if (argc >= 3) {
            return checkout(argv[2]);
        } else {
            std::cerr << "Usage: minigit checkout [-b] <branchName>\n";
            return 1;
        }
    } else if(command == "merge") {
        if(argc< 3) {
            std::cerr<<"Usage: minigit merge <branchName> \n";
            return 1;
        }
        return merge(argv[2]);
    } else if (command == "pull"){
        if(argc < 3) {
            std::cerr<<"Usage: minigit pull <branchName> \n";
            return 1;
        }
        return pull(argv[2]);
    }


    std::cout << "Unknown command: " << command << "\n";
    return 1;
}