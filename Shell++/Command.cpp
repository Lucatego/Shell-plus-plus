#include "Command.h"

// Private Functions

// Constructors & Destructors

Command::Command() {
	
}

Command::Command(const std::string input) {
	if (input.size() == 0) {
		this->tokens = std::vector<std::string>(1, "");
	}
	else {
		std::string token;
		bool isPhrase = false;
		//mv this ./data
		for (char c : input) {
			if (c == ' ') {
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

bool Command::Validate() {
	return false;
}

uint64_t Command::Execute() {
	return 1;
}

std::string Command::GetCommand() {
	return tokens[0];
}