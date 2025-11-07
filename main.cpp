#include <iostream>

// method when mode is r

// method when mode is w

// method when mode is u

int main(const int argc, char* argv[]) {

    // The first line/number of the file will be the total number of tasks. Compare with ranges to see if out of bounds.
    // Look through the note app to see what to implement.
    int totalTasks = 10;    // Here, you get the first number from the task file. It will be the total number of tasks.

    if (argc < 1) {
        std::cout << "No mode specified." << std::endl;
        return 1;
    }

    if (strcmp(argv[1], "r") == 0) {
        // check for corrections or errors, then call the method for r
    } else if (strcmp(argv[1], "w") == 0) {
        // check for corrections or errors, then call the method for w
    } else if (strcmp(argv[1], "u") == 0) {
        // check for corrections or errors, then call the method for u
    } else {
        std::cout << "Invalid mode specified." << std::endl;
        return 1;
    }

    return 0;
}