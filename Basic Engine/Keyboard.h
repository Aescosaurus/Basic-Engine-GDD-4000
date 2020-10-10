#pragma once

#include <thread>

class Keyboard
{
public:
	Keyboard();
	~Keyboard();

	char CheckKey() const;
private:
	bool stop = false;
	std::thread inputThread;
	char key = '\0';
};