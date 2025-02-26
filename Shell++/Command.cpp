#include "Command.h"
#include "SPP_Codes.h"

#include <iostream>

#include <Windows.h>

// Private Functions

void Command::CleanInput() {
	std::string cleanInput;
	// 1. Remove whitespaces at start
	// 2. Remove double whitespaces
	char lastLetter = 0, c;
	std::string clean("");
	bool endsWithSpace = true;
	//____echo_____"Hola como estan"__\n
	for (int i = 0; i < this->userInput.size(); i++) {
		c = userInput[i];

		if (lastLetter == ' ' and c == ' ') {
			endsWithSpace = true;
			continue;
		}
		else if (i == 0 and c == ' ') {
			lastLetter = ' ';
			endsWithSpace = true;
			continue;
		}

		clean.push_back(c);
		lastLetter = c;
		endsWithSpace = false;
	}
	if (clean.size() > 0 and endsWithSpace) clean.pop_back();
	this->userInput = clean;
}

// Constructors & Destructors

Command::Command() {
	
}

Command::Command(const std::string &input) {
	// Copy the value
	this->userInput = input;
	// Work with the local variable
	this->CleanInput();
	if (this->userInput.size() == 0) {
		this->tokens = std::vector<std::string>(1, "");
	}
	else {
		std::string token;
		bool isPhrase = false; // For "..." or '...' cases (TODO)
		//cmd txt1 txt2 tx3
		for (char c : this->userInput) {
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

// TODO: Must modify to implement the complete version with own made commands. -> Add executables in a library (SQLite)
uint64_t Command::Execute() {
	// Cast from std::string to char*
	if (this->tokens.empty() or this->userInput.empty()) return NO_COMMAND_STORED;

	// Necessary for CreateProcess
	STARTUPINFOA si = { sizeof(si) };
	PROCESS_INFORMATION pi;

	// There is no "fork()" in Windows, you must execute another program from an executable path.
	if (!CreateProcessA(NULL, &userInput[0], NULL, NULL, false, 0, NULL, NULL, &si, &pi)) return NO_PROCESS_CREATED;
	
	// Wait for "child" to end.
	WaitForSingleObject(pi.hProcess, INFINITE);

	// Close 
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
}

std::string Command::GetCommand() {
	return tokens[0];
}