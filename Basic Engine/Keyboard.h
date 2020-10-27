#pragma once

#include <thread>
#include <queue>

class Keyboard
{
public:
	Keyboard();
	~Keyboard();

	char ReadBuffer() const;

	char CheckKey() const;
private:
	bool stop = false;
	std::thread inputThread;
	char key = '\0';
	mutable std::queue<char> keyBuffer;
	int c = 0;
};