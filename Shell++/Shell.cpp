#include "Shell.h"
#include "SPP_Codes.h"

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

void Shell::LoadAvailableCommands() {
    /*
     *  TODO: 
     *  El shell también deberia ser capaz de permitir al usuario cargar sus propios comandos con la estrucura clásica de un programa en C/C++ e inclusive otros lenguajes.
     *  Para esto se usará una pequeña DB en SQLite, ya que solo necesitamos una tabla simple. Además nos beneficiará si es que necesitamos escalar el proyecto para guardar otro
     *  tipo de registros. (Ej: Mostrar colores, cambiar el Header, ...)
     */
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

bool Shell::FindCommand(const Command &c) {
    // Here the shell must verify the commands that are avaliable

    return true;
}

void Shell::ExecuteCommand(Command &c) {
    uint64_t status = 0;

    switch ((status = c.Execute())) {
    case NO_COMMAND_STORED:
        std::cerr << "Error: Could not parse the tokens. Please try again.\n";
        break;
    case NO_PROCESS_CREATED:
        std::cerr << "Error: Could not create the process.\n";
        break;
    default:
        break;
    }
}

// Constructors & Destructors

Shell::Shell() {
    // Rework, this can be removed:
    if (this->enableHeader) { 
        this->FirstHeader(); 
        this->enableHeader = false;
    }
    this->GetCurrentPath();
    this->GetUsername();
    this->GetHostname();
    this->LoadAvailableCommands();
}

Shell::~Shell() {

}

// Public Functions

void Shell::Run() {
    // Loop
    while (true) {
        this->ReadUser();
        if (input == "") continue;
        if (input == "exit") exit(0);
        // Command creation
        Command c(this->input);
        // Command not found in register -> TODO: Create register system
        if (!this->FindCommand(c)) {
            std::cout << c.GetCommand() << ": Commnand not found.\n";
            continue;
        }
        // Execute
        if(c.GetCommand() != "") this->ExecuteCommand(c);
    }
}
