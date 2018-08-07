#define CHECK(CALL) if (CALL) { perror (#CALL); exit (EXIT_FAILURE); }

#define OUTPUT_MSG_NUM(msg, var) do { \
	printf(msg); \
	printf(" "); \
	cout << var << endl; \
} while(0)

#define OUTPUT_NUM(var) do { \
	_OUTPUT_NUM(var, :); \
} while(0)

#define _OUTPUT_NUM(var, separator) do { \
	OUTPUT_MSG_NUM(#var#separator, var); \
} while(0)
