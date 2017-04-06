/* The CircBuf class Implementation (CircBuf.cpp) */
#include "CircBuf.h" // user-defined header in the same directory
#include <string.h> // user-defined header in the same directory

/* A test driver for the CircBuf class (TestCircBuf.cpp) */
#include <iostream>
using namespace std;

// Constructor
// default values shall only be specified in the declaration,
// cannot be repeated in definition
CircBuf::CircBuf(int len) {
	this->buf = new char[len];
	this->len = len;
}

CircBuf::~CircBuf() {
	delete[] buf;
}

int CircBuf::ReadBuffer(char *buf, int len) {
	int count = 0;
	while (!BUF_EMPTY(this) && count < len) {
		buf[count] = this->buf[rd];
		this->rd = WRAP_INC(this->rd, this->len);
		count++;
	}
	return count;
}

int CircBuf::WriteBuffer(const char *buf, int len) {
	int count = 0;
	while (!BUF_FULL(this) && count < len) {
		this->buf[wr] = buf[count];
		this->wr = WRAP_INC(this->wr, this->len);
		count++;
	}
	return count;
}

int main() {
	const char *write = "Hello";
	char read[8];
	// Construct an instance of CircBuf c1
	CircBuf c1(1024);
	while (c1.WriteBuffer(write, 6));
	while (c1.ReadBuffer(read, 6));
	cout << "Buffer=" << read << endl;
	return 0;
}
