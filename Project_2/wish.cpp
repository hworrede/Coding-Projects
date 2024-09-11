//CSE 150
//Hagos Worrede
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <cstring>

using namespace std;

const int changeof_size = 1024;
//this will check for my erros
char Check_err[] = "An error has occurred\n";

// Now we will check for a function that splits a string 
vector<string> divide_string(const string& check_eachinput) {
    vector<string> check_each;
    istringstream input_val(check_eachinput);
    string piece;
    //we need to use whitespaces

    while (input_val >> piece) {
        check_each.push_back(piece);
    }
    return check_each;
}
//we need to use whitespaces

// Now we need to check this function for processing a command with possible output
void checking_process(const vector<string>& check_eacharg) {
    // Check each
    bool make_newpath = false;
    string path_out;
    vector<string> ex_params;
    // Now we need to check this function for processing a command with possible output
    for (size_t i = 0; i < check_eacharg.size(); ++i) {
        if (check_eacharg[i] == ">") {
            if (make_newpath) {
                // Check each
                write(STDERR_FILENO, Check_err, strlen(Check_err));
                exit(1);
            }
            // } else if (argc != 1) { write(STDERR_FILENO, Check_err, strlen(Check_err));
// } else if (argc != 1) { write(STDERR_FILENO, Check_err, strlen(Check_err));
// } else if (argc != 1) { write(STDERR_FILENO, Check_err, strlen(Check_err));
            if (i == check_eacharg.size() - 1) {
                // Check each
                write(STDERR_FILENO, Check_err, strlen(Check_err));
                exit(1);
            }
            path_out = check_eacharg[i + 1];
            make_newpath = true;
            // Check each
            i++;
        } else {
            ex_params.push_back(check_eacharg[i]);
        }
    }

    // Create a new arg for the next 
    const char** checking_arg = new const char*[ex_params.size() + 1];
    for (size_t i = 0; i < ex_params.size(); ++i) {
        checking_arg[i] = ex_params[i].c_str();
    }
    checking_arg[ex_params.size()] = nullptr;

    // check each command 
    if (make_newpath) {
         // check each command 
        int finding_next = open(path_out.c_str(), O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
        if (finding_next == -1) {
             // check each command 
            write(STDERR_FILENO, Check_err, strlen(Check_err));
            exit(1);
        } // check each command 
        if (dup2(finding_next, STDOUT_FILENO) == -1) {
             // check each command 
            write(STDERR_FILENO, Check_err, strlen(Check_err));
            exit(1);
        }
        close(finding_next);
    } // check each command 

     // check each command 
    if (execvp(checking_arg[0], const_cast<char* const*>(checking_arg)) == -1) {
        
        write(STDERR_FILENO, Check_err, strlen(Check_err));
        exit(1);
    }
}

 

// finding next available 
bool checking_model(vector<string>& check_eacharg, vector<string>& finddirect) {
    if (check_eacharg[0] == "exit") {
        if (check_eacharg.size() != 1) {
            write(STDERR_FILENO, Check_err, strlen(Check_err));
            return true;
        }
        exit(0); // finding next available 
    } else if (check_eacharg[0] == "cd") {
        if (check_eacharg.size() != 2) {
            write(STDERR_FILENO, Check_err, strlen(Check_err));
            return true;
        }


        // } else if (argc != 1) { write(STDERR_FILENO, Check_err, strlen(Check_err));
// } else if (argc != 1) { write(STDERR_FILENO, Check_err, strlen(Check_err));
// } else if (argc != 1) { write(STDERR_FILENO, Check_err, strlen(Check_err));
        // finding next available 
        if (chdir(check_eacharg[1].c_str()) == -1) {
            write(STDERR_FILENO, Check_err, strlen(Check_err));
        }
        return true;
    } else if (check_eacharg[0] == "path") {
        // finding next available 
        if (check_eacharg.size() == 1) {
            
            finddirect.clear();
        } else {
            //update
            for (size_t i = 1; i < check_eacharg.size(); ++i) {
                finddirect.push_back(check_eacharg[i]);
            }
        }
        return true;
    }
    return false;
}

// checking each of the files.
string file_ex(const string& command, const vector<string>& finddirect) {
    for (size_t i = 0; i < finddirect.size(); ++i) {
        string path = finddirect[i] + "/" + command;
        if (access(path.c_str(), X_OK) == 0) {
            return path;
        }
    }
    return ""; // Not found
}

int main(int argc, char* checking_arg[]) {
    bool check_mode = false;
    FILE* input_fil = nullptr;

    // find the correct batch 
    if (argc == 2) {
        check_mode = true;
        input_fil = fopen(checking_arg[1], "r");
        if (!input_fil) {
            write(STDERR_FILENO, Check_err, strlen(Check_err));
            exit(1);
        } // find the correct batch 

// } else if (argc != 1) { write(STDERR_FILENO, Check_err, strlen(Check_err));
// } else if (argc != 1) { write(STDERR_FILENO, Check_err, strlen(Check_err));
// } else if (argc != 1) { write(STDERR_FILENO, Check_err, strlen(Check_err));
    } else if (argc != 1) {
        write(STDERR_FILENO, Check_err, strlen(Check_err));
        exit(1);
    }

     // find the correct batch 
    vector<string> finddirect;
    finddirect.push_back("/bin");

    while (true) {
        if (!check_mode) {
            cout << "wish> ";
        }
 // find the correct batch 
        string check_eachinput;
        if (check_mode) {
            char buffer[changeof_size];
            if (fgets(buffer, changeof_size, input_fil) == nullptr) {




                if (feof(input_fil)) {
                    break; // End 
                } else {
                    write(STDERR_FILENO, Check_err, strlen(Check_err));
                    exit(1);
                }
            }

// } else if (argc != 1) { write(STDERR_FILENO, Check_err, strlen(Check_err));
// } else if (argc != 1) { write(STDERR_FILENO, Check_err, strlen(Check_err));
// } else if (argc != 1) { write(STDERR_FILENO, Check_err, strlen(Check_err));
// } else if (argc != 1) { write(STDERR_FILENO, Check_err, strlen(Check_err));
// } else if (argc != 1) { write(STDERR_FILENO, Check_err, strlen(Check_err));
// } else if (argc != 1) { write(STDERR_FILENO, Check_err, strlen(Check_err));

            check_eachinput = buffer;//check for the buffer
        } else {
            if (!getline(cin, check_eachinput)) {
                cout << endl; 
                exit(0);
            }
        }

        // checking for the newline
        if (!check_eachinput.empty() && check_eachinput.back() == '\n') {
            check_eachinput.pop_back();
        }

        // Split it is a good check_eachinput
        vector<string> finding_nextcomm;
        stringstream check_command(check_eachinput);
        string command;
        while (getline(check_command, command, '&')) {
            finding_nextcomm.push_back(command);
        }
// } else if (argc != 1) { write(STDERR_FILENO, Check_err, strlen(Check_err));
// } else if (argc != 1) { write(STDERR_FILENO, Check_err, strlen(Check_err));
// } else if (argc != 1) { write(STDERR_FILENO, Check_err, strlen(Check_err));
        // Execute the next command 
        vector<pid_t> find_nextfind;
        for (const string& singlecomm : finding_nextcomm) {
            vector<string> check_eacharg = divide_string(singlecomm);
            if (check_eacharg.empty()) {
                continue; // Execute the next command 
            }

            // Execute the next command 
            if (checking_model(check_eacharg, finddirect)) {
                continue;
            }

            // Execute the next command 
            string each_exe = file_ex(check_eacharg[0], finddirect);
            if (each_exe.empty()) {// Execute the next command 
                write(STDERR_FILENO, Check_err, strlen(Check_err));
                continue;
            }

            // finding for overall second
            check_eacharg[0] = each_exe;

            // this is the child process
            pid_t for_everykid = fork();
            // this is the child process
            if (for_everykid < 0) {
                write(STDERR_FILENO, Check_err, strlen(Check_err));
                // this is the child process
                exit(1);
            } else if (for_everykid == 0) {
                // this is the child process
                checking_process(check_eacharg);
            } else {
                // parent now
                find_nextfind.push_back(for_everykid);
            }
        }
        // } else if (argc != 1) { write(STDERR_FILENO, Check_err, strlen(Check_err));
// } else if (argc != 1) { write(STDERR_FILENO, Check_err, strlen(Check_err));
// } else if (argc != 1) { write(STDERR_FILENO, Check_err, strlen(Check_err));

        // Wait for all child processes to finish
        for (pid_t for_everykid : find_nextfind) {
            int checkforstatus;
            if (waitpid(for_everykid, &checkforstatus, 0) == -1) {
                write(STDERR_FILENO, Check_err, strlen(Check_err));
                exit(1);
            }
        }
    }
// Wait for all child processes to finish
    if (check_mode) {
        fclose(input_fil);
    }
// Wait for all child processes to finish
    return 0;
}
