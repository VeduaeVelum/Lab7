#include "binaryfilework.h"

bool check_letter(void);
bool check_string(char *string);
bool check_number(char *number);
struct good *input_information(struct good *str);

bool input_files(void)
{
	FILE *file1_1, *file1_2, *file2_1, *file2_2;
	if (!(file1_1 = fopen("main_input_names_file.bin", "w+b"))
		|| (!(file1_2 = fopen("main_input_numbers_file.bin", "w+b")))
		|| (!(file2_1 = fopen("support_input_names_file.bin", "w+b")))
		|| (!(file2_2 = fopen("support_input_numbers_file.bin", "w+b"))))
	{
		printf("\nFiles aren't opened\n");
		fclose(file1_1); fclose(file1_2);
		fclose(file2_1); fclose(file2_2);
		return false;
	}
	printf("\t\tInput information into the main file\n");
	binary_file_input(file1_1, file1_2);
	fclose(file1_1); fclose(file1_2); 
	printf("\n\t\tInput information into the support file\n");
	binary_file_input(file2_1, file2_2);
	fclose(file2_1); fclose(file2_2);
	return true;
}
void binary_file_input(FILE *file1, FILE *file2)
{
	bool flag = false;
	const char massive[] = { "$$$" };
	struct good *str;
	do
	{
		if ((!(str = (struct good*)calloc(1, sizeof(struct good))) 
			|| !(str->name = (char*)calloc((WORD_LENGTH + 1), sizeof(char)))
			|| !(str->number = (char*)calloc((NUMBER_LENGTH + 1), sizeof(char)))))
		{
			printf("\nMemory isn't allocated\n");
			fclose(file1); fclose(file2);
			exit(-3);
		}
		str = input_information(str);
		fwrite(str->name, sizeof(char), sizeof(str->name) / sizeof(char), file1);
		fwrite(str->number, sizeof(char), sizeof(str->number) / sizeof(char), file2);
		printf("\tDo you want to input information about another good?(Y/N): ");
		flag = check_letter();
		free(str->name);
		free(str->number);
		free(str);
	} while (flag == true);
	fwrite(massive, sizeof(char), sizeof(massive) / sizeof(char), file1);
	fwrite(massive, sizeof(char), sizeof(massive) / sizeof(char), file2);
}
bool check_letter(void)
{
	char c;
	do
	{
		scanf("%c", &c);
		FLUSH;
		if (c == 'Y' || c == 'y') return true;
		else if (c == 'N' || c == 'n') return false;
		else printf("\tIncorrect input, try again: ");
	} while (1);
}
struct good *input_information(struct good *str)
{
	bool flag;
	printf("\tInput name of good: ");
	do
	{
		scanf("%25s", str->name);
		FLUSH;
		flag = check_string(str->name);			
	} while (flag == false);
	printf("\tInput number of this good: ");
	do
	{
		scanf("%10s", str->number);
		FLUSH;
		flag = check_number(str->number);
	} while (flag == false);
	return str;
}
bool show_inputfiles(void)
{
	FILE *file1_1, *file1_2, *file2_1, *file2_2;
	if (!(file1_1 = fopen("main_input_names_file.bin", "r+b")))
	{
		printf("\nFiles aren't opened\n");
		return false;
	}
	if (!(file1_2 = fopen("main_input_numbers_file.bin", "r+b")))
	{
		printf("\nFiles aren't opened\n");
		fclose(file1_1); 
		return false;
	}
	if (!(file2_1 = fopen("support_input_names_file.bin", "r+b")))
	{
		printf("\nFiles aren't opened\n");
		fclose(file1_1); 
		fclose(file1_2);
		return false;
	}
	if (!(file2_2 = fopen("support_input_numbers_file.bin", "r+b")))
	{
		printf("\nFiles aren't opened\n");
		fclose(file1_1); 
		fclose(file1_2);
		fclose(file2_1); 
		return false;
	}
	printf("\t\tMain file: \n");
	binary_file_read(file1_1, file1_2);
	fclose(file1_1); fclose(file1_2);
	printf("\n\n\t\tSupport file: \n\n");
	binary_file_read(file2_1, file2_2);
	fclose(file2_1); fclose(file2_2);
	return true;
}
void binary_file_read(FILE *file1, FILE *file2)
{
	const char massive[] = { "$$$" };
	struct good *str;
	while (1)
	{
		if ((!(str = (struct good*)calloc(1, sizeof(struct good)))
			||!(str->name = (char*)calloc((WORD_LENGTH + 1), sizeof(char)))
			||!(str->number = (char*)calloc((WORD_LENGTH + 1), sizeof(char)))))
		{
			printf("\nMemory isn't allocated\n");
			fclose(file1); fclose(file2);
			exit(-3);
		}
		fread(str->name, sizeof(char), sizeof(str->name) / sizeof(char), file1);
		fread(str->number, sizeof(char),  sizeof(str->name) / sizeof(char), file2);
		if (strcmp(str->name, massive) == 0 || strcmp(str->number, massive) == 0)
		{
			free(str->name);
			free(str->number);
			free(str);
			break;
		}
		printf("%s  %s\n", str->name, str->number);
		free(str->name);
		free(str->number);
		free(str);
	}
}
bool check_string(char *string)
{
	int j, n, temp1 = 0;
	n = (strlen(string) - 1);
	if (string[0] == '\n' || string[0] == '\0')
	{
		printf("\tEmpty input is forbidden, try again: ");
		return false;
	}
	for (j = 0; j < n; j++)
	{
		if (string[j] == ' ') temp1++;
	}
	if (temp1 == n)
	{
		printf("\tEmpty input is forbidden and max size of name is %d, try again: ", WORD_LENGTH);
		return false;
	}
	return true;
}
bool check_number(char *number)
{
	int element, n = strlen(number), i;
	for (i = 0; i < (n - 1); i++)
	{
		if (number[i] < '0' || number[i] > '9')
		{
			if (i == 0 && number[i] == '-') continue;
			else
			{
				printf("\tInput number again please(example: 123): ");
				return false;
			}
		}
	}
	element = atoi(number);
	if (element < INT32_MIN || element > INT32_MAX)
	{
		printf("\tIncorrect input, try again: ");
		return false;
	}
	return true;
}
