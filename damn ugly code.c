#include "header.h"

void	copies_char(char string1[], int poz1, char string2[], int poz2)

// Copies the char at position 'poz2' from string2, to the pozition 'poz1' in string1.

{
	string1[poz1] = string2[poz2];
	if (string2[poz2 + 1] == ';' || string2[poz2 + 1] == '\0')
		string1[poz1 + 1] = '\0';
}

void	print_if_over_eight(char first_name[], char sure_name[], char grade[], char state[])

// Prints the person, if it has a greater grade than eight, and it is from Cluj.

{
	if (strcmp(state, "Cluj") == 0 && atof(grade) > 8.00)
		printf("%s %s\n", first_name, sure_name);
}

int		ft_is_alpha(char string[])

// Returns 1 if the string is alphabetical and 0 otherwise.

{
	int index;

	index = 0;
	while (string[index])
	{
		if (!((string[index] <= 'Z' && string[index] >= 'A') || (string[index] <= 'z' && string[index] >= 'a')))
			return (0);
		index++;
	}
	return (1);
}

int		fname_validator(char first_name[])

// Returns 1 if the first name is valid. If not, it returns 0 and prints an error message.

{
	if (!(ft_is_alpha(first_name)))
	{
		printf("The first name is invalid! \"%s\"\n", first_name);
		return (0);
	}
	else
		return (1);
}

int		sname_validator(char sure_name[])

// Returns 1 if the sure name is valid. If not, it returns 0 and prints an error message.

{
	if (!(ft_is_alpha(sure_name)))
	{
		printf("The sure name is invalid! \"%s\"\n", sure_name);
		return (0);
	}
	else
		return (1);
}


int		grade_validator(char grade[])

// Returns 1 if the grade is valid. If not, it returns 0 and prints an error message.

{
	int not_ok;

	not_ok = 1;
	if (grade[0] == '1' && grade[1] == '0')
		not_ok = 0;
	else if (grade[0] <= '9' && grade[0] >= '0' && (grade[1] == '.' || grade[1] == ','))
		if (grade[2] <= '9' && grade[2] >= '0' && grade[3] <= '9' && grade[3] >= '0')
			not_ok = 0;
	if (not_ok)
	{
		printf("The grade is invalid! It must have: <x.yz> format! \"%s\"\n", grade);
		return (0);
	}
	return (1);
}

int		copy_for_type(char first_name[], char sure_name[], char mail[], char grade[], char state[], int word_type, int *word_counter, int buff_counter, char buff[])

// copies_char function is applied having in mind the type of the word.

{
	if (word_type == 0)
		copies_char(first_name, *word_counter, buff, buff_counter);
	if (word_type == 1)
		copies_char(sure_name, *word_counter, buff, buff_counter);
	if (word_type == 2)
		copies_char(mail, *word_counter, buff, buff_counter);
	if (word_type == 3)
		copies_char(grade, *word_counter, buff, buff_counter);
	if (word_type == 4)
		copies_char(state, *word_counter, buff, buff_counter);
	*word_counter = *word_counter + 1;
	return (1);
}

int		open_validator(FILE *file)

// Returns 1 if the file was succesfully opened and 0 plus an error message otherwise.

{
	if (file == NULL)
	{
		printf("Error opening the file!\n");
		return (0);
	}
	return (1);
}

int		validator(char first_name[], char sure_name[], char grade[], int word_type)

// Returns 1 if all the fields are valid and 0 plus an error message if one or more fields are invalid.

{
	if (word_type > 4)
	{
		printf("Invalid line! It must contain only 5 fields: first_name;sure_name;mail;grade;state !\n");
		return (0);
	}
	if (!(fname_validator(first_name)))
		return (0);
	else if (!(sname_validator(sure_name)))
		return (0);
	else if (!(grade_validator(grade)))
		return (0);
	return (1);
}

int		main(void)
{
	FILE	*file;
	char	buff[255];
	char	first_name[20];
	char	sure_name[20];
	char	mail[20];
	char	grade[5];
	char	state[10];
	int		buff_counter = 0;
	int		word_type = 0;
	int		word_counter = 0;

	file = fopen("students.csv", "r");
	if (!(open_validator(file)))
		return (0);
	while (fscanf(file, "%s", buff) > 0)
	{
		word_type = 0;
		word_counter = 0;
		buff_counter = 0;
		while (*(buff + buff_counter) != 0)
		{
			if (buff[buff_counter] == ';')
			{
				word_type++;
				word_counter = 0;
			}
			else
				copy_for_type(first_name, sure_name, mail, grade, state, word_type, &word_counter, buff_counter, buff);
			buff_counter++;
		}
		if (!(validator(first_name, sure_name, grade, word_type)))
			return (0);
		print_if_over_eight(first_name, sure_name, grade, state);
	}

	//Test
	test_ft_is_alpha();
	return (0);
}
