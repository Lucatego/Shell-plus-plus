#pragma once

#include "Command.h"

#include <string>

class Shell {
private:
	std::string currentPath;
	std::string username;
	std::string hostname;
	bool enableHeader = true;

	std::string uStatus = "USER";
	bool isAdmin = false;

	std::string input;
	
private:
	void FirstHeader();
	void GetUsername();
	void GetHostname();
	void GetCurrentPath();

	void ReadUser();
	Command CreateCommand();

public:
	Shell();
	~Shell();

public:
	void Run();

};

