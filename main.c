#include "binaryfilework.h"

bool help(void);

int main(int argc, char** argv)
{
	typedef bool(*func_p)();
	int i, j;
	bool flag1 = false, flag2 = false;
	func_p function_pointer[NUMBER_OF_COMANDS] = { help, input_files, show_inputfiles, determine_prodacts_number};
	char optStrings[NUMBER_OF_COMANDS][WORD_LENGTH] = {
		{ "help" },
		{ "input" },
		{ "show" },
		{ "determine" } };
	for (i = 1; i < argc; i++)
	{
		for (j = 0; j < NUMBER_OF_COMANDS; j++)
		{
			if (strcmp(argv[i], optStrings[j]) == 0)
			{
				flag1 = function_pointer[j]();
				flag2 = true;
				break;
			}
		}
		if (flag2 == true) break;
	}
	if (flag1 == false)
	{
		printf("\nIn the course of an error occurred\n");
		return 1;
	}
	return 0;
}
bool help(void)
{
	puts("List of comands:");
	puts("                 input - to input information about goods into files");
	puts("                 show - to look throw the file information");
	puts("                 determine - to calculate number of repeating word");
	puts("                 help - to see list of comands");
	return true;
}

