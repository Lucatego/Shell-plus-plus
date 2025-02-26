#include "Command.h"

#include <iostream>

#include <Windows.h>

#define NO_COMMAND 0xFFF1
#define NO_PROCESS 0xFFF2

// Private Functions

// Constructors & Destructors

Command::Command() {
	
}

Command::Command(const std::string &input) {
	this->userInput = input;
	if (input.size() == 0) {
		this->tokens = std::vector<std::string>(1, "");
	}
	else {
		std::string token;
		bool isPhrase = false; // For "..." or '...' cases
		//cmd txt1 txt2 tx3
		for (char c : input) {
			if (c == ' ' and not isPhrase) {
				this->tokens.push_back(token);
				token.clear();
				continue;
			}
			token.push_back(c);
		}
		this->tokens.push_back(token);
	}
}

Command::~Command() {

}

// Public Functions

bool Command::Parse() {
	// Here the shell must verify the commands that are avaliable

	return true;
}

// TODO: Must modify to implement the complete version with own made commands.
uint64_t Command::Execute() {
	// Cast from std::string to char*
	if (this->tokens.empty() or this->userInput.empty()) return NO_COMMAND;

	// Necessary for CreateProcess
	STARTUPINFOA si = { sizeof(si) };
	PROCESS_INFORMATION pi;

	// There is no "fork()" in Windows, you must execute another program from an executable path.
	if (!CreateProcessA(NULL, &userInput[0], NULL, NULL, false, 0, NULL, NULL, &si, &pi)) {
		std::cerr << "Error: Could not create the process\n";
		return NO_PROCESS;
	}
	
	// Wait for "child" to end.
	WaitForSingleObject(pi.hProcess, INFINITE);

	// Close 
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
}

std::string Command::GetCommand() {
	return tokens[0];
}