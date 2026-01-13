#include <fstream>
#include <iostream>

// method when mode is r
void modeR(const int argc, char* argv[]) {
    // options going to be done, open, or iprg (inprogress); and -first, -se, or -last (decided to do only one)
    // if given multiple, only the last of the two will be considered
    // all other options will be given a warning, but it still continues
    std::ifstream infile("tasks.txt");
    std::ifstream countfile("count.txt");

    if (argc == 2) {
        std::string line;
        while (std::getline(infile, line)) {
            std::cout << line << std::endl;
        }
    } else {
        std::string rangeMode = "default";
        std::string taskType = "default";

        int firstNumber = 1, secondNumber = 0;

        std::string line;
        std::getline(countfile, line);

        int maxNumber = std::stoi(line);
        secondNumber = maxNumber;

        for (int i = 2; i < argc; i++) {
            if (strcmp(argv[i], "-first") == 0) {
                if (i + 1 < argc
                    && std::all_of(argv[i + 1], argv[i + 1] + strlen(argv[i + 1]), ::isdigit)
                    && std::stoi(argv[i + 1]) <= maxNumber) {
                    rangeMode = "first";
                    firstNumber = 0;
                    secondNumber = std::stoi(argv[i + 1]);
                    i = i + 1;
                } else {
                    // Here, the first is essentially ignored
                    std::cout << "Warning: no number specified for -first (MAYBE also out of bounds)" << std::endl;
                }
            } else if (strcmp(argv[i], "-se") == 0) {
                if (i + 2 < argc
                    && std::all_of(argv[i + 1], argv[i + 1] + strlen(argv[i + 1]), ::isdigit)
                    && std::all_of(argv[i + 2], argv[i + 2] + strlen(argv[i + 2]), ::isdigit)
                    && std::stoi(argv[i + 1]) < std::stoi(argv[i + 2])
                    && std::stoi(argv[i + 2]) <= maxNumber
                    && std::stoi(argv[i + 1]) <= 0) {
                    rangeMode = "se";
                    firstNumber = std::stoi(argv[i + 1]);
                    secondNumber = std::stoi(argv[i + 2]);
                    i = i + 2;
                } else if (i + 1 < argc
                    && std::all_of(argv[i + 1], argv[i + 1] + strlen(argv[i + 1]), ::isdigit)) {
                    std::cout << "Warning: no second number specified for -se (MAYBE also out of bounds)" << std::endl;
                    i = i + 1;
                } else {
                    // Here, the se is essentially ignored
                    std::cout << "Warning: no numbers specified for -se (MAYBE also out of bounds)" << std::endl;
                }
            } else if (strcmp(argv[i], "-last") == 0) {
                if (i + 1 < argc
                    && std::all_of(argv[i + 1], argv[i + 1] + strlen(argv[i + 1]), ::isdigit)
                    && std::stoi(argv[i + 1]) >= 0) {
                    rangeMode = "last";
                    firstNumber = std::stoi(argv[i + 1]);
                    secondNumber = maxNumber;
                    i = i + 1;
                } else {
                    // Here, the last is essentially ignored
                    std::cout << "Warning: no number specified for -last (MAYBE also out of bounds)" << std::endl;
                }
            } else if (strcmp(argv[i], "-done") == 0) {
                taskType = "DONE";
            } else if (strcmp(argv[i], "-open") == 0) {
                taskType = "OPEN";
            } else if (strcmp(argv[i], "-iprg") == 0) {
                taskType = "IPRG";
            } else {
                std::cout << "Warning: unknown option " << argv[i] << std::endl;
            }
        }

        std::cout << "Range mode: " << rangeMode << std::endl;
        std::cout << "Task type: " << taskType << std::endl;

        for (int i = 1; i < firstNumber; i++) {
            std::getline(infile, line);
        }

        char status[5]; // 5 chars + null terminator
        for (int i = firstNumber; i <= secondNumber; i++) {
            infile.read(status, 4);
            status[4] = '\0';

            std::getline(infile, line); // probably inefficient
            if (status == taskType) {
                std::cout << i << ":" << line << std::endl;
            }
        }
    }
    infile.close();
    countfile.close();
}

// method when mode is w
void modeW(const int argc, char* argv[]) {
    // the 3rd arg is the task description, and it's assumed the task description is surrounded by quotation marks
    // for extra flags, it's going to be put in a loop and only looks for one flag, open, done, or iprg
    // if nothing or invalid results only, then defaults to open flag
    std::cout << "This is mode w" << std::endl;

    std::ofstream outfile("tasks.txt", std::ios::app);
    std::fstream countfile("count.txt", std::ios::in | std::ios::out);

    std::string taskType = "OPEN";  // its the default

    if (argc > 3) {     // add flags here, like changing the open to iprg or done (make into while loop like read)
        for (int i = 3; i < argc; i++) {
            if (strcmp(argv[i], "-done") == 0) {
                taskType = "DONE";
            } else if (strcmp(argv[i], "-open") == 0) {
                taskType = "OPEN";
            } else if (strcmp(argv[i], "-iprg") == 0) {
                taskType = "IPRG";
            } else {
                std::cout << "Warning: unknown option " << argv[i] << std::endl;
            }
        }
    }

    outfile << taskType << " " << argv[2] << std::endl;
    std::cout << "Task added." << std::endl;
    std::string line;
    std::getline(countfile, line);
    int maxNumber = std::stoi(line);
    countfile.seekp(0);  // Rewind to start of file
    countfile << maxNumber + 1 << std::endl;

    outfile.close();
    countfile.close();
}

// method when mode is u
void modeU(const int argc, char* argv[]) {
    std::cout << "This is mode u" << std::endl;
}

// method to sync count with number of tasks (auxiliary/admin usage)

int main(const int argc, char* argv[]) {

    // The first line/number of the file will be the total number of tasks. Compare with ranges to see if out of bounds.
    // Look through the note app to see what to implement.

    // The To-Do List file is system-based and automatically generated.

    if (argc < 2) {
        std::cout << "No mode specified." << std::endl;
         return 1;
    }

    std::ifstream infile("tasks.txt");
    if (!infile) {
        std::cout << "Task file not found. Creating one: " << std::endl;

        std::ofstream outfile("tasks.txt");
        if (!outfile) {
            std::cout << "Error creating task file." << std::endl;
            return 1;
        }

        std::cout << "Task file created, proceeding." << std::endl;
        outfile.close();
    } else {
        std::cout << "Task file found, proceeding." << std::endl;
        infile.close();
    }

    std::ifstream cinfile("count.txt");
    if (!cinfile) {
        std::cout << "Count file not found. Creating one: " << std::endl;

        std::ofstream coutfile("count.txt");
        if (!coutfile) {
            std::cout << "Error creating count file." << std::endl;
            return 1;
        }

        coutfile << 0 << std::endl;

        std::cout << "Count file created, proceeding." << std::endl;
        coutfile.close();
    } else {
        std::cout << "Count file found, proceeding." << std::endl;
        cinfile.close();
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