#include "Shell.h"

#include <iostream>
#include <iomanip>

#include <Windows.h>
#include <lmcons.h>

// Private Functions

void Shell::FirstHeader() {
    // Just a welcome header for the user.
    std::cout << std::setw(120) << std::setfill('*') << '\n' << std::setfill(' ');
    std::cout << '*' << std::right << std::setw(78) << "SHELL++ - OPEN SOURCE SHELL MADE IN C++" << std::setw(40) << '*' << '\n';
    std::cout << std::setw(120) << std::setfill('*') << '\n' << std::setfill(' ') << '\n';
}

void Shell::GetCurrentPath() {
    // NOTE: The usage of std::filesystem is also valid.
    CHAR pt[MAX_PATH];
    DWORD pt_l = GetCurrentDirectoryA(MAX_PATH, pt);

    if (pt_l == 0) {
        std::cerr << "Fatal error: Unable to get current directory.\n";
        exit(1);
    }

    this->currentPath = std::string(pt);
}

void Shell::GetUsername() {
    CHAR un[UNLEN + 1];
    DWORD un_l = UNLEN + 1;

    if (GetUserNameA(un, &un_l)) {
        this->username = std::string(un);
    }
    else {
        std::cerr << "Fatal error: Unable to get username.\n";
        exit(1);
    }
}

void Shell::GetHostname() {
    CHAR hn[MAX_PATH];
    DWORD hn_l = MAX_PATH;

    if (GetComputerNameA(hn, &hn_l)) {
        this->hostname = std::string(hn);
    } 
    else {
        std::cerr << "Fatal error: Unable to get computer hostname.\n";
        exit(1);
    }
}

void Shell::ReadUser() {
    std::cout << this->username << '@' << this->hostname << " (" << this->uStatus << ") " << this->currentPath << std::endl;
    std::cout << "> ";
    std::getline(std::cin, this->input);
}

Command Shell::CreateCommand() {
    Command c;

    return c;
}

// Constructors & Destructors

Shell::Shell() {
    if (this->enableHeader) { 
        this->FirstHeader(); 
        this->enableHeader = false;
    }
    this->GetCurrentPath();
    this->GetUsername();
    this->GetHostname();
}

Shell::~Shell() {

}

// Public Functions

void Shell::Run() {
    uint64_t status = 0;
    while (true) {
        // Start
        this->ReadUser();
        if (input == "exit") exit(0);

        Command c(this->input);
        // Empty input
        if (c.GetCommand() == "") continue;
        // Command not found
        if (!c.Parse()) {
            std::cout << c.GetCommand() << ": Commnand not found.\n";
            continue;
        }
        // Execute
        status = c.Execute();
    }
}
