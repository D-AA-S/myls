#include <iostream>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <string>

// Accepts directories and a hidden file boolean to scan through a directory
// If a directory isn't accessible/doesn't exist the function outputs that it cannot access it and returns
// If the directory is accessible then the passed in directory's contents are outputed onto the screen, 
// anything beginning with a . character will not be read unless the hiddenfile's value is true

int printDirectories(std::string argument, bool hiddenfile) {
    struct dirent* direntp;
    DIR *dirp;
    std::size_t index = argument.find_last_of("/");     // Find the last "/" to get the name of the current directory

    dirp = opendir(argument.c_str());
    if (dirp == NULL) {
        std::cout << "Cannot access " << argument << std::endl;
        closedir(dirp);
        return 0;
    }

    std::cout << argument.substr(index + 1) << std::endl;   // Print the name of the current working directory
    if (hiddenfile == true) {  // If the first argument is "-h", then we can print every file in the directory
        while (direntp = readdir(dirp))   // Loop through the files in the directory
            std::cout << direntp->d_name << std::endl;
        closedir(dirp);     // Close the directory
    }

    else {
        while (direntp = readdir(dirp)) {   // Loop through the files in the directory
            std::string filename = direntp->d_name;
            if (filename[0] != '.')         // If the file does not start with "."
                std::cout << filename << std::endl;
        }
        closedir(dirp);     // Close the directory
    }
}

// Handles the command line argument, giving special cases when nothing is inputted
// when only -h is inputted, and for when there are multiple inputted directories
int main(int argc, char** argv) {
    bool hidenfil = false;
    int i = 1;
    std::string hiddenCheck; 
    char* dirName;

    // No command line arguments provided. Need the name of the current working 
    // directory to list the files
    if (argc == 1) {  // The only command line argument is "myls"
        dirName = get_current_dir_name();       // Get the current working directory name to pass into the function
        printDirectories(dirName, false);
        return 0;
    }

    hiddenCheck = argv[1];

    // The only argument is -h so we need to list all the files in the current 
    // working directory including the hidden files
    if (argc == 2 && hiddenCheck.compare("-h") == 0) {
        dirName = get_current_dir_name();
        printDirectories(dirName, true);
        return 0;
    }

    // 1 or more arguments -> Use argc to loop through all of the listed
    // directories
    if (argc > 2 && hiddenCheck.compare("-h") == 0) { hidenfil = true; i = 2; }
    while (i < argc) {
        printDirectories(argv[i],hidenfil);
        i++;
    }
}