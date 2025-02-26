#pragma once

#include <string>
#include <vector>

class Command {
private:
	std::vector<std::string> tokens;

	bool isValid = false;
private:


public:
	Command();
	Command(const std::string input);
	~Command();

public:
	bool Validate();
	uint64_t Execute();
	std::string GetCommand();
};

