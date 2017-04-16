/* The DList class Header (DList.h) */
#include <string>   // using string
using namespace std;

// DList class declaration
class DList {
	private:// Accessible by members of this class only
		// private data members (variables)
		struct List {
			int data;
			struct List *prev;
			struct List *next;
		};
		struct List *head;

	public: // Accessible by ALL
		// Declare prototype of member functions
		// Constructor with default values
		DList();
		~DList();

		// Public member Function
		int Add(int data);
		int Delete(void *node);
		void *Search(int data);
};
