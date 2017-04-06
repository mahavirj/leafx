/* The CircBuf class Header (CircBuf.h) */
#include <string>   // using string
using namespace std;

// CircBuf class declaration
class CircBuf {
	private:// Accessible by members of this class only
		// private data members (variables)
		int wr = 0;
		int rd = 0;
		char *buf;
		int len;

	#define WRAP_INC(x, y) (((x) + 1) % (y))
	#define BUF_EMPTY(x) ((x->rd) == (x->wr))
	#define BUF_FULL(x) (WRAP_INC(x->wr, x->len) == (x->rd))

	public: // Accessible by ALL
		// Declare prototype of member functions
		// Constructor with default values
		CircBuf(int len = 0);
		~CircBuf();

		// Public member Function
		int ReadBuffer(char *buf, int len);
		int WriteBuffer(const char *buf, int len);
};
