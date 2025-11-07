#include <fstream>
#include <iostream>

// method when mode is r

// method when mode is w

// method when mode is u

int main(const int argc, char* argv[]) {

    // The first line/number of the file will be the total number of tasks. Compare with ranges to see if out of bounds.
    // Look through the note app to see what to implement.

    // The To-Do List file is system-based and automatically generated.

    int totalTasks = 0;    // Here, you get the first number from the task file. It will be the total number of tasks.

    if (argc < 2) {
        std::cout << "No mode specified." << std::endl;
         return 1;
    }

    std::ifstream infile("tasks.txt");
    if (!infile) {
        std::cout << "File not found. Creating one: " << std::endl;

        std::ofstream outfile("tasks.txt");
        if (!outfile) {
            std::cout << "Error creating file." << std::endl;
            return 1;
        }

        outfile << totalTasks;

        std::cout << "File created, proceeding." << std::endl;
        outfile.close();
    } else {
        std::cout << "File found, proceeding." << std::endl;
        infile.close();
    }

    std::cout << argv[1] << std::endl;

    // if (strcmp(argv[2], "r") == 0) {
    //     // check for corrections or errors, then call the method for r
    // } else if (strcmp(argv[2], "w") == 0) {
    //     // check for corrections or errors, then call the method for w
    // } else if (strcmp(argv[2], "u") == 0) {
    //     // check for corrections or errors, then call the method for u
    // } else {
    //     std::cout << "Invalid mode specified." << std::endl;
    //     return 1;
    // }

    return 0;
}