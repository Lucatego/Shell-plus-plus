#pragma once

#include <string>
#include <vector>

class Command {
private:
	std::string userInput; // Parsed input
	std::vector<std::string> tokens;

	bool isValid = false;

private:
	void CleanInput();

public:
	Command();
	Command(const std::string &input);
	~Command();

public:
	uint64_t Execute();

	std::string GetCommand();
	
};

