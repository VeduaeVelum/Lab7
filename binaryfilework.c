#include "binaryfilework.h"

void queue_push(struct good *str);
bool func_delete(void);
bool reinput_binaryfile(void);

struct queue_words
{
	char *prodact_name;
	int prodact_number;
	struct queue_words *next;
}*q_first = { NULL }, *q_last = { NULL };

bool determine_prodacts_number(void)
{
	bool flag = true;
	FILE *file1_1, *file1_2, *file2_1, *file2_2;
	if (!(file1_1 = fopen("main_input_names_file.bin", "r+b"))
		|| (!(file1_2 = fopen("main_input_numbers_file.bin", "r+b")))
		|| (!(file2_1 = fopen("support_input_names_file.bin", "r+b")))
		|| (!(file2_2 = fopen("support_input_numbers_file.bin", "r+b"))))
	{
		printf("\nFiles aren't opened\n");
		fclose(file1_1); fclose(file1_2);
		fclose(file2_1); fclose(file2_2);
		return false;
	}
	binary_file_work(file1_1, file1_2);
	binary_file_work(file2_1, file2_2);							
	flag = reinput_binaryfile();
	func_delete();
	if (flag == true)
	{
		printf("File was successfully reinputed\n");
		return true;
	}
	else return false;
}
void binary_file_work(FILE *file1, FILE *file2)
{
	const char massive[] = { "$$$" };	
	int a, b;
	struct queue_words *q_current;
	struct good *str;
	while (1)
	{
		if ((!(str = (struct good*)calloc(1, sizeof(struct good)))
			||!(str->name = (char*)calloc((WORD_LENGTH + 1), sizeof(char)))
			||!(str->number = (char*)calloc((WORD_LENGTH + 1), sizeof(char)))))
		{
			printf("\nMemory isn't allocated\n");
			if(str->name) 
			{
				free(str->name);
				free(str);
			}
			if(str->number) 
			{
				free(str->number);
				free(str);
			}
			fclose(file1); fclose(file2);
			exit(-3);
		}
		fread(str->name, sizeof(char), sizeof(str->name) / sizeof(char), file1);
		fread(str->number, sizeof(char), sizeof(str->number) / sizeof(char), file2);
		if (strcmp(str->name, massive) == 0 || strcmp(str->number, massive) == 0)
		{
			free(str->name);
			free(str->number);
			free(str);
			break;
		}
		if (q_first == NULL) queue_push(str);
		else
		{
			q_current = q_first;
			do
			{
				if (strcmp(q_current->prodact_name, str->name) == 0)
				{
					q_current->prodact_number += atoi(str->number);
					break;
				}
				q_current = q_current->next;
			} while (q_current != NULL);
			if (q_current == NULL) queue_push(str);
		}
		free(str->name);
		free(str->number);
		free(str);
	}
	fclose(file1); fclose(file2);
}
void queue_push(struct good *str)
{
	struct queue_words *q;
	int i = 0;
	if (!(q = (struct queue_words*)calloc(1, sizeof(struct queue_words))) ||
		!(q->prodact_name = (char*)calloc(WORD_LENGTH, sizeof(char))))
	{
		printf("Memory is not allocated\n");
		fcloseall();
		func_delete();
		exit(-3);
	}
	do
	{
		q->prodact_name[i] = str->name[i++];
	} while (str->name[i] != '\0');
	q->prodact_number = atoi(str->number);
	if (q_first == NULL) q_first = q_last = q;
	else
	{
		q_last->next = q;
		q_last = q;
	}
}
bool reinput_binaryfile(void)
{
	char *number;
	const char massive[] = { "$$$" };
	FILE *file1, *file2;
	struct queue_words *q_current;
	q_current = q_first;
	if (!(file1 = fopen("main_input_names_file.bin", "w+b"))
		|| (!(file2 = fopen("main_input_numbers_file.bin", "w+b"))))
	{
		printf("\nFiles aren't opened\n");
		func_delete();
		fclose(file1); fclose(file2);
		return false;
	}
	do
	{
		if(!(number = (char*)calloc((NUMBER_LENGTH + 1), sizeof(char))))
		{
			printf("Memory is not allocated\n");
			fclose(file1); fclose(file2);
			func_delete();
			return false;
		}
		sprintf(number, "%d", q_current->prodact_number);
		if (q_current->prodact_number <= 0)
		{
			q_current = q_current->next;
			free(number);
			continue;
		}
		fwrite(q_current->prodact_name, sizeof(char), sizeof(q_current->prodact_name) / sizeof(char), file1);
		fwrite(number, sizeof(char), sizeof(number) / sizeof(char), file2);
		q_current = q_current->next;
		free(number);
	} while (q_current != NULL);
	fwrite(massive, sizeof(char), sizeof(massive) / sizeof(char), file1);
	fwrite(massive, sizeof(char), sizeof(massive) / sizeof(char), file2);
	fclose(file1); fclose(file2);
	return true;
}
bool func_delete(void)
{
	struct queue_words *q_current;
	if (q_first == NULL)
	{
		return true;
	}
	q_current = q_first;
	while (q_current != NULL)
	{
		q_first = q_current;
		q_current = q_first->next;
		free(q_first->prodact_name);
		free(q_first);
	}
	return true;
}
