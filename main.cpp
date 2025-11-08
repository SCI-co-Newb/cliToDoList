#include <fstream>
#include <iostream>

// method when mode is r
void modeR(const int argc, char* argv[]) {
    std::cout << "This is mode r" << std::endl;

    // options going to be done task, or not done tasks; and -first, -se, or -last (decided to do only one)
    // if given multiple, only the last of the two will be considered
    // all other options will be given a warning, but it continues
    if (argc == 2) {
        std::ifstream infile("tasks.txt");

        std::string line;
        std::getline(infile, line);
        while (std::getline(infile, line)) {
            std::cout << line << std::endl;
        }
    } else {
        for (int i = 2; i < argc; i++) {
            if (strcmp(argv[i], "-first") == 0) {
                std::cout << "first" << std::endl;
            } else if (strcmp(argv[i], "-se") == 0) {
                std::cout << "se" << std::endl;
            } else if (strcmp(argv[i], "-last") == 0) {
                std::cout << "last" << std::endl;
            } else if (strcmp(argv[i], "-done") == 0) {
                std::cout << "done" << std::endl;
            } else if (strcmp(argv[i], "-left") == 0) {
                std::cout << "left" << std::endl;
            } else {
                std::cout << "Warning: unknown option " << argv[i] << std::endl;
            }
        }
    }
}

// method when mode is w
void modeW(const int argc, char* argv[]) {
    std::cout << "This is mode w" << std::endl;
}

// method when mode is u
void modeU(const int argc, char* argv[]) {
    std::cout << "This is mode u" << std::endl;
}

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

    if (strcmp(argv[1], "r") == 0) {
        // check for corrections or errors, then call the method for r
        modeR(argc, argv);
    } else if (strcmp(argv[1], "w") == 0) {
        // check for corrections or errors, then call the method for w
        if (argc > 2 ) modeW(argc, argv);
        else std::cout << "No task specified." << std::endl;
    } else if (strcmp(argv[1], "u") == 0) {
        // check for corrections or errors, then call the method for u
        if (argc > 2) modeU(argc, argv);
        else std::cout << "No task/ticket number specified." << std::endl;
    } else {
        std::cout << "Invalid mode specified." << std::endl;
        return 1;
    }

    return 0;
}