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

	// SQLite Database
	
private:
	void FirstHeader();

	void GetUsername();
	void GetHostname();
	void GetCurrentPath();
	void LoadAvailableCommands();

	void ReadUser();
	Command CreateCommand();

	bool FindCommand(const Command &c);
	void ExecuteCommand(Command &c);

public:
	Shell();
	~Shell();

public:
	void Run();

};

