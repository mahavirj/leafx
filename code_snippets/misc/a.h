
typedef struct test_struct_t {
	int num;
#ifdef PADDING
	char padding[16];
#endif
} test_struct_t;
