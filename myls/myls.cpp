#include <iostream>
#include <sys/types.h>
#include <dirent.h>
#include <string>

int printDirectories(std::string argument, bool hiddenfile) 
{
    struct dirent* direntp;
    DIR *dirp;
    
    dirp = opendir(argument.c_str());
    if (dirp == NULL) 
    {
        std::cout << "Cannot access " << argument << std::endl;
        closedir(dirp);
        return 0;
    }
    argument = (argument == ".") ? "Current Directory" : argument;
    if (hiddenfile == true) {  // If the first argument is "-h", then we can print every file in the directory
        std::cout << argument << std::endl;
        while (direntp = readdir(dirp))   // Loop through the files in the directory
            std::cout << direntp->d_name << std::endl;
        closedir(dirp);     // Close the directory
    }
    else {
        std::cout << argument << std::endl;
        while (direntp = readdir(dirp)) {   // Loop through the files in the directory
            std::string filename = direntp->d_name;
            if (filename[0] != '.')         // If the file does not start with "."
                std::cout << filename << std::endl;
        }
        closedir(dirp);     // Close the directory
    }
}


int main(int argc, char** argv)
{
    bool hidenfil = false;
    int i = 1;
    std::string hiddenCheck;
    // No command line arguments provided. Need the name of the current working 
    // directory to list the files
    if (argc == 1) {  // The only command line argument is "myls"
        printDirectories(".", false);
        return 0;
    }

    hiddenCheck = argv[1];

    // The only argument is -h so we need to list all the files in the current 
    // working directory including the hidden files
    if (argc == 2 && hiddenCheck.compare("-h") == 0) {
        printDirectories(".", true);
        return 0;
    }

    // 1 or more arguments -> Use argc to loop through all of the listed
    // directories
    if (argc > 2 && hiddenCheck.compare("-h") == 0) { hidenfil = true; i = 2; }
    while (i < argc) 
    {
        printDirectories(argv[i],hidenfil);
        i++;
    }
}


