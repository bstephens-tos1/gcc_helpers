/**
 * Usage:
 * PUSH_GCC_WARNINGS();
 * ...
 * POP_GCC_WARNINGS(); // #pragma GCC diagnostic pop
 */
#define GCC_DIAG_DO_PRAGMA(x) _Pragma (#x)
#define GCC_DIAG_DO_PRAGMA_WARN(x) GCC_DIAG_DO_PRAGMA(GCC diagnostic warning #x)
#define GCC_DIAG_DO_PRAGMA_IGNORE(x) GCC_DIAG_DO_PRAGMA(GCC diagnostic ignored #x)
#define PUSH_GCC_WARNINGS() \
	_Pragma ("GCC diagnostic push") \
	GCC_DIAG_DO_PRAGMA_WARN(-Wall) \
	GCC_DIAG_DO_PRAGMA_WARN(-Wextra) \
	GCC_DIAG_DO_PRAGMA_WARN(-Wshadow) \
	GCC_DIAG_DO_PRAGMA_WARN(-Wconversion) \
	GCC_DIAG_DO_PRAGMA_IGNORE(-Wdeclaration-after-statement)

/**
 * Disable warnings for sections of code. Useful to turn off gcc warnings for
 * sections of code when a unit of code has enabled many non-default warnings.
 * E.g., included kernel headers (lots of warnings!).
 *
 * Typical code sequence generated by define (below):
 *
 * 		#pragma GCC diagnostic push //save diagnostic state
 * 			...
 * 			#pragma GCC diagnostic ignored "-Wsign-conversion"
 * 			...
 * 		#pragma GCC diagnostic pop // reenable warnings
 *
 * Usage:
 *
 * 		PUSH_IGNORE_GCC_WARNINGS();
 * 		...
 * 		POP_GCC_WARNINGS(); // #pragma GCC diagnostic pop
 */
#define PUSH_IGNORE_GCC_WARNINGS() \
	_Pragma ("GCC diagnostic push") \
	GCC_DIAG_DO_PRAGMA_IGNORE(-Wsign-conversion) \
    GCC_DIAG_DO_PRAGMA_IGNORE(-Wunused-parameter) \
    GCC_DIAG_DO_PRAGMA_IGNORE(-Wconversion) \
    GCC_DIAG_DO_PRAGMA_IGNORE(-Wshadow)

#define POP_GCC_WARNINGS() \
	_Pragma ("GCC diagnostic pop")

/**
 * TODO:
 *      The generated *_mod.c is generated and compiled using Makefile warnings
 *      and therefore generates MANY warnings due to kernel headers.
 */
