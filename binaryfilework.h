#ifdef __linux__
#define FLUSH __fpurge(stdin)
#endif

#ifdef _WIN32
#define FLUSH fflush(stdin)
#endif

#ifdef _WIN64
#define FLUSH fflush(stdin)
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <inttypes.h>
#define WORD_LENGTH 25
#define NUMBER_LENGTH 10
#define NUMBER_OF_COMANDS 4

bool show_files(void);
bool input_files(void);
bool show_inputfiles(void); 
bool determine_prodacts_number(void);
void binary_file_input(FILE *file1, FILE *file2);
void binary_file_read(FILE *file1, FILE *file2);
void binary_file_work(FILE *file1, FILE *file2);

struct good
{
	char *number;
	char *name;
};
